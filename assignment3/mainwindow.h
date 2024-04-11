#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevator.h"
#include "controller.h"
#include "floor.h"
#include <QDebug>
#include <queue>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Controller controller;
    void setConnections();
    int current_elevator;
    int current_floor;
    std::queue<QPushButton*> floorButtonQueue;
    std::queue<QLCDNumber*> elevatorScreenQueue;
    std::vector<QLCDNumber*> elevatorScreenList;
    std::vector<QPushButton*> floorButtonList;
    void initFloorQueue();
    void initElevatorQueue();
    void updateEleScreen();
    void updateEleButtons();
private slots:
    void addElevator();
    void sendElevators();
    void handleElevatorButton(int f);
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void on_floorUpButton_clicked();
    void on_floorDownButton_clicked();
    void on_eleHelpButton_clicked();
    void on_fireButton_clicked();
    void on_powerOutButton_clicked();
    void on_eleWeight_editingFinished();
    void on_doorBlockerButton_clicked();
    void on_openDoorButton_clicked();
    void on_closeDoorButton_clicked();
    void on_addFloorButton_clicked();
};
#endif // MAINWINDOW_H
