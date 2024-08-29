/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include "GameState.h"
#include "Toolbox.h"
#include <fstream>
#include <random>
#include <iostream>

//Define the constructor that takes in a dimension and mine count parameter
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {

    //Set the private variables to parameters
    dimensions = _dimensions;
    numberOfMines = _numberOfMines;

    //Get the Toolbox class instance
    Toolbox& toolbox = Toolbox::getInstance();

    //Defines a new board with no mines initially
    toolbox.board.resize(0);
    for(int j = 0; j < dimensions.y; ++j) {
        toolbox.board.push_back(std::vector<bool>(dimensions.x));
        for(int k = 0; k < dimensions.x; ++k) {
            toolbox.board.at(j).at(k) = false;
        }
    }

    //Randomly generates a board with the desired number of mines on it
    for(int i = 0; i < numberOfMines; ++i) {
        bool isAlreadyMine = true;
        while(isAlreadyMine) {
            int randRow = rand() % dimensions.y;
            int randColumn = rand() % dimensions.x;
            if(!toolbox.board.at(randRow).at(randColumn)) {
                isAlreadyMine = false;
                toolbox.board.at(randRow).at(randColumn) = true;
            }
        }
    }

    //Generates the 2D vector of tiles given the board dimensions
    for(int j = 0; j < dimensions.y; ++j) {
        tiles.push_back(std::vector<Tile*>(dimensions.x));
        for(int k = 0; k < dimensions.x; ++k) {
            tiles.at(j).at(k) = new Tile(sf::Vector2f(k * 32, j * 32));
        }
    }

    //Sets the neighbors of each tile by checking if the neighboring tiles are on the board (if not, sets them to nullptr)
    for(int j = 0; j < dimensions.y; ++j) {
        for(int k = 0; k < dimensions.x; ++k) {
            tiles.at(j).at(k)->setNeighbors(
                    {
                        j - 1 < 0 || k - 1 < 0 ?                            nullptr : tiles.at(j - 1).at(k - 1),
                        j - 1 < 0 ?                                         nullptr : tiles.at(j - 1).at(k),
                        j - 1 < 0 || k + 1 >= dimensions.x ?                nullptr : tiles.at(j - 1).at(k + 1),
                        k - 1 < 0 ?                                         nullptr : tiles.at(j).at(k - 1),
                        k + 1 >= dimensions.x ?                             nullptr : tiles.at(j).at(k + 1),
                        j + 1 >= dimensions.y || k - 1 < 0 ?                nullptr : tiles.at(j + 1).at(k - 1),
                        j + 1 >= dimensions.y ?                             nullptr : tiles.at(j + 1).at(k),
                        j + 1 >= dimensions.y || k + 1 >= dimensions.x ?    nullptr : tiles.at(j + 1).at(k + 1)
                    }
                    );
        }
    }

    //Sets the status to PLAYING
    status = PLAYING;
}

//Defines the constructor for GameState given a filename
GameState::GameState(const char *filepath) {
    std::ifstream in(filepath);
    numberOfMines = 0;

    //Since we do not know the dimensions yet, we have this vector so we can determine dimensions
    std::vector<char> tempHolder;
    int rowCount = 1;

    //Reads in the file, while giving the row and column count
    char c;
    int prevSize = -1;
    while(in.get(c)) {
        if(c != '\n') {
            tempHolder.push_back(c);
            numberOfMines += c == '0' ? 0 : 1;
        }
        else if(prevSize != tempHolder.size()){
            rowCount++;
            prevSize = tempHolder.size();
        }
    }
    if(c == '\n') {
        rowCount--;
    }

    //Sets the dimensions of the board
    int columnCount = tempHolder.size() / rowCount;
    dimensions.x = columnCount;
    dimensions.y = rowCount;

    //Generates the board
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.board.resize(dimensions.y);
    for(auto& row : toolbox.board) {
        row.resize(dimensions.x);
    }

    //Sets board tiles to mines as desired from the file
    for(int j = 0; j < rowCount; ++j) {
        for(int k = 0; k < columnCount; ++k) {
            toolbox.board.at(j).at(k) = tempHolder.at(j * columnCount + k % columnCount) != '0';
        }
    }

    //Create the tiles vector given the dimensions
    for(int j = 0; j < dimensions.y; ++j) {
        tiles.push_back(std::vector<Tile*>(dimensions.x));
        for(int k = 0; k < dimensions.x; ++k) {
            tiles.at(j).at(k) = new Tile(sf::Vector2f(k * 32, j * 32));
        }
    }

    //Sets the neighbors of each tile by checking if the neighboring tiles are on the board (if not, sets them to nullptr)
    for(int j = 0; j < dimensions.y; ++j) {
        for(int k = 0; k < dimensions.x; ++k) {
            tiles.at(j).at(k)->setNeighbors(
                    {
                            j - 1 < 0 || k - 1 < 0 ?                            nullptr : tiles.at(j - 1).at(k - 1),
                            j - 1 < 0 ?                                         nullptr : tiles.at(j - 1).at(k),
                            j - 1 < 0 || k + 1 >= dimensions.x ?                nullptr : tiles.at(j - 1).at(k + 1),
                            k - 1 < 0 ?                                         nullptr : tiles.at(j).at(k - 1),
                            k + 1 >= dimensions.x ?                             nullptr : tiles.at(j).at(k + 1),
                            j + 1 >= dimensions.y || k - 1 < 0 ?                nullptr : tiles.at(j + 1).at(k - 1),
                            j + 1 >= dimensions.y ?                             nullptr : tiles.at(j + 1).at(k),
                            j + 1 >= dimensions.y || k + 1 >= dimensions.x ?    nullptr : tiles.at(j + 1).at(k + 1)
                    }
            );
        }
    }

    //Set the play status to PLAYING
    status = PLAYING;
}

//Returns the current PlayStatus
GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}

//Sets the current PlayStatus given the _status parameter
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    status = _status;
}

//Returns the desired Tile pointer at the given location
Tile* GameState::getTile(int x, int y) {
    return tiles.at(y).at(x);
}

//Returns the number of mines
int GameState::getMineCount() {
    return numberOfMines;
}

//Returns the number of flags, by iterating through tiles and incrementing the flag count if a tile is FLAGGED
int GameState::getFlagCount() {
    int flagCount = 0;
    for(auto& row : tiles) {
        for(auto& tile : row) {
            if(tile->getState() == Tile::FLAGGED) {
                flagCount++;
            }
        }
    }

    return flagCount;
}

//Destructor that goes through the 2D vector of tile pointers, deleting each one
GameState::~GameState() {
    for(auto row : tiles) {
        for(auto tile : row) {
            delete tile;
        }
    }
}
