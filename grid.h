#pragma once

#include <vector>

class Grid {
public:
    Grid() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = false;
            }
        }
    }

    static const int M = 25;
    static const int N = 10;
    
    void printGrid();
    bool checkCollision(int x, int y, std::vector< std::vector<int> > relativeCoordinates);

    bool grid[M][N];
};