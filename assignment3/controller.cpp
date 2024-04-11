#include "controller.h"

Controller::Controller()
{

}

Controller::~Controller()
{
    for(int i = 0; i < elevators.size(); i++){
        delete elevators[i];
    }
    for(int i = 0; i < floors.size(); i++){
        delete floors[i];
    }
}
//adds the given elevator to the controllers list
void Controller::addElevatorToList(Elevator *e){
    elevators.push_back(e);
}

//adds the given floor to the controllers list
void Controller::addFloorToList(Floor *f){
    floors.push_back(f);
}

//controls the elevators, send them all to their next destination and toggle the buttons
void Controller::controlElevators(){
    int next_floor;
    for(int i = 0; i < elevators.size(); i++){
        next_floor = elevators[i]->getNextInQueue();
        if(next_floor == 0) continue; //skip waiting elevators
        if(getFloor(next_floor)->getUpPressed()){
            getFloor(next_floor)->toggleUpPressed();
        }
        if(getFloor(next_floor)->getDownPressed()){
            getFloor(next_floor)->toggleDownPressed();
        }
        elevators[i]->travelTo(next_floor);
    }
}

//return the elevator from the id
Elevator* Controller::getElevator(int id){
    for(int i = 0; i < elevators.size(); i++){
        if(elevators[i]->getId() == id){
            return elevators[i];
        }
    }
    return NULL;
}

//return the floor from the id
Floor* Controller::getFloor(int fn){
    for(int i = 0; i < floors.size(); i++){
        if(floors[i]->getFloorNum() == fn){
            return floors[i];
        }
    }
    return NULL;
}

//calculate the best elevator for a given floor id
Elevator* Controller::findBestElevator(int fn){
    int dist = abs(elevators[0]->getFloor()-fn);
    int ev = 0;
    int prevSize = elevators[0]->getQueueSize();
    //find the elevators with the shortest queue
    for(int i = 1; i < elevators.size(); i++){
        if(elevators[i]->getQueueSize() < prevSize){
            prevSize = elevators[i]->getQueueSize();
            ev = i;
        }
    }
    //find the elevator that is closest with the that has the shortest queue
    for(int i = 1; i < elevators.size(); i++){
        if(elevators[i]->getQueueSize() == prevSize){
            if(dist > abs(elevators[i]->getFloor() - fn)){

                dist = elevators[i]->getFloor() - fn;
                ev = i;
            }
        }
    }



    return elevators[ev];
}


//return the elevator list size
int Controller::getElevatorCount(){
    return elevators.size();
}

//handle fire alarm pressed
void Controller::fireAlarmPressed(){
    for(int i = 0; i < elevators.size(); i++){
        elevators[i]->safeFloor();
        elevators[i]->changeMessage("Fire detected! " + elevators[i]->getMessage());
    }
}

//handle power out pressed
void Controller::powerOutPressed(){
    for(int i = 0; i < elevators.size(); i++){
        elevators[i]->safeFloor();
        elevators[i]->changeMessage("Power outage detected! " + elevators[i]->getMessage());
    }
}
