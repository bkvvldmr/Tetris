#include <vector>
#include <stdexcept>

#include "block.h"

using namespace std;

// You win the game if you get OutOfMemory (or whatever it's called in c++ world) error because I'm lazy to create const vectors.
vector< vector<int> > Block::getRelativeCoordinates() {
    switch (this->type)
    {
        case SL: 
            switch (rotationAngle)
            {
            case 0:
                return { {0, 0}, {-1, 0}, {1, 0}, {2, 0} };
            case 1: 
                return { {0, 0}, {0, 1}, {0, -1}, {0, -2} };
            case 2: 
                return { {0, 0}, {-1, 0}, {-2, 0}, {1, 0} };
            case 3: 
                return { {0, 0}, {0, 1}, {0, 2}, {0, -1} };
            default:
                throw invalid_argument("Only 0-3 angle values supported");
            }
            
        case SQ:
            return { {0, 0}, {1, 0}, {0, 1}, {1, 1} };

        case LL:
            switch (rotationAngle)
            {
            case 0:
                return { {0, 0}, {-1, 0}, {-2, 0}, {0, 1} };
            case 1: 
                return { {0, 0}, {1, 0}, {0, 1}, {0, 2} };
            case 2: 
                return { {0, 0}, {1, 0}, {2, 0}, {0, -1} };
            case 3: 
                return { {0, 0}, {-1, 0}, {0, -1}, {0, -2} };
            default:
                throw invalid_argument("Only 0-3 angle values supported");
            }

        case RL:
            switch (rotationAngle)
            {
            case 0:
                return { {0, 0}, {0, -1}, {-1, 0}, {-2, 0} };
            case 1: 
                return { {0, 0}, {-1, 0}, {0, 1}, {0, 2} };
            case 2: 
                return { {0, 0}, {0, 1}, {1, 0}, {2, 0} };
            case 3: 
                return { {0, 0}, {1, 0}, {0, -1}, {0, -2} };
            default:
                throw invalid_argument("Only 0-3 angle values supported");
            }

        case S:
            switch (rotationAngle)
            {
            case 0:
                return { {0, 0}, {0, 1}, {1, 0}, {1, -1} };
            case 1: 
                return { {0, 0}, {1, 0}, {0, -1}, {-1, -1} };
            case 2: 
                return { {0, 0}, {-1, 0}, {-1, 1}, {0, -1} };
            case 3: 
                return { {0, 0}, {-1, 0}, {0, 1}, {1, 1} };
            default:
                throw invalid_argument("Only 0-3 angle values supported");
            }

        case MS:
            switch (rotationAngle)
            {
            case 0:
                return { {0, 0}, {1, 0}, {0, -1}, {1, 1} };
            case 1: 
                return { {0, 0}, {-1, 0}, {0, -1}, {1, -1} };
            case 2: 
                return { {0, 0}, {-1, 0}, {0, 1}, {-1, -1} };
            case 3: 
                return { {0, 0}, {0, 1}, {-1, 1}, {1, 0} };
            default:
                throw invalid_argument("Only 0-3 angle values supported");
            }
    }
}

void Block::rotateLeft() {
    if (--rotationAngle < 0) {
        rotationAngle = 3;
    }
}

void Block::rotateRight() {
    if (++rotationAngle > 3) {
        rotationAngle = 0;
    }
}