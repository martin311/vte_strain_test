/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnOpen;
    QPushButton *btnClose;
    QPushButton *btnClear;
    QComboBox *comboBoxPort;
    QLabel *label;
    QChartView *chartViewCH1;
    QLabel *labelCH1Max;
    QPushButton *btnRefresh;
    QLabel *label_2;
    QComboBox *comboBoxBaud;
    QLabel *label_3;
    QLabel *label_7;
    QComboBox *comboBoxFreq;
    QLabel *label_8;
    QPushButton *btnZero;
    QPushButton *btnSetFreq;
    QPushButton *btnResetChart;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1302, 637);
        MainWindow->setMouseTracking(true);
        MainWindow->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName("btnOpen");
        btnOpen->setGeometry(QRect(50, 100, 80, 23));
        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName("btnClose");
        btnClose->setGeometry(QRect(50, 140, 80, 23));
        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(50, 560, 80, 23));
        comboBoxPort = new QComboBox(centralwidget);
        comboBoxPort->setObjectName("comboBoxPort");
        comboBoxPort->setGeometry(QRect(10, 260, 72, 23));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 230, 51, 21));
        chartViewCH1 = new QChartView(centralwidget);
        chartViewCH1->setObjectName("chartViewCH1");
        chartViewCH1->setGeometry(QRect(350, 80, 811, 431));
        labelCH1Max = new QLabel(centralwidget);
        labelCH1Max->setObjectName("labelCH1Max");
        labelCH1Max->setGeometry(QRect(580, 50, 111, 16));
        btnRefresh = new QPushButton(centralwidget);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setGeometry(QRect(50, 180, 71, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 230, 61, 21));
        comboBoxBaud = new QComboBox(centralwidget);
        comboBoxBaud->setObjectName("comboBoxBaud");
        comboBoxBaud->setGeometry(QRect(90, 260, 72, 23));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(510, 50, 51, 21));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 10, 91, 21));
        comboBoxFreq = new QComboBox(centralwidget);
        comboBoxFreq->setObjectName("comboBoxFreq");
        comboBoxFreq->setGeometry(QRect(10, 330, 72, 23));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 310, 53, 15));
        btnZero = new QPushButton(centralwidget);
        btnZero->setObjectName("btnZero");
        btnZero->setGeometry(QRect(10, 370, 80, 23));
        btnSetFreq = new QPushButton(centralwidget);
        btnSetFreq->setObjectName("btnSetFreq");
        btnSetFreq->setGeometry(QRect(100, 330, 80, 23));
        btnResetChart = new QPushButton(centralwidget);
        btnResetChart->setObjectName("btnResetChart");
        btnResetChart->setGeometry(QRect(100, 370, 80, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1302, 20));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\225\260\346\215\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\257\345\217\243", nullptr));
        labelCH1Max->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\344\270\262\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\263\242\347\211\271\347\216\207", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "CH1", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "VTE\345\272\224\345\217\230\346\265\213\350\257\225", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\250\243\347\216\207", nullptr));
        btnZero->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\233\266", nullptr));
        btnSetFreq->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\226\260\351\207\207\346\250\243\347\216\207", nullptr));
        btnResetChart->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
