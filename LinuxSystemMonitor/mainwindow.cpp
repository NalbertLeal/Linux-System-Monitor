#include <thread>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include<csignal>
#include <stdlib.h>

#include <QLineEdit>
#include <QString>
#include <QSharedPointer>
#include <QColor>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "JsonCreator.h"
#include "CPUs.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    jc = new JsonCreator();
    cpu = new CPUs();
    mem = new Memory();
    energy = new Energy();

    jsonType = 0;

    ui->setupUi(this);

    ui->widget->load(QUrl::fromLocalFile("/home/nalbert/programacao/c++/projetosC++/TesteWeb/index.html"));

    connect(ui->pushButton_kill, SIGNAL(clicked(bool)), this, SLOT(SlotKillProcess()));

    connect(ui->pushButton_CPU, SIGNAL(clicked(bool)), this, SLOT(updateBubllesCPU()));
    connect(ui->pushButton_Threads, SIGNAL(clicked(bool)), this, SLOT(updateBubllesThreads()));
    connect(ui->pushButton_Memory, SIGNAL(clicked(bool)), this, SLOT(updateBubllesMemory()));
    connect(ui->pushButton_Media, SIGNAL(clicked(bool)), this, SLOT(updateBubllesMedia()));

//    connect(this, SIGNAL(updateChartOfCPU(std::vector<double>)), SLOT(SlotchartOfCPU(std::vector<double>)));

    startChartCpu();
    startChartMemory();
    startChartBatteryPercentage();
    startChartBatteryDischage();

//    std::thread threadCPU = std::thread(&MainWindow::ThreadSlotChartCPU, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBubllesCPU() {
    jsonType = 0;
    jc->createJson(jsonType);
    ui->widget->repaint();
    ui->widget->reload();
    ui->widget->update();
}

void MainWindow::updateBubllesThreads() {
    jsonType = 1;
    jc->createJson(jsonType);
    ui->widget->repaint();
    ui->widget->reload();
    ui->widget->update();
}

void MainWindow::updateBubllesMemory() {
    jsonType = 2;
    jc->createJson(jsonType);
    ui->widget->repaint();
    ui->widget->reload();
    ui->widget->update();
}

void MainWindow::updateBubllesMedia() {
    jsonType = 3;
    jc->createJson(jsonType);
    ui->widget->repaint();
    ui->widget->reload();
    ui->widget->update();
}

//kill process
void MainWindow::SlotKillProcess() {
    QString toKill;
    toKill = ui->lineEdit->text();
    std::string auxToKill = toKill.toUtf8().constData();

    std::stringstream ss(auxToKill);
    pid_t p;
    ss >> p;
    ss.clear();

    kill(p, SIGKILL);

    jc->createJson(jsonType);
    ui->widget->repaint();
    ui->widget->reload();
    ui->widget->update();
}

// cpu chart

