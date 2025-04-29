#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVector>
#include <QRegularExpression>
// #include "xlsxdocument.h"  // 添加 QtXlsx 头文件
// #include "xlsxformat.h"    // 用于设置单元格格式
// #include <QFileDialog>     // 让用户选择 Excel 保存路径

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// 定义通道数，4个通道
static const int CHANNEL_COUNT = 4;

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
    void updateBaudRate();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;    // 串口
    QVector<double> maxStrain;
    QVector<double> minStrain;

    QSerialPort::BaudRate currentBaudRate;
    QSerialPort::DataBits currentDataBits;
    QSerialPort::Parity currentParity;
    QSerialPort::StopBits currentStopBits;

    // 对于4个通道，每个通道有一个 QLineSeries 和一个 QChart（这里每个图表都显示一条曲线）
    QLineSeries* series[CHANNEL_COUNT];
    QChart* chart[CHANNEL_COUNT];
    QValueAxis* axisX[CHANNEL_COUNT];
    QValueAxis* axisY[CHANNEL_COUNT];

    // 存储每个通道的采集数据（用于可选的进一步处理，这里主要用于曲线显示）
    QVector<QVector<double>> strainData; // strainData[i] 存储第 i 个通道的数据

    // 记录每个通道的最值（输出绝对值最大的值，无论正负）
    double absMax[CHANNEL_COUNT]; // 初始化时设为 0

    // 辅助函数：解析一行串口数据，更新对应通道数据和图表
    void parseStrainLine(const QString &line);

};
#endif // MAINWINDOW_H
