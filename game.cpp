#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "game.h"

int getRandomBlockInd() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 5);

    return dist6(rng);
}

void Game::createNewBlock() {
    int randomBlock = getRandomBlockInd();
    this->block = Block((BlockType) randomBlock);
    this->blockX = 5;
    this->blockY = 5;
}

void Game::drawGameState(Grid grid, Block block, int x, int y, sf::RenderWindow* window) {
    window->clear(sf::Color::Black);

    // Display frame
    sf::RectangleShape frame(sf::Vector2f(10 * grid.N, 10 * grid.M));
    frame.setPosition(sf::Vector2f(5, 5));
    frame.setOutlineThickness(5);
    frame.setOutlineColor(sf::Color::Green);
    frame.setFillColor(sf::Color::Black);
    window->draw(frame);
    
    // Display Grid state
    for (int i = 0; i < grid.M; i++) {
        for (int j = 0; j < grid.N; j++) {
            if (grid.grid[i][j]) {
                sf::RectangleShape rectangle(sf::Vector2f(10, 10));

                rectangle.setPosition(sf::Vector2f(10 * j + 5, 10 * i + 5));
                
                window->draw(rectangle);
            }
        }
    }

    // Display current block
    for (vector<int> coordinates : block.getRelativeCoordinates()) {

        sf::RectangleShape rectangle(sf::Vector2f(10, 10));

        rectangle.setPosition(sf::Vector2f(10 * (x + coordinates[0]) + 5, 10 * (y + coordinates[1]) + 5));
        
        window->draw(rectangle);
    }

    window->display();
}

bool Game::checkCollision(Grid grid, Block block, int x, int y) {
    for (vector<int> coordinates : block.getRelativeCoordinates()) {
        int nextX = x + coordinates[0], nextY = y + coordinates[1];

        if (nextX < 0 || nextX >= grid.N || nextY < 0 || nextY >= grid.M) {
            return true;
        }

        if (grid.grid[nextY][nextX]) {
            return true;
        }
    }

    return false;
}

bool Game::checkNextMoveCollision(Grid grid, Block block, int x, int y) {
    return checkCollision(grid, block, x, y + 1);
}

bool Game::checkRotationCollision(Grid grid, Block block, int x, int y) {
    block.rotateLeft();
    bool hasCollision = checkCollision(grid, block, x, y);
    block.rotateRight();
    
    return hasCollision;
}


void Game::shiftAllRows(Grid* grid, int row) {
    for (int i = row - 1; i >= 0; i--) {
        for (int j = 0; j < grid->N; j++) {
            grid->grid[i + 1][j] = grid->grid[i][j];
        }
    }
}

// todo if passing grid by value it doesn't work - why?
void Game::updateGrid(Grid* grid, Block block, int x, int y) {
    for (vector<int> coordinates : block.getRelativeCoordinates()) {
        grid->grid[y + coordinates[1]][x + coordinates[0]] = true;
    }

    int i = grid->M - 1;
    while (i > 0) {
        bool rowFilled = true;

        for (int j = 0; j < grid->N; j++) {
            if (!grid->grid[i][j]) {
                rowFilled = false;
                break;
            }
        }

        if (rowFilled) {
            shiftAllRows(grid, i);
        } else {
            i--;
        }
    }
}

void Game::play() {
    bool stop = false;
    
    sf::RenderWindow window(sf::VideoMode(110, 260), "My window");

    while (window.isOpen())
    {
        if (checkCollision(grid, block, this->blockX, this->blockY)) {
            window.close();
            continue;
        } 

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Left && event.type == sf::Event::KeyPressed) {
                if (!checkCollision(grid, block, this->blockX - 1, this->blockY)) {
                    this->blockX--;
                }
            } else if (event.key.code == sf::Keyboard::Right && event.type == sf::Event::KeyPressed) {
                if (!checkCollision(grid, block, this->blockX + 1, this->blockY)) {
                    this->blockX++;
                }
            } else if (event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyPressed) {
                if (!checkRotationCollision(grid, block, this->blockX, this->blockY)) {
                    this->block.rotateLeft();
                }
            }
        }

        if(checkNextMoveCollision(grid, block, this->blockX, this->blockY)) {
            updateGrid(&grid, block, this->blockX, this->blockY);

            drawGameState(grid, block, this->blockX, this->blockY, &window);

            this->createNewBlock();
            continue;
        }         
        
        this->blockY++;
        drawGameState(this->grid, block, this->blockX, this->blockY, &window);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
