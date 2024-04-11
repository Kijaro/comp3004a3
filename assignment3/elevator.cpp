#include "elevator.h"

Elevator::Elevator(){
    id = Elevator::nextId;
    nextId++;
    floorNum = 1;
    message = "Elevator is working correctly";
    weight = 0;
    doorBlocked = false;
    doorOpenTime = 10;
}

//open the door
void Elevator::openDoor(){
    qInfo("elevator %d opens its door for %d seconds", id, doorOpenTime);
    doorOpenTime = 10;
}

//close the door
void Elevator::closeDoor() {
    qInfo("Elevator %d closing doors", id);
}

//ring the bell
void Elevator::ringBell(){
    qInfo("Bell Rung in Elevator %d", id);
}


//move the elevator to a floor id
void Elevator::travelTo(int fn){
    floorNum = fn;
    removeChecked(fn);
    qInfo("");
    qInfo("Elevator %d arrived at floor %d", id, floorNum);
    ringBell();
    openDoor();
    qInfo("Passengers unloading and loading...");
    if(doorBlocked) {
        qInfo("Elevator %d has a blocked door! Remove obstruction to continue.",id);
        qInfo("Elevator %d plays the warning message \"Elevator door is blocked, please remove obstruction\"", id);
        changeMessage("Elevator door is blocked, remove obstruction");
    } else{
        ringBell();
        closeDoor();
    }
    changeMessage("Elevator is working correctly");
}

//find the next floor in queue and do some error checking
int Elevator::getNextInQueue(){
    if(floorQueue.size() == 0){
        return 0;
    }else if(weight > 500){
        qInfo("Elevator %d is overloaded! Reduce weight to continue.",id);
        qInfo("Elevator %d plays the warning message \"Elevator is overloaded, please reduce load\"", id);
        changeMessage("Elevator is overloaded, reduce weight");
    }else if(doorBlocked){
        qInfo("Elevator %d has a blocked door! Remove obstruction to continue.",id);
        qInfo("Elevator %d plays the warning message \"Elevator door is blocked, please remove obstruction\"", id);
        changeMessage("Elevator door is blocked, remove obstruction");
    }else{
        int next = floorQueue.front();
        floorQueue.pop();
        return next;
    }
    return 0;
}

//add to queue
void Elevator::addToQueue(int f){
    floorQueue.push(f);
}

//return id
int Elevator::getId(){
    return id;
}

//get floor num
int Elevator::getFloor(){
    return floorNum;
}

//get queue size
int Elevator::getQueueSize(){
    return floorQueue.size();
}

//return the elevators message
QString Elevator::getMessage(){
    return message;
}

//change elevators message
void Elevator::changeMessage(QString m){
    message = m;
}

//travel to a safe floor
void Elevator::safeFloor(){
    floorQueue = std::queue<int>();
    checkedButtons = std::vector<int>();
    travelTo(1);
    qInfo("Elevator %d plays the warning message \"Emergency Alert! Please exit the elevator!\"", id);
    changeMessage("Emergency Alert! Please exit the elevator!");
}

//set the elevators weight
void Elevator::setWeight(int w){
    weight = w;
}

//get this elevators weight
int Elevator::getWeight(){
    return weight;
}

//toggle if the door is blocked
void Elevator::toggleDoorBlocked(){
    doorBlocked = !doorBlocked;
}

//get door blocked
bool Elevator::getDoorBlocked(){
    return doorBlocked;
}

//door open pressed
void Elevator::doorOpenPressed(){
    doorOpenTime += 5;
}

//door closed pressed
void Elevator::doorClosedPressed(){
    doorOpenTime -= 5;
    if(doorOpenTime <= 3){
        doorOpenTime = 3;
    }

}

//check if a button is checked
bool Elevator::checkIfButtonChecked(int b){
    for(int i = 0; i < checkedButtons.size(); i++){
        if(checkedButtons[i] == b) return true;
    }
    return false;
}

//add checked elevator
void Elevator::addChecked(int b){
    checkedButtons.push_back(b);
}

//removed the checked
void Elevator::removeChecked(int b){
    checkedButtons.erase(std::remove(checkedButtons.begin(), checkedButtons.end(), b), checkedButtons.end());
}

