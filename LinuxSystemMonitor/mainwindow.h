#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <vector>

#include <QTimer>

#include "Energy.h"
#include "JsonCreator.h"
#include "CPUs.h"
#include "memory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    JsonCreator* jc;
    CPUs* cpu;
    Memory* mem;
    Energy* energy;
    QTimer dataTimer;
    int jsonType;

//    void ThreadSlotChartCPU();

private slots:
    void SlotKillProcess();

    void updateBubllesCPU();
    void updateBubllesThreads();
    void updateBubllesMemory();
    void updateBubllesMedia();

    void startChartCpu();
    void SlotchartOfCPU();

    void startChartMemory();
    void SlotchartOfMemory();

    void startChartBatteryPercentage();
    void SlotchartOfBatteryPercentage();

    void startChartBatteryDischage();
    void SlotchartOfBatteryDischage();

signals:
    void updateChartOfCPU(std::vector<long>);
};

#endif // MAINWINDOW_H
