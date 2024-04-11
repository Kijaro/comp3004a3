#include "floor.h"

Floor::Floor(){
    floorNum = Floor::nextFloorNum;
    nextFloorNum++;
    upPressed = false;
    downPressed = false;
}

//get the floor number
int Floor::getFloorNum(){
    return floorNum;
}

//get if up pressed
bool Floor::getUpPressed(){
    return upPressed;
}

//toggle up pressed
void Floor::toggleUpPressed(){
    if(upPressed){
        upPressed = false;
    }
    else{
        upPressed = true;
    }
}

//get down pressed
bool Floor::getDownPressed(){
    return downPressed;
}

//toggle down pressed
void Floor::toggleDownPressed(){
    if(downPressed){
        downPressed = false;
    }
    else{
        downPressed = true;
    }
}
