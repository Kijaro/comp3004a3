#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>
#include <QMainWindow>
#include <queue>

class Elevator
{
private:
        int floorNum;
        int id;
        std::string direction;
        static int nextId;
        std::queue<int> floorQueue;
        QString message;
        int weight;
        bool doorBlocked;
        int doorOpenTime;
        std::vector<int> checkedButtons;

public:

    Elevator();
    void openDoor();
    void closeDoor();
    void ringBell();
    void travelTo(int fn); //void travelTo(*Floor f);
    int getNextInQueue();
    void addToQueue(int f);
    int getId();
    int getFloor();
    int getQueueSize();
    QString getMessage();
    void changeMessage(QString m);
    void safeFloor();
    void setWeight(int w);
    int getWeight();
    void toggleDoorBlocked();
    bool getDoorBlocked();
    void doorOpenPressed();
    void doorClosedPressed();
    bool checkIfButtonChecked(int b);
    void addChecked(int b);
    void removeChecked(int b);
};



#endif // ELEVATOR_H
