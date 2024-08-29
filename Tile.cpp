/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include "Tile.h"
#include "Toolbox.h"
#include "minesweeper.h"

//Define the constructor for a Tile that sets the location and sets the initial State to HIDDEN
Tile::Tile(sf::Vector2f position) {
    location = position;
    state = HIDDEN;
}

//Returns the location of a Tile
sf::Vector2f Tile::getLocation() {
    return location;
}

//Returns the State of a Tile
Tile::State Tile::getState() {
    return state;
}

//Returns the array of Tile pointers that are the neighbors of the current Tile
std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}

//Sets the State given a _state parameter
void Tile::setState(Tile::State _state) {
    state = _state;
}

//Sets the neighbors of a Tile by setting them equal to the _neighbors
//Also sets the count of surrounding mines by checking if each neighbor is a mine or not
void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    surroundingMines = 0;

    for(int i = 0; i < 8; ++i) {
        neighbors.at(i) = _neighbors.at(i);
        if(neighbors.at(i) != nullptr && Toolbox::getInstance().board.at((int) neighbors.at(i)->location.y / 32).at((int) neighbors.at(i)->location.x / 32)) {
            surroundingMines++;
        }
    }
}

//Draws the Tile to the screen
void Tile::draw() {
    Toolbox& toolbox = Toolbox::getInstance();

    //Set sprites that are at the designated location of the Tile
    sf::Sprite displayTile;
    sf::Sprite displayModifier;
    displayTile.setPosition(getLocation().x, getLocation().y);
    displayModifier.setPosition(getLocation().x, getLocation().y);

    //If the Tile is FLAGGED, and is in debug mode, and is a mine, draws the mine to the screen rather than the flag
    if(state == FLAGGED && getDebugMode() && toolbox.board.at((int) location.y / 32).at((int) location.x / 32)) {
        displayTile.setTexture(toolbox.tileHidden);
        displayModifier.setTexture(toolbox.mine);
        toolbox.window.draw(displayTile);
        toolbox.window.draw(displayModifier);
    }

    //Draws the flag to the screen if the Tile is FLAGGED
    else if(state == FLAGGED) {
        displayTile.setTexture(toolbox.tileHidden);
        displayModifier.setTexture(toolbox.flag);
        toolbox.window.draw(displayTile);
        toolbox.window.draw(displayModifier);
    }

    //If the Tile is HIDDEN, and is in debug mode, and is a mine, draws the mine to the screen rather than the hidden tile
    if(state == HIDDEN && getDebugMode() && toolbox.board.at((int) location.y / 32).at((int) location.x / 32)) {
        displayTile.setTexture(toolbox.tileHidden);
        displayModifier.setTexture(toolbox.mine);
        toolbox.window.draw(displayTile);
        toolbox.window.draw(displayModifier);
    }

    //If the Tile is HIDDEN, draws the hidden tile to the screen
    else if(state == HIDDEN) {
        displayTile.setTexture(toolbox.tileHidden);
        toolbox.window.draw(displayTile);
    }

    //If the Tile is REVEALED, draws the revealed tile to the screen along with the number corresponding to the amount of mines surrounding the Tile
    if(state == REVEALED) {
        displayTile.setTexture(toolbox.tileRevealed);
        toolbox.window.draw(displayTile);
        if(surroundingMines == 1) {
            displayModifier.setTexture(toolbox.one);
        }
        else if(surroundingMines == 2) {
            displayModifier.setTexture(toolbox.two);
        }
        else if(surroundingMines == 3) {
            displayModifier.setTexture(toolbox.three);
        }
        else if(surroundingMines == 4) {
            displayModifier.setTexture(toolbox.four);
        }
        else if(surroundingMines == 5) {
            displayModifier.setTexture(toolbox.five);
        }
        else if(surroundingMines == 6) {
            displayModifier.setTexture(toolbox.six);
        }
        else if(surroundingMines == 7) {
            displayModifier.setTexture(toolbox.seven);
        }
        else if(surroundingMines == 8) {
            displayModifier.setTexture(toolbox.eight);
        }
        toolbox.window.draw(displayModifier);
    }

    //If the Tile is EXPLODED, displays th erevealed tile along with the mine
    if(state == EXPLODED) {
        displayTile.setTexture(toolbox.tileRevealed);
        displayModifier.setTexture(toolbox.mine);
        toolbox.window.draw(displayTile);
        toolbox.window.draw(displayModifier);
    }

}

//If the Tile is HIDDEN, either reveals a non-mine tile or sets a mine tile to EXPLODED
void Tile::onClickLeft() {
    Toolbox& toolbox = Toolbox::getInstance();
    int xCoord = (int) location.x / 32;
    int yCoord = (int) location.y / 32;

    if(state == HIDDEN) {
        if(toolbox.board.at(yCoord).at(xCoord)) {
            state = EXPLODED;
        }
        else {
            revealNeighbors();
        }
    }
}

//If the Tile is HIDDEN or FLAGGED, switches to FLAGGED and HIDDEN, respectively
void Tile::onClickRight() {
    if(state == HIDDEN) {
        state = FLAGGED;
    }
    else if(state == FLAGGED) {
        state = HIDDEN;
    }
}

//Reveals all neighbors by recursively calling the revealNeighbors() function across all neighbors of a Tile
//If the neighbor Tile exists on the board, and its state is HIDDEN, and is not a mine, call revealNeighbors
//If the current Tile is not a Mine, reveal it
void Tile::revealNeighbors() {
    if(!Toolbox::getInstance().board.at((int) location.y / 32).at((int) location.x / 32)) {
        state = REVEALED;
    }

    if(surroundingMines == 0) {

        for(auto& tile : getNeighbors()) {
            if(tile != nullptr
               && tile->state == HIDDEN
               && !Toolbox::getInstance().board.at((int) location.y / 32).at((int) location.x / 32)
                    ) {
                tile->revealNeighbors();
            }
        }
    }
}
