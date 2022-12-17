#include "micromouseserver.h"

void microMouseServer::studentAI()
{
    static std::string movements{}; //variable that will track past movements
    moveForward();
    movements += "F";
    if (movements.size() > 6) //making sure index is not out of range
    {
        if (movements.substr(movements.size() - 6) == "LFLFLF") //checking if past turns went around a 2x2 box
        {
            foundFinish();
        }
    }
    if (!isWallRight()) //follows right wall
    {
        turnRight();
        movements += "R";
    }
    while (isWallForward()) //if there is a front wall, turn back
    {
        turnLeft();
        movements += "L";
    }
}
