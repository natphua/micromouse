#include "micromouseserver.h"
#include <stack>
#include <vector>

void microMouseServer::studentAI()
{
    static std::string movements{};
    static char last_turn{};
    std::stack<char> stack;
    while (stack)
    {
        // if there is a joint, add possible turns to stack
        if (isWallForward() + isWallLeft() + isWallRight() == 1 or isWallForward() + isWallLeft() + isWallRight() == 0)
        {
            if (!isWallRight())
            {
                stack.push('R');
            }
            if (!isWallLeft())
            {
                stack.push('L');
            }
            if (!isWallForward()) // maybe delete this
            {
                stack.push('F');
            }
        }

        // setting next path to take (right or left); forward is default
        char next{stack.top};
        switch (next)
        {
            case 'R':
                turnRight();
                last_turn = 'R';
            case 'L':
                turnLeft();
                last_turn = 'L';
        }
        stack.pop();

        moveForward();
        movements += "F";

        // unfinished
        // add backtracking next and also finish condition

    }
}

// issue: if I want to track visited, how will I record turns without x, y coords?
// - try to backtrack using var movements?

// depth first search algorithm using stacks (FILO)




/*
 * Unislanded solution:
 *
void microMouseServer::studentAI()
{
    static std::string movements{}; //tracks past movements
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
*/
