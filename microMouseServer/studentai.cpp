#include "micromouseserver.h"
#include <stack>
#include <string>
using namespace std;


bool isCellValid(int maze[20][20], bool visited[20][20], int row, int col)
{
    // cell is out of bounds, already visited, or on a wall
    if (row<0 || col<0 || row>20 || col>20 || visited[row][col] || maze[row][col] == '1')
    {
        return false;
    }
    return true;
}

void moveToCell(pair<int, int> current, pair<int, int> next)
{
    if (next.first > current.first)
    {
        moveForward(); // will fix function calls later
    }
    if (next.second > current.second)
    {
        turnRight();
    }
    else if (next.second < current.second)
    {
        turnLeft();
    }
}


void microMouseServer::studentAI()
{
    static string movements{}; // tracking past movements
    static int maze[20][20], row, col;
    static bool visited[20][20]; // 2d array matching maze to record whether visited or not
    static stack <pair <int, int>> st;
    st.push({0, 0}); // starting point

    // setting all values in visited to false bc none have been visited yet
    for (auto i=0; i<20; i++)
    {
        for (auto j=0; j<20; j++)
        {
            visited[i][j] = false;
        }
    }

    while (st) // while stack is not empty
    {
        pair<int, int> current = st.top;
        st.pop();
        row = current.first;
        col = current.second;

        // marking surroundings and saving to maze record
        if (isWallForward())
        {
            // ISSUE: orientation of mouse can confuse location of walls using +1 -1 for right/left/forward
        }


        if (isCellValid(maze, visited, row, col))
        {
            continue;
        }

        moveToCell(current, next); // need to sort out diff between current and next with stack
        visited[row][col] = true;

        st.push({row+1, col}); // go forward
        st.push({row, col-1}); // go left
        st.push({row, col+1}); // go right

        // unfinished; need to add backtracking, fix maze array, and sort out functions

    }
}





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
