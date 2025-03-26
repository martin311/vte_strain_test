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
    // , statusbar()
{
    ui->setupUi(this);
    // 配置串口
    serial->setBaudRate(115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);

    // 连接信号和槽
    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::clearData);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);

    // 初始化图表
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("实时应变曲线");

    // 配置 X 轴 (时间轴)
    axisX->setTitleText("Time (s)");
    axisX->setLabelFormat("%d");
    axisX->setRange(0, 1000);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSerialPort()
{
    serial->setPortName(ui->comboBoxPort->currentText());
    // if (serial->open(QIODevice::ReadOnly)) {
    //     ui->statusbar->showMessage("串口打开成功");
    // } else {
    //     ui->statusbar->showMessage("串口打开失败");
    // }
}

void MainWindow::closeSerialPort()
{
    serial->close();
    // ui->statusbar->showMessage("串口已关闭");
}

// 读取 STM32 发送的应变数据
void MainWindow::readSerialData()
{
    QByteArray data = serial->readAll();
    QString strData = QString::fromUtf8(data).trimmed();  // 转换为字符串

    // 解析数据格式: "ADC=xxx  VOL=xx.xx  STRAIN=xx.xx"
    QStringList list = strData.split(" ");
    if (list.size() >= 6) {
        double strain = list[5].toDouble();

        // 记录最值
        if (strain < minStrain) minStrain = strain;
        if (strain > maxStrain) maxStrain = strain;

        // 显示最值
        ui->labelMin->setText(QString("Min: %1").arg(minStrain, 0, 'f', 6));
        ui->labelMax->setText(QString("Max: %1").arg(maxStrain, 0, 'f', 6));

        // 绘制数据
        strainData.append(strain);
        series->append(strainData.size(), strain);

        // 让 X 轴滚动
        if (strainData.size() > 1000) {
            strainData.removeFirst();
            axisX->setRange(strainData.size() - 1000, strainData.size());
        }

        // 更新 Y 轴范围
        double minY = *std::min_element(strainData.begin(), strainData.end());
        double maxY = *std::max_element(strainData.begin(), strainData.end());
        axisY->setRange(minY, maxY);
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
