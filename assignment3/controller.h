#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "elevator.h"
#include "floor.h"


class Controller
{
private:
    std::vector<Elevator*> elevators;
    std::vector<Floor*> floors;

public:
    void addElevatorToList(Elevator* e);
    void addFloorToList(Floor* f);
    void controlElevators();
    Controller();
    ~Controller();
    Elevator* getElevator(int id);
    Elevator* findBestElevator(int fn);
    Floor* getFloor(int fn);
    int getElevatorCount();
    void fireAlarmPressed();
    void powerOutPressed();
};

#endif // CONTROLLER_H
