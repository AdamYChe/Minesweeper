/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include "Tile.h"
#include <vector>
#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H

//Declares the GameState class
class GameState {
public:

    //Defines the enumeration to get the PlayStatus
    enum PlayStatus{ WIN, LOSS, PLAYING };

    //Declare the constructors for GameState, one which takes in the dimensions and number of mines of the board,
    //and the other which sets the board from a file
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);

    //Declare functions to get the flag and mine count, respectively
    int getFlagCount();
    int getMineCount();

    //Declare a function that returns the tile at a designated coordinate
    Tile* getTile(int x, int y);

    //Returns the current PlayStatus
    PlayStatus getPlayStatus();

    //Sets the current PlayStatus
    void setPlayStatus(PlayStatus _status);

    //Overrides the default destructor in order to delete dynamic memory
    ~GameState();
private:

    //Declare variables for the dimensions, mine count, play status, and the board of tiles
    sf::Vector2i dimensions;
    int numberOfMines;
    PlayStatus status;
    std::vector<std::vector<Tile*>> tiles;

};


#endif //MINESWEEPER_GAMESTATE_H
