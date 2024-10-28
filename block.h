#pragma once
#include <vector>

using namespace std;

enum BlockType {
    SL, // straight line
    SQ, // square
    LL, // left L
    RL, // right L
    S,  // S
    MS  // mirrored S
};

class Block {
public:
    Block() { 
        rotationAngle = 0; 
    }
    Block(BlockType _type): type(_type), rotationAngle(0) {}

    // Get coordinates relative to rotation center.
    vector< vector<int> > getRelativeCoordinates();
    void rotateLeft();
    void rotateRight();

private:
    BlockType type;
    // Values 0-3.
    int rotationAngle;
};