void MainWindow::startChartCpu() {
    for(int index = 0; index < cpu->nCores(); index++) {
        if(index % 3 == 1) {
            ui->chartOfCPU->addGraph();
            ui->chartOfCPU->graph(index)->setPen(QPen(QColor(index*index, index, index*index*index*index)));
        }
        else if(index % 3 == 2) {
            ui->chartOfCPU->addGraph();
            ui->chartOfCPU->graph(index)->setPen(QPen(QColor(index*index*index, index*index, index)));
        }
        else {
            ui->chartOfCPU->addGraph();
            ui->chartOfCPU->graph(index)->setPen(QPen(QColor(index, index*index*index*index, index*index)));
        }

    }

    ui->chartOfCPU->xAxis->setTickLabels(true);
    ui->chartOfCPU->axisRect()->setupFullAxesBox();

    ui->chartOfCPU->yAxis->setRange(-3, 100.0);

    ui->chartOfCPU->legend->setVisible(true);
    ui->chartOfCPU->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartOfCPU->legend->setRowSpacing(0);

//    connect(ui->chartOfCPU->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfCPU->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->chartOfCPU->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfCPU->yAxis2, SLOT(setRange(QCPRange)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->chartOfCPU->xAxis->setTicker(timeTicker);
    ui->chartOfCPU->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartOfCPU->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfCPU->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartOfCPU->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfCPU->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(SlotchartOfCPU()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

//void MainWindow::ThreadSlotChartCPU() {
//    while(true) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(250));
//        cpu->updateCpuCores();
//        std::vector<double> auxVec;
//        for(int index = 0; index < cpu->nCores(); index++) {
//            auxVec.push_back(cpu->corePercentage(index));
//        }
//        emit(updateChartOfCPU(auxVec));
//    }
//}

void MainWindow::SlotchartOfCPU() {
//    static QTime time(QTime::currentTime());
//        double key = time.elapsed()/1000.0;

//        for (int index = 0; index < cpu->nCores(); index++)
//            ui->chartOfCPU->graph(index)->addData(key, vec[index]);

//        ui->chartOfCPU->xAxis->setRange(key, 60, Qt::AlignRight);
//        ui->chartOfCPU->replot();

    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        cpu->updateCpuCores();
        for(int index = 0; index < cpu->nCores(); index++) {
            ui->chartOfCPU->graph(index)->addData(key, cpu->corePercentage(index));
        }
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartOfCPU->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartOfCPU->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->chartOfCPU->graph(0)->data()->size()+ui->chartOfCPU->graph(1)->data()->size())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

// memory chart

void MainWindow::startChartMemory() {
    ui->chartOfMem->addGraph();
    ui->chartOfMem->graph(0)->setPen(QPen(QColor(200, 50, 50)));
    ui->chartOfMem->graph(0)->setName("Ram");
    ui->chartOfMem->addGraph();
    ui->chartOfMem->graph(1)->setPen(QPen(QColor(50, 200, 50)));
    ui->chartOfMem->graph(1)->setName("Swap");

    ui->chartOfMem->xAxis->setTickLabels(true);
    ui->chartOfMem->axisRect()->setupFullAxesBox();

    ui->chartOfMem->yAxis->setRange(-3, 101.0);

    ui->chartOfMem->legend->setVisible(true);
    ui->chartOfMem->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartOfMem->legend->setRowSpacing(0);

//    connect(ui->chartOfMem->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->chartOfMem->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->yAxis2, SLOT(setRange(QCPRange)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->chartOfMem->xAxis->setTicker(timeTicker);
    ui->chartOfMem->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartOfMem->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartOfMem->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(SlotchartOfMemory()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::SlotchartOfMemory() {
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        mem->getMemory();
        ui->chartOfMem->graph(0)->addData(key, mem->getPercentageUsed());
        ui->chartOfMem->graph(1)->addData(key, mem->percentageSwap());
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartOfMem->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartOfMem->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->chartOfMem->graph(0)->data()->size()+ui->chartOfMem->graph(1)->data()->size()), 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

// energy battery percentage

void MainWindow::startChartBatteryPercentage() {
    ui->chartOfEnergyPercentage->addGraph();
    ui->chartOfEnergyPercentage->graph(0)->setPen(QPen(QColor(50, 200, 50)));
    ui->chartOfEnergyPercentage->graph(0)->setName("percentage");

    ui->chartOfEnergyPercentage->xAxis->setTickLabels(true);
    ui->chartOfEnergyPercentage->axisRect()->setupFullAxesBox();

    ui->chartOfEnergyPercentage->yAxis->setRange(-3, 101.0);

    ui->chartOfEnergyPercentage->legend->setVisible(true);
    ui->chartOfEnergyPercentage->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartOfEnergyPercentage->legend->setRowSpacing(0);

//    connect(ui->chartOfMem->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->chartOfMem->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->yAxis2, SLOT(setRange(QCPRange)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->chartOfEnergyPercentage->xAxis->setTicker(timeTicker);
    ui->chartOfEnergyPercentage->axisRect()->setupFullAxesBox();
    ui->chartOfEnergyPercentage->yAxis->setRange(-1, 101);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartOfEnergyPercentage->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfEnergyPercentage->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartOfEnergyPercentage->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfEnergyPercentage->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(SlotchartOfBatteryPercentage()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::SlotchartOfBatteryPercentage() {
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        energy->getFileData();
        ui->chartOfEnergyPercentage->graph(0)->addData(key, energy->getPercentage());
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartOfEnergyPercentage->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartOfEnergyPercentage->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->chartOfEnergyPercentage->graph(0)->data()->size()), 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

// energy time to dischage

void MainWindow::startChartBatteryDischage() {
    ui->chartOfEnergyTime->addGraph();
    ui->chartOfEnergyTime->graph(0)->setPen(QPen(QColor(200, 50, 50)));
    ui->chartOfEnergyTime->graph(0)->setName("time to discharge");

    ui->chartOfEnergyTime->xAxis->setTickLabels(true);
    ui->chartOfEnergyTime->axisRect()->setupFullAxesBox();

    ui->chartOfEnergyTime->yAxis->setRange(-3, 60*60*10);

    ui->chartOfEnergyTime->legend->setVisible(true);
    ui->chartOfEnergyTime->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartOfEnergyTime->legend->setRowSpacing(0);

//    connect(ui->chartOfMem->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->chartOfMem->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfMem->yAxis2, SLOT(setRange(QCPRange)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->chartOfEnergyTime->xAxis->setTicker(timeTicker);
    ui->chartOfEnergyTime->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartOfEnergyTime->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfEnergyTime->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartOfEnergyTime->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfEnergyTime->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(SlotchartOfBatteryDischage()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::SlotchartOfBatteryDischage() {
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        energy->getFileData();
        ui->chartOfEnergyTime->graph(0)->addData(key, energy->getTimeToDischage());;
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartOfEnergyTime->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartOfEnergyTime->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->chartOfEnergyTime->graph(0)->data()->size()), 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

// cpu chart

//void MainWindow::startChartCpu() {

//    for(int index = 0; index < cpu->getCpuNumber(); index++) {
//        ui->chartOfCPU->addGraph();
//        ui->chartOfCPU->graph(index)->setPen(QPen(QColor(1, 1, 1)));
//        ui->chartOfCPU->graph(index)->setName("core " + QString::number(index));
//    }

//    ui->chartOfCPU->xAxis->setTickLabels(true);
//    ui->chartOfCPU->axisRect()->setupFullAxesBox();

//    ui->chartOfCPU->yAxis->setRange(0.0, 100.0);

//    ui->chartOfCPU->legend->setVisible(true);
//    ui->chartOfCPU->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
//    ui->chartOfCPU->legend->setRowSpacing(0);

//    connect(ui->chartOfCPU->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfCPU->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->chartOfCPU->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartOfCPU->yAxis2, SLOT(setRange(QCPRange)));
//}

//void MainWindow::ThreadSlotChartCPU() {
//    while(true) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(250));
//        cpu = new CPU();
//        std::vector<long> auxVec;
//        for(int index = 0; index < cpu->getCpuNumber(); index++) {
//            auxVec.push_back(cpu->getCorePercentage(index));
//        }
//        emit(updateChartOfCPU(auxVec));
//    }
//}

//void MainWindow::SlotchartOfCPU(std::vector<long> vec) {
//    static QTime time(QTime::currentTime());
//    double key = time.elapsed()/1000.0;

//    for (int index = 0; index < cpu->getCpuNumber(); index++)
//        ui->chartOfCPU->graph(index)->addData(key, vec[index]);

//    ui->chartOfCPU->xAxis->setRange(key, 60, Qt::AlignRight);
//    ui->chartOfCPU->replot();
//}
