#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , series(new QLineSeries())
    , chart(new QChart())
    , axisX(new QValueAxis())
    , axisY(new QValueAxis())
    , minStrain(1e9)  // 初始化为极大值
    , maxStrain(-1e9)  // 初始化为极小值
    // , statusbar()
{
    ui->setupUi(this);
    refreshSerialPorts();
    // 配置串口
    currentBaudRate = QSerialPort::Baud115200;
    currentDataBits = QSerialPort::Data8;
    currentParity = QSerialPort::NoParity;
    currentStopBits = QSerialPort::OneStop;

    // 连接信号和槽
    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::clearData);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &MainWindow::refreshSerialPorts);

    // 初始化图表
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("实时应变曲线");

    // 配置 X 轴 (时间轴)
    axisX->setTitleText("Time (s)");
    axisX->setLabelFormat("%.1f");
    axisX->setRange(0, 60);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 配置 Y 轴 (应变值)
    axisY->setTitleText("Strain");
    axisY->setLabelFormat("%.6f");
    axisY->setRange(-0.002, 0.002);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 显示图表
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete series;
    delete chart;
    delete axisX;
    delete axisY;
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
    } else {
        statusBar()->showMessage("串口打开失败: " + serial->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    serial->close();
    statusBar()->showMessage("串口已关闭");  // 统一使用 statusBar()
}

// 读取 STM32 发送的应变数据
void MainWindow::readSerialData()
{
    QByteArray data = serial->readAll();
    QString strData = QString::fromUtf8(data).trimmed();

    // 使用正则表达式匹配数据格式
    QRegularExpression regex("STRAIN=([+-]?\\d+\\.?\\d*)");
    QRegularExpressionMatch match = regex.match(strData);

    if (match.hasMatch()) {
        bool ok;
        double strain = match.captured(1).toDouble(&ok);

        if (!ok) {
            qDebug() << "数据转换失败：" << strData;
            return;
        }

        // 更新最值（需在类声明中初始化 minStrain 和 maxStrain）
        minStrain = qMin(minStrain, strain);
        maxStrain = qMax(maxStrain, strain);

        // 显示最值
        ui->labelMin->setText(QString("Min: %1").arg(minStrain, 0, 'f', 6));
        ui->labelMax->setText(QString("Max: %1").arg(maxStrain, 0, 'f', 6));

        // 绘制数据
        static qint64 startTime = QDateTime::currentMSecsSinceEpoch();
        qreal time = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;

        series->append(time, strain);

        // 动态调整 X 轴范围（显示最近 60 秒数据）
        if (time > 60) {
            axisX->setRange(time - 60, time);
        } else {
            axisX->setRange(0, 60);
        }

        // 自动缩放 Y 轴
        chart->axisY ()->setRange(minStrain - 0.0001, maxStrain + 0.0001);
    } else {
        qDebug() << "无效数据格式：" << strData;
    }
}

// 清除数据
void MainWindow::clearData()
{
    strainData.clear();
    series->clear();
    minStrain = 1e9;
    maxStrain = -1e9;
    ui->labelMin->setText("Min: -");
    ui->labelMax->setText("Max: -");
}
