/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include <SFML/Graphics.hpp>
#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include <array>

//Declare the Tile class
class Tile {
public:

    //Declare an enumeration that gives the State of a specific Tile
    enum State{ REVEALED, HIDDEN, FLAGGED, EXPLODED };

    //Tile constructor
    Tile(sf::Vector2f position);

    //Tile class getters
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();

    //Tile class setters
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);\

    //Define methods that update the state of a tile given the user's click type and the State of the tile already
    void onClickLeft();
    void onClickRight();

    //Draws the desired sprite of the tile to the window
    void draw();

protected:

    //Declare the function to reveal the neighbors of a specific Tile
    void revealNeighbors();

private:
    //Declare private variables for the neighbors of a Tile, the location of a Tile on the screen, the State, and the number of mines surrounding a Tile
    std::array<Tile*, 8> neighbors;
    sf::Vector2f location;
    State state;
    int surroundingMines;
};


#endif //MINESWEEPER_TILE_H
