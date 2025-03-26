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
    QChartView *chartView;
    QLabel *labelMin;
    QLabel *labelMax;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMouseTracking(true);
        MainWindow->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName("btnOpen");
        btnOpen->setGeometry(QRect(30, 70, 80, 23));
        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName("btnClose");
        btnClose->setGeometry(QRect(30, 110, 80, 23));
        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(30, 150, 80, 23));
        comboBoxPort = new QComboBox(centralwidget);
        comboBoxPort->addItem(QString());
        comboBoxPort->addItem(QString());
        comboBoxPort->addItem(QString());
        comboBoxPort->addItem(QString());
        comboBoxPort->addItem(QString());
        comboBoxPort->setObjectName("comboBoxPort");
        comboBoxPort->setGeometry(QRect(30, 230, 72, 23));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 200, 71, 21));
        chartView = new QChartView(centralwidget);
        chartView->setObjectName("chartView");
        chartView->setGeometry(QRect(200, 70, 431, 281));
        labelMin = new QLabel(centralwidget);
        labelMin->setObjectName("labelMin");
        labelMin->setGeometry(QRect(250, 450, 81, 16));
        labelMax = new QLabel(centralwidget);
        labelMax->setObjectName("labelMax");
        labelMax->setGeometry(QRect(250, 470, 81, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
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
        comboBoxPort->setItemText(0, QCoreApplication::translate("MainWindow", "COM1", nullptr));
        comboBoxPort->setItemText(1, QCoreApplication::translate("MainWindow", "COM2", nullptr));
        comboBoxPort->setItemText(2, QCoreApplication::translate("MainWindow", "COM3", nullptr));
        comboBoxPort->setItemText(3, QCoreApplication::translate("MainWindow", "COM4", nullptr));
        comboBoxPort->setItemText(4, QCoreApplication::translate("MainWindow", "COM5", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\344\270\262\345\217\243\345\217\267", nullptr));
        labelMin->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelMax->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
