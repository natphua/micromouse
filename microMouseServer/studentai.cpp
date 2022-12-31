// iterative depth first search

#include "micromouseserver.h"
#include <stack>
#include <vector>
using namespace std;


static int dir_moved{0};

// 0 - forward, 1 - right, 2 - down, 3 - left
static int orientation = 0;

// [orientation][direction moving towards]
// lookup table for movements w/ orientation
// 0 - north, 1 - east, 2 - south, 3 - west
static int xKey[4][4] = {{0, 1, 0, -1}, {1, 0, -1, 0}, {0, -1, 0, 1}, {-1, 0, 1, 0}};
static int yKey[4][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}, {-1, 0, 1, 0}, {0, -1, 0, 1}};

// setting all values in visited to false bc none have been visited yet
static int visited[20][20] = {{false}};


// checks whether the mouse should move to that cell
bool isCellValid(int vis[20][20], int xpos, int ypos)
{
    // if cell is out of bounds or already visited, return false
    if (xpos<0 || ypos<0 || xpos>20 || ypos>20 || !vis[xpos][ypos])
    {
        return false;
    }
    return true;
}


void microMouseServer::studentAI()
{
    static stack <pair<int, int>> st;
    static int xpos, ypos, xnext, ynext;
    static string moves;
    static pair<int, int> last;

    while (!st.empty()) // while stack is not empty
    {
        if (moves.size() > 6) //making sure index is not out of range
        {
            if (moves.substr(moves.size() - 6) == "RFRFRF") //checking if past turns went around a 2x2 box
            {
                foundFinish();
                break;
            }
        }

        // current coords
        xpos += xKey[orientation][dir_moved];
        ypos += yKey[orientation][dir_moved];

        // next path/turn to take
        pair<int, int> next = st.top();
        xnext = next.first;
        ynext = next.second;


        // moving to next cell
        if (xnext < xpos)
        {
            // unfinished
            // would use switch function to choose movements depending on orientation
            // would also record turns in variable moves
        }
        if (ynext < ypos)
        {

        }
        if (ynext < ypos)
        {

        }

        st.pop();

        moveForward();
        moves += "F";

        visited[xpos][ypos] = true; // marking cell as visited

        // adding possible paths/turns to stack
        if (!isWallRight() && isCellValid(visited, xKey[orientation][1], yKey[orientation][1]) ) // right
        {
            st.push({xKey[orientation][1], yKey[orientation][1]});
        }
        if (!isWallForward() && isCellValid(visited, xKey[orientation][0], yKey[orientation][0])) // up
        {
            st.push({xKey[orientation][0], yKey[orientation][0]});
        }
        if (!isWallLeft() && isCellValid(visited, xKey[orientation][3], yKey[orientation][3])) // left
        {
            st.push({xKey[orientation][3], yKey[orientation][3]});
        }
        else // down (backwards)
        {
            st.push({xKey[orientation][2], yKey[orientation][2]});
        }

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
    while (isWallForward()) //if there is a front wall, turn down
    {
        turnLeft();
        movements += "L";
    }
}
*/
