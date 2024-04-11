#ifndef FLOOR_H
#define FLOOR_H
#include <vector>

class Floor
{
private:
    int floorNum;
    static int nextFloorNum;
    bool upPressed;
    bool downPressed;
public:
    Floor();
    int getFloorNum();
    bool getUpPressed();
    void toggleUpPressed();
    bool getDownPressed();
    void toggleDownPressed();


};

#endif // FLOOR_H
