#include <SFML/Graphics.hpp>
#include "grid.h"
#include "block.h"

class Game {
private: 
    Grid grid;
    // current block
    Block block;
    int blockX = 5;
    int blockY = 5;

    bool checkNextMoveCollision(Grid grid, Block block, int x, int y);
    bool checkRotationCollision(Grid grid, Block block, int x, int y);
    void shiftAllRows(Grid* grid, int row);
    void updateGrid(Grid* grid, Block block, int x, int y);
    bool checkCollision(Grid grid, Block block, int x, int y);
    void drawGameState(Grid grid, Block block, int x, int y, sf::RenderWindow* window);

public:
    Game() { }
    Game(BlockType _type): block(_type) { }

    void createNewBlock();

    void play();
};