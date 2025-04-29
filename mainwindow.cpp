#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , maxStrain(4, -1e9)
    , minStrain(4, 1e9)
    // , statusbar()
{
    ui->setupUi(this);
    refreshSerialPorts();

    // 初始化波特率下拉框
    ui->comboBoxBaud->addItem("9600", QSerialPort::Baud9600);
    ui->comboBoxBaud->addItem("19200", QSerialPort::Baud19200);
    ui->comboBoxBaud->addItem("38400", QSerialPort::Baud38400);
    ui->comboBoxBaud->addItem("57600", QSerialPort::Baud57600);
    ui->comboBoxBaud->addItem("115200", QSerialPort::Baud115200);
    //ui->comboBoxBaud->addItem("230400", QSerialPort::Baud230400);


    // 配置串口
    //currentBaudRate = QSerialPort::Baud115200;
    // 默认选中 115200
    int index = ui->comboBoxBaud->findData(QSerialPort::Baud115200);
    if (index != -1) {
        ui->comboBoxBaud->setCurrentIndex(index);
    }

    currentDataBits = QSerialPort::Data8;
    currentParity = QSerialPort::NoParity;
    currentStopBits = QSerialPort::OneStop;

    // 连接信号槽，用户更改波特率时更新 currentBaudRate
    connect(ui->comboBoxBaud, &QComboBox::currentIndexChanged, this, &MainWindow::updateBaudRate);

    // 连接信号和槽
    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::clearData);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &MainWindow::refreshSerialPorts);

    // 初始化 4 个通道相关数据
    strainData.resize(CHANNEL_COUNT);
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        absMax[i] = 0.0; // 初始绝对值最大为0

        // 初始化图表对象，每个通道独立显示
        series[i] = new QLineSeries();
        chart[i] = new QChart();
        axisX[i] = new QValueAxis();
        axisY[i] = new QValueAxis();

        chart[i]->legend()->hide();
        chart[i]->addSeries(series[i]);
        chart[i]->setTitle(QString("CH%1 实时应变曲线").arg(i + 1));

        // X轴设置：时间轴，范围显示最近60秒数据
        axisX[i]->setTitleText("Time (s)");
        axisX[i]->setLabelFormat("%.1f");
        axisX[i]->setRange(0, 240);
        chart[i]->addAxis(axisX[i], Qt::AlignBottom);
        series[i]->attachAxis(axisX[i]);

        // Y轴设置：应变值，初始范围可根据实际情况调整
        axisY[i]->setTitleText("Strain");
        axisY[i]->setLabelFormat("%.2f");
        axisY[i]->setRange(-20000, 20000);
        chart[i]->addAxis(axisY[i], Qt::AlignLeft);
        series[i]->attachAxis(axisY[i]);
    }

    // 将4个图表分别放到 UI 中的对应 ChartView 控件里
    ui->chartViewCH1->setChart(chart[0]);
    ui->chartViewCH1->setRenderHint(QPainter::Antialiasing);
    ui->chartViewCH2->setChart(chart[1]);
    ui->chartViewCH2->setRenderHint(QPainter::Antialiasing);
    ui->chartViewCH3->setChart(chart[2]);
    ui->chartViewCH3->setRenderHint(QPainter::Antialiasing);
    ui->chartViewCH4->setChart(chart[3]);
    ui->chartViewCH4->setRenderHint(QPainter::Antialiasing);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete serial;
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        delete series[i];
        delete chart[i];
        delete axisX[i];
        delete axisY[i];
    }
}

void MainWindow::refreshSerialPorts() {
    ui->comboBoxPort->clear();  // 清空现有选项

    // 获取所有可用串口
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    // 如果没有找到串口
    if (ports.isEmpty()) {
        ui->comboBoxPort->addItem("无可用串口");
        ui->comboBoxPort->setEnabled(false);  // 禁用下拉框
        ui->btnOpen->setEnabled(false);       // 禁用打开按钮
        qDebug() << "未检测到任何串口设备！";
        return;
    }

    // 添加检测到的串口到下拉框
    foreach (const QSerialPortInfo &port, ports) {
        ui->comboBoxPort->addItem(port.portName());
    }

    qDebug() << "检测到串口：" << ui->comboBoxPort->count() << "个";
}

void MainWindow::openSerialPort()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &port, ports) {
        qDebug() << "Found port:" << port.portName();
    }
    QString portName = ui->comboBoxPort->currentText(); // 确保获取的是正确的串口号（如 "COM3"）
    serial->setPortName(portName);
    serial->setBaudRate(currentBaudRate);
    serial->setDataBits(currentDataBits);
    serial->setParity(currentParity);
    serial->setStopBits(currentStopBits);

    if (serial->open(QIODevice::ReadOnly)) {
        statusBar()->showMessage("串口打开成功");  // 使用 statusBar() 方法
    }
    else {
        statusBar()->showMessage("串口打开失败: " + serial->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen()) {
        serial->close();
        statusBar()->showMessage("串口已关闭");
    }
}

