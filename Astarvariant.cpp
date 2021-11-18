// A C++ Program to implement A* Search Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <cmath>
#include <cfloat>
#include <cstring>
#include <vector>
#include <stack>
#include <array>
#include <set>
#include "map.h"

using namespace std;

#define ROW 15
#define COL 19

int roboteaten = 0;
int prevLongestPath = 0;
int foodOnPath = 0;
int pathFound = 0;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
//typedef pair<double, pair<int, int> > pPair;

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    //printf("%d  %d \n", row, col);
    return (row >= 0) && (row < ROW) && (col >= 0)
        && (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int map[][COL], int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (map[row][col] == 0)
        return (true);
    else
        return (false);
}

// A Utility Function to check whether robot has eaten everything 
bool haseatenEverything(int eaten, int foodCount)
{
    if (eaten == foodCount)
        return (true);
    else
        return (false);
}

void cellsVisited(set<Pair> closedList) {
    for (set<pair<int, int> >::iterator it = closedList.begin(); it != closedList.end();)
    {
        cout << "closedList" << " " << "(" << it->first << "," << it->second << ")" << endl;
        ++it;
    }
}

// A Function that chooses the path with the most food
// Checks up, down, left and right until it hits a deadend
// Compares to find the highest g value (represents the most food on that path)
void aStarSearch(int(&map)[ROW][COL], Pair src, int eaten, int foodCount)
{
    // If the source is out of range
    if (isValid(src.first, src.second) == false) {
        printf("Source is invalid\n");
        return;
    }

    // Either the source is blocked
    if (isUnBlocked(map, src.first, src.second) == false) {
        printf("Source is blocked\n");
        return;
    }

    // Create a closed list 
    //set<pPair> closedList;

    int i = src.first;
    int j = src.second;

    /*
     Create an open list having information as-
     <i, j>
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
    set<Pair> openList;
    set<Pair> closedList;

    // Put the starting cell on the open list and set its
    // 'g' as 0
    openList.insert(make_pair(i, j));
    closedList.insert(make_pair(i, j));

    // Put the starting cell on the closed list
    /*closedList.insert(make_pair(0, make_pair(i, j)));*/

    while (haseatenEverything(eaten, foodCount) == false) {
        /*
    Generating all the 4 successor of this cell
            N
            |
            |
        W----Cell----E
            |
            |
            S
    Cell-->Popped Cell (i, j)
    N -->  North       (i-1, j)
    S -->  South       (i+1, j)
    E -->  East        (i, j+1)
    W -->  West        (i, j-1)*/

    //----------- 1st Successor (North) ------------
        int I;
        int J;
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;
        int largestg = 0;
        int g = 0;
        int g2 = 0;
        int g3 = 0;
        int g4 = 0;

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j) == true) {
            if (isUnBlocked(map, i - 1, j) == true) {
                I = i - 1;
                J = j;

                Pair closedListpair = make_pair(I, j);
                Pair key = closedListpair;
                bool pairPresent = false;
                while (map[I][J] == 0) {
                    if (closedList.find(key) != closedList.end()) {
                        pairPresent = true;
                    }

                    if (pairPresent == true) {
                        I -= 1;
                        key = make_pair(I, j);
                        pairPresent = false;
                    }
                    else {
                        up += 1;
                        I -= 1;
                        key = make_pair(I, j);
                    }
                }

                g += up;

                cout << "up:number of food" << " " << g << "\n";

                Pair successorDetailsNorth = make_pair(i - 1, j);

                key = successorDetailsNorth;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i - 1, j));
                }

                largestg = g;
                I = i;
                J = j;

            }
            else {

                cout << "blocked up" << "\n";
                Pair successorDetailsNorth = make_pair(i - 1, j);

                Pair key = successorDetailsNorth;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i - 1, j));
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j) == true) {
            if (isUnBlocked(map, i + 1, j) == true) {

                I = i + 1;
                J = j;

                Pair closedListpair = make_pair(I, j);
                Pair key = closedListpair;
                bool pairPresent = false;
                while (map[I][J] == 0) {
                    if (closedList.find(key) != closedList.end()) {
                        pairPresent = true;
                    }

                    if (pairPresent == true) {
                        I += 1;
                        key = make_pair(I, j);
                        pairPresent = false;
                    }
                    else {
                        down += 1;
                        I += 1;
                        key = make_pair(I, j);
                    }
                }

                g2 += down;

                cout << "down:number of food" << " " << g2 << "\n";

                Pair successorDetailsSouth = make_pair(i + 1, j);

                key = successorDetailsSouth;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i + 1, j));
                }

                if (g2 > largestg) {
                    largestg = g2;
                }

                I = i;
                J = j;
            }
            else {
                cout << "Blocked down" << "\n";
                Pair successorDetailsSouth = make_pair(i + 1, j);

                Pair key = successorDetailsSouth;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i + 1, j));
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j + 1) == true) {
            if (isUnBlocked(map, i, j + 1) == true) {
                I = i;
                J = j + 1;

                Pair closedListpair = make_pair(i, J);
                Pair key = closedListpair;
                bool pairPresent = false;
                while (map[I][J] == 0) {
                    if (closedList.find(key) != closedList.end()) {
                        pairPresent = true;
                    }

                    if (pairPresent == true) {
                        J += 1;
                        key = make_pair(i, J);
                        pairPresent = false;
                    }
                    else {
                        right += 1;
                        J += 1;
                        key = make_pair(i, J);
                    }
                }

                g3 += right;

                cout << "right:number of food" << " " << g3 << "\n";

                Pair successorDetailsEast = make_pair(i, j + 1);

                key = successorDetailsEast;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i, j + 1));
                }

                if (g3 > largestg) {
                    largestg = g3;
                }

                I = i;
                J = j;

            }
            else {
                cout << "Blocked right" << "\n";
                Pair successorDetailsEast = make_pair(i, j + 1);

                Pair key = successorDetailsEast;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i, j + 1));
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j - 1) == true) {
            if (isUnBlocked(map, i, j - 1) == true) {
                I = i;
                J = j - 1;

                Pair closedListpair = make_pair(i, J);
                Pair key = closedListpair;
                bool pairPresent = false;
                while (map[I][J] == 0) {
                    if (closedList.find(key) != closedList.end()) {
                        pairPresent = true;
                    }

                    if (pairPresent == true) {
                        J -= 1;
                        key = make_pair(i, J);
                        pairPresent = false;
                    }
                    else {
                        left += 1;
                        J -= 1;
                        key = make_pair(i, J);
                    }
                }

                g4 += left;

                cout << "left:number of food" << " " << g4 << "\n";

                Pair successorDetailsWest = make_pair(i, j - 1);
                key = successorDetailsWest;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i, j - 1));
                }

                if (g4 > largestg) {
                    largestg = g4;
                }

                I = i;
                J = j;

            }
            else {
                cout << "Blocked left" << "\n";
                Pair successorDetailsWest = make_pair(i, j - 1);

                Pair key = successorDetailsWest;
                bool vertexPresent = false;

                if (openList.find(key) != openList.end()) {
                    vertexPresent = true;
                }

                if (vertexPresent != true) {
                    openList.insert(make_pair(i, j - 1));
                }
            }
        }

        if (prevLongestPath == 1 && foodOnPath > 0) {
            closedList.insert(make_pair(i - 1, j));
            eaten += 1;
            roboteaten += 1;
            foodOnPath -= 1;

            if (foodOnPath == 0) {
                prevLongestPath = 0;
                pathFound = 0;
            }
            else {
                i = i - 1;
                pathFound = 1;
            }
        }
        else if (prevLongestPath == 2 && foodOnPath > 0) {
            closedList.insert(make_pair(i + 1, j));
            eaten += 1;
            roboteaten += 1;
            foodOnPath -= 1;

            if (foodOnPath == 0) {
                prevLongestPath = 0;
                pathFound = 0;
            }
            else {
                i = i + 1;
                pathFound = 1;
            }
        }

        else if (prevLongestPath == 3 && foodOnPath > 0) {
            closedList.insert(make_pair(i, j + 1));
            eaten += 1;
            roboteaten += 1;
            foodOnPath -= 1;

            if (foodOnPath == 0) {
                prevLongestPath = 0;
                pathFound = 0;
            }
            else {
                j = j + 1;
                pathFound = 1;
            }
        }
        else if (prevLongestPath == 4 && foodOnPath > 0) {
            closedList.insert(make_pair(i, j - 1));
            eaten += 1;
            roboteaten += 1;
            foodOnPath -= 1;

            if (foodOnPath == 0) {
                prevLongestPath = 0;
                pathFound = 0;
            }
            else {
                j = j - 1;
                pathFound = 1;
            }
        }

        if (largestg == g && pathFound == 0) {
            closedList.insert(make_pair(i - 1, j));
            i = i - 1;
            eaten += 1;
            roboteaten += 1;
            prevLongestPath = 1;
            foodOnPath = g;
        }
        else if (largestg == g2 && pathFound == 0) {
            closedList.insert(make_pair(i + 1, j));
            i = i + 1;
            eaten += 1;
            roboteaten += 1;
            prevLongestPath = 2;
            foodOnPath = g2;
        }
        else if (largestg == g3 && pathFound == 0) {
            closedList.insert(make_pair(i, j + 1));
            j = j + 1;
            eaten += 1;
            roboteaten += 1;
            prevLongestPath = 3;
            foodOnPath = g3;
        }
        else if (largestg == g4 && pathFound == 0) {
            closedList.insert(make_pair(i, j - 1));
            j = j - 1;
            eaten += 1;
            roboteaten += 1;
            prevLongestPath = 4;
            foodOnPath = g4;
        }

        cout << "pathfound" << prevLongestPath << "\n";

        if (haseatenEverything(eaten, foodCount)) {
            printf("openList size: %d \n", openList.size());
            printf("closedList size: %d \n", closedList.size());
            cellsVisited(closedList);
        }
    }
}

// Driver program to test above function
int main()
{
    /* Description of the Grid-
     1--> The cell is blocked
     0--> The cell is not blocked with food  */
    int i, j;
    int foodCount = 0;
    int eaten = 0;

    //Map imported from map.h

    // Source node
    Pair src = make_pair(1, 1);

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            //printf("%d ", map[i][j]);
            if (map[i][j] == 0) {
                foodCount += 1;
            }
        }
        //printf("\n");
    }

    aStarSearch(map, src, eaten, foodCount);
    // prints the number of food available on map
    //cout << "Food count " << foodCount << "\n";
    // prints the number of food the robot ate
    //cout << "eaten " << roboteaten;

    return (0);
}
