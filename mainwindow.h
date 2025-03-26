#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void refreshSerialPorts(); //刷新串口
    void openSerialPort();  // 打开串口
    void closeSerialPort(); // 关闭串口
    void readSerialData();  // 读取串口数据
    void clearData();       // 清除数据


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;    // 串口
    QSerialPort::BaudRate currentBaudRate;
    QSerialPort::DataBits currentDataBits;
    QSerialPort::Parity currentParity;
    QSerialPort::StopBits currentStopBits;
    QLineSeries *series;    // 数据曲线
    QChart *chart;          // 图表
    QValueAxis *axisX;      // X轴
    QValueAxis *axisY;      // Y轴
    QVector<double> strainData; // 存储应变数据
    double minStrain = 1e9, maxStrain = -1e9; // 记录最小、最大值
};
#endif // MAINWINDOW_H
