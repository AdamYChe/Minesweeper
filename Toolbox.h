/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include <array>
#include <vector>
#ifndef MINESWEEPER_TOOLBOX_H
#define MINESWEEPER_TOOLBOX_H

//Declare the Toolbox Class
class Toolbox {

public:

    //Declare RenderWindow Object which will be used to display the Minesweeper board
    sf::RenderWindow window;

    //Declare pointers to Buttons and Gamestate Objects, which will handle Button functionality and the game logic
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    Button* testButton3;

    //Define the getInstance() function for a Toolbox singleton, that will be able to be called across classes
    static Toolbox& getInstance() {
        static Toolbox toolboxInstance;
        return toolboxInstance;
    }

    //Declare the gameLoop() function that will update the game when the user has taken actions
    int gameLoop();

    //Declare Texture objects for the tiles
    sf::Texture tileHidden;
    sf::Texture tileRevealed;

    //Declare Texture objects for the flags and mines
    sf::Texture flag;
    sf::Texture mine;

    //Declare Texture objects for the mine count around each tile
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Texture four;
    sf::Texture five;
    sf::Texture six;
    sf::Texture seven;
    sf::Texture eight;

    //Declare Texture objects for the reset game face
    sf::Texture happy;
    sf::Texture win;
    sf::Texture lose;

    //Declare Texture object for the flag count display
    sf::Texture digits;

    //Declare Texture object for the debug button
    sf::Texture debug;

    //Declare Texture object for the test buttons
    sf::Texture testOne;
    sf::Texture testTwo;
    sf::Texture testThree;

    //Declare a 2D vector of booleans that handles whether there are mines at certain board coordinates
    std::vector<std::vector<bool>> board;

    //Declare variable that checks if the game is in debug mode
    bool isDebugMode;

    //Need to override the default constructor as we are dealing with dynamic memory
    ~Toolbox();

private:

    //Declare the Toolbox() constructor, that will be used by the getInstance() singleton method
    Toolbox();

};


#endif //MINESWEEPER_TOOLBOX_H
