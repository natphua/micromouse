#include "micromouseserver.h"
#include <stack>
#include <string>
using namespace std;


bool isCellValid(int visited[20][20], int row, int col)
{
    // cell is out of bounds, already visited, or on a wall
    if (row<0 || col<0 || row>20 || col>20 || visited[row][col] != 0)
    {
        return false;
    }
    return true;
}


void microMouseServer::studentAI()
{
    static string movements, orientation;
    static int row, col;
    static int visited[20][20]; // 1 for visited, 0 for not visited, 9 for wall
    static stack <pair <int, int>> st;
    st.push({0, 0}); // starting point
    static pair<int, int> last = {0, 0};
    static int last_row{last.first};
    static int last_col{last.second};
    orientation = "forward";

    // setting all values in visited to 0 bc none have been visited yet; will add walls later
    for (auto i=0; i<20; i++)
    {
        for (auto j=0; j<20; j++)
        {
            visited[i][j] = 0;
        }
    }

    while (!st.empty()) // while stack is not empty
    {
        if (movements.size() > 6) //making sure index is not out of range
        {
            if (movements.substr(movements.size() - 6) == "LFLFLF") //checking if past turns went around a 2x2 box
            {
                foundFinish();
                break;
            }
        }

        pair<int, int> current = st.top;
        st.pop();
        row = current.first;
        col = current.second;

        if (isCellValid(visited, row, col))
        {
            // moving to cell --> keep track of orientations to decide which way to move
            // always moving forward! i.e. if want to move backwards then just turn twice
            if (orientation == "forward")
            {
                if (row < last_row)
                {
                    turnLeft();
                    turnLeft();
                    movements += "LL";
                    orientation = "back";
                }
                if (col > last_col)
                {
                    turnRight();
                    movements += "R";
                    orientation = "right";
                }
                if (col < last_col)
                {
                    turnLeft();
                    movements += "L";
                    orientation = "left";
                }
                if (isWallForward())
                {
                    visited[row+1][col] = 9;
                }
                if (isWallRight())
                {
                    visited[row][col+1] = 9;
                }
                if (isWallLeft())
                {
                    visited[row][col-1] = 9;
                }
            }
            else if (orientation == "right")
            {
                if (row < last_row)
                {
                    turnRight();
                    movements += "R";
                    orientation = "back";
                }
                if (col < last_col)
                {
                    turnLeft();
                    turnLeft();
                    movements += "LL";
                    orientation = "left";
                }
                if (row > last_row)
                {
                    turnLeft();
                    movements += "L";
                    orientation = "forward";
                }
                if (isWallForward())
                {
                    visited[row][col+1] = 9;
                }
                if (isWallRight())
                {
                    visited[row-1][col] = 9;
                }
                if (isWallLeft())
                {
                    visited[row+1][col] = 9;
                }
            }
            else if (orientation == "left")
            {
                if (row < last_row)
                {
                    turnLeft();
                    movements += "L";
                    orientation = "back";
                }
                if (col > last_col)
                {
                    turnLeft();
                    turnLeft();
                    movements += "LL";
                    orientation = "right";
                }
                if (row > last_row)
                {
                    turnRight();
                    movements += "R";
                    orientation = "forward";
                }
                if (isWallForward())
                {
                    visited[row][col-1] = 9;
                }
                if (isWallRight())
                {
                    visited[row+1][col] = 9;
                }
                if (isWallLeft())
                {
                    visited[row-1][col] = 9;
                }
            }
            else if (orientation == "back")
            {
                if (row > last_row)
                {
                    turnLeft();
                    turnLeft();
                    movements += "LL";
                    orientation = "forward";
                }
                if (col > last_col)
                {
                    turnLeft();
                    movements += "L";
                    orientation = "right";
                }
                if (col < last_col)
                {
                    turnRight();
                    movements += "R";
                    orientation = "left";
                }
            }
            moveForward();
            movements += "F";
            if (isWallForward())
            {
                visited[row-1][col] = 9;
            }
            if (isWallRight())
            {
                visited[row][col-1] = 9;
            }
            if (isWallLeft())
            {
                visited[row][col+1] = 9;
            }
        }

        visited[row][col] = 1; // marking cell as visited

        // adding all directions to stack
        st.push({row+1, col});
        st.push({row, col+1});
        st.push({row, col-1});
        st.push({row-1, col});

        last = current;
        last_row = row;
        last_col = col;
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
