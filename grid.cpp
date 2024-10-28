#include <iostream>
#include <vector>
#include "grid.h"

using namespace std;

void Grid::printGrid()
{
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // cout << grid[i][j] ? "*" : "";
            if ((i % 2 == 0) && (j % 2 == 0)) {
                cout << "*";
            } else {
                cout << " ";
            }
        }

        cout << endl;
    }
}

bool Grid::checkCollision(int x, int y, vector< vector<int> > relativeCoordinates) {
    for (vector<int> coordinates : relativeCoordinates) {
        int xx = x + coordinates[0], yy = y + coordinates[1];
        if (grid[xx][yy]) {
            return true;
        }
    }

    return false;
}