void MainWindow::updateBaudRate()
{
    currentBaudRate = static_cast<QSerialPort::BaudRate>(ui->comboBoxBaud->currentData().toInt());
    qDebug() << "波特率已修改为:" << currentBaudRate;
}

// 读取 STM32 发送的应变数据
void MainWindow::readSerialData()
{
    QByteArray data = serial->readAll();
    QString strData = QString::fromUtf8(data).trimmed();

    qDebug() << "[串口接收]：" << strData;

    // 使用正则表达式匹配数据格式
    // QRegularExpression regex("CH(\\d+):\\s*([+-]?\\d+\\.?\\d*)\\s*µε");
    // QRegularExpressionMatch match = regex.match(strData);

    // 假设每一行数据以换行符结束
    static QByteArray buffer;
    buffer += data;
    while (buffer.contains('\n')) {
        int idx = buffer.indexOf('\n');
        QString line = QString::fromUtf8(buffer.left(idx)).trimmed();
        buffer.remove(0, idx + 1);
        parseStrainLine(line);
    }
}

// 解析串口数据，格式示例（第二张图的样子）：
// "CH1:0.00123 CH2:-0.00234 CH3:0.00056 CH4:0.00321"
// 提取每个通道的应变数据，并更新对应图表和最值显示
void MainWindow::parseStrainLine(const QString &line)
{
     // 用正则表达式提取通道数据
     // 正则：匹配 "CH" 后面跟一个或多个数字，后面是冒号，再匹配一个浮点数（带可能的正负号）
    QRegularExpression regex("CH(\\d+):\\s*([+-]?\\d+\\.?\\d*)");
    QRegularExpressionMatchIterator it = regex.globalMatch(line);
    // 获取当前时间（秒），作为X轴数据
    static qint64 startTime = QDateTime::currentMSecsSinceEpoch();
    qreal time = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int ch = match.captured(1).toInt();  // 通道编号（例如1~4）
        double strain = match.captured(2).toDouble();

        // 数组下标从 0 开始，要求 ch 在 1~CHANNEL_COUNT 之间
        if (ch >= 1 && ch <= CHANNEL_COUNT) {
            int idx = ch - 1;
            // 保存数据
            strainData[idx].append(strain);
            // 添加数据到对应的曲线
            series[idx]->append(time, strain);

            // 更新最值：取绝对值最大的值
            if (qAbs(strain) > qAbs(maxStrain[idx])) {
                maxStrain[idx] = strain; // 直接更新最大绝对值对应的值
            }

            // 更新 UI 标签（假设标签名称为 labelCH1Max, labelCH2Max, …）
            QLabel* labels[] = {ui->labelCH1Max, ui->labelCH2Max, ui->labelCH3Max, ui->labelCH4Max};
            labels[idx]->setText(QString("Max: %1 µε").arg(qAbs(maxStrain[idx]), 0, 'f', 2));
            // switch (idx) {
            // case 0: ui->labelCH1Max->setText(QString("Max: %1 µε").arg(qMax(qAbs(minStrain[0]), qAbs(maxStrain[0])), 0, 'f', 2)); break;
            // case 1: ui->labelCH2Max->setText(QString("Max: %1").arg(qMax(qAbs(minStrain[1]), qAbs(maxStrain[1])), 0, 'f', 2)); break;
            // case 2: ui->labelCH3Max->setText(QString("Max: %1 µε").arg(qMax(qAbs(minStrain[2]), qAbs(maxStrain[2])), 0, 'f', 2)); break;
            // case 3: ui->labelCH4Max->setText(QString("Max: %1").arg(qMax(qAbs(minStrain[3]), qAbs(maxStrain[3])), 0, 'f', 2)); break;
            // default: break;
            // }

            // 调整 X 轴范围，保持显示最近 60 秒
            if (time > 240)
                axisX[idx]->setRange(time - 240, time);
        }
    }
}


// 清除数据
void MainWindow::clearData()
{
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        strainData[i].clear();
        series[i]->clear();
        //minStrain[i] = 1e9;
        //maxStrain[i] = -1e9;
    }
    // 同时更新 UI 标签
    ui->labelCH1Max->setText("Max: - µε");
    ui->labelCH2Max->setText("Max: - µε");
    ui->labelCH3Max->setText("Max: - µε");
    ui->labelCH4Max->setText("Max: - µε");
}

