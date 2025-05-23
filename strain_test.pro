QT       += core gui serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 添加 QXlsx 目录
INCLUDEPATH += "D:/PROGRA~2/Qt/project/strain_test/strain_test/QXlsx"
DEPENDPATH += "D:/PROGRA~2/Qt/project/strain_test/strain_test/QXlsx"

include($$PWD/QXlsx/QXlsx.pri)


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    strain_test_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
