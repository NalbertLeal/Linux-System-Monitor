#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T19:17:33
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = LinuxSystemMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ProcessData.cpp \
    JsonCreator.cpp \
    qcustomplot.cpp \
    CPUs.cpp \
    memory.cpp \
    Energy.cpp

HEADERS  += mainwindow.h \
    process.h \
    ProcessData.h \
    JsonCreator.h \
    qcustomplot.h \
    CPUs.h \
    memory.h \
    Energy.h

FORMS    += mainwindow.ui

RESOURCES += \
    meusarquivos.qrc

DISTFILES += \
    processos.json \
    TesteWeb.pro.user \
    index.html
