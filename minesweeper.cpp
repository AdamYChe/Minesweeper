/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include "minesweeper.h"
#include <iostream>

//Defines the function that switches between debug modes
void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.isDebugMode = !toolbox.isDebugMode;
}

//Returns the current debug mode of the game
bool getDebugMode() {
    return Toolbox::getInstance().isDebugMode;
}

//Restarts the game by deleting the previous GameState and creating a new one that is set with the correct size
//Also toggles the debug mode to off
void restart() {
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;

    toolbox.gameState = new GameState(sf::Vector2i(25, 16));
    if(getDebugMode()) { toggleDebugMode(); }
}

//Renders all Sprites to the window
void render() {
    Toolbox& toolbox = Toolbox::getInstance();

    //Calculates the flag counter in the bottom corner
    int flagsAvailable = toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount();
    bool isNegative = flagsAvailable < 0;
    if(isNegative) {
        flagsAvailable *= -1;
    }

    //Finds each digit
    int firstDigit = flagsAvailable % 10;
    int secondDigit = (flagsAvailable / 10) % 10;
    int thirdDigit = flagsAvailable / 100;

    sf::Sprite first(toolbox.digits);
    sf::Sprite second(toolbox.digits);
    sf::Sprite third(toolbox.digits);

    //Finds the location of the sprite on the Texture for digits
    sf::IntRect zero = sf::IntRect(0, 0, 21, 32);
    sf::IntRect one = sf::IntRect(21, 0, 21, 32);
    sf::IntRect two = sf::IntRect(42, 0, 21, 32);
    sf::IntRect three = sf::IntRect(63, 0, 21, 32);
    sf::IntRect four = sf::IntRect(84, 0, 21, 32);
    sf::IntRect five = sf::IntRect(105, 0, 21, 32);
    sf::IntRect six = sf::IntRect(126, 0, 21, 32);
    sf::IntRect seven = sf::IntRect(147, 0, 21, 32);
    sf::IntRect eight = sf::IntRect(168, 0, 21, 32);
    sf::IntRect nine = sf::IntRect(189, 0, 21, 32);
    sf::IntRect neg = sf::IntRect(210, 0, 21, 32);

    //Sets the sprite for the first digit
    if(firstDigit == 0) {first.setTextureRect(zero);}
    else if(firstDigit == 1) {first.setTextureRect(one);}
    else if(firstDigit == 2) {first.setTextureRect(two);}
    else if(firstDigit == 3) {first.setTextureRect(three);}
    else if(firstDigit == 4) {first.setTextureRect(four);}
    else if(firstDigit == 5) {first.setTextureRect(five);}
    else if(firstDigit == 6) {first.setTextureRect(six);}
    else if(firstDigit == 7) {first.setTextureRect(seven);}
    else if(firstDigit == 8) {first.setTextureRect(eight);}
    else {first.setTextureRect(nine);}

    //Sets the sprite for the second digit
    if(secondDigit == 0) {second.setTextureRect(zero);}
    else if(secondDigit == 1) {second.setTextureRect(one);}
    else if(secondDigit == 2) {second.setTextureRect(two);}
    else if(secondDigit == 3) {second.setTextureRect(three);}
    else if(secondDigit == 4) {second.setTextureRect(four);}
    else if(secondDigit == 5) {second.setTextureRect(five);}
    else if(secondDigit == 6) {second.setTextureRect(six);}
    else if(secondDigit == 7) {second.setTextureRect(seven);}
    else if(secondDigit == 8) {second.setTextureRect(eight);}
    else {second.setTextureRect(nine);}

    //Sets the sprite for the third digit
    if(thirdDigit == 0) {third.setTextureRect(zero);}
    else if(thirdDigit == 1) {third.setTextureRect(one);}
    else if(thirdDigit == 2) {third.setTextureRect(two);}
    else if(thirdDigit == 3) {third.setTextureRect(three);}
    else if(thirdDigit == 4) {third.setTextureRect(four);}
    else if(thirdDigit == 5) {third.setTextureRect(five);}
    else if(thirdDigit == 6) {third.setTextureRect(six);}
    else if(thirdDigit == 7) {third.setTextureRect(seven);}
    else if(thirdDigit == 8) {third.setTextureRect(eight);}
    else {third.setTextureRect(nine);}

    //Sets the third digit to a negative sign if the flag count is negative
    if(isNegative) {
        third.setTextureRect(neg);
    }

    //Draw the sprites to the window
    third.setPosition(0, 512);
    second.setPosition(21, 512);
    first.setPosition(42, 512);
    toolbox.window.draw(third);
    toolbox.window.draw(second);
    toolbox.window.draw(first);

    //Set the sprites for each button
    toolbox.debugButton->setSprite(new sf::Sprite(toolbox.debug));
    toolbox.testButton1->setSprite(new sf::Sprite(toolbox.testOne));
    toolbox.testButton2->setSprite(new sf::Sprite(toolbox.testTwo));
    toolbox.testButton3->setSprite(new sf::Sprite(toolbox.testThree));

    //Sets the sprite for the new game button depending on the GameState
    if(toolbox.gameState->getPlayStatus() == GameState::PLAYING) {
        toolbox.newGameButton->setSprite(new sf::Sprite(toolbox.happy));
    }
    else if(toolbox.gameState->getPlayStatus() == GameState::WIN) {
        toolbox.newGameButton->setSprite(new sf::Sprite(toolbox.win));
    }
    else {
        toolbox.newGameButton->setSprite(new sf::Sprite(toolbox.lose));
    }

    //Sets the Position for each Button
    toolbox.debugButton->getSprite()->setPosition(toolbox.debugButton->getPosition().x, toolbox.debugButton->getPosition().y);
    toolbox.newGameButton->getSprite()->setPosition(toolbox.newGameButton->getPosition().x, toolbox.newGameButton->getPosition().y);
    toolbox.testButton1->getSprite()->setPosition(toolbox.testButton1->getPosition().x, toolbox.testButton1->getPosition().y);
    toolbox.testButton2->getSprite()->setPosition(toolbox.testButton2->getPosition().x, toolbox.testButton2->getPosition().y);
    toolbox.testButton3->getSprite()->setPosition(toolbox.testButton3->getPosition().x, toolbox.testButton3->getPosition().y);

    //Draws each Button to the window
    toolbox.window.draw(*toolbox.debugButton->getSprite());
    toolbox.window.draw(*toolbox.newGameButton->getSprite());
    toolbox.window.draw(*toolbox.testButton1->getSprite());
    toolbox.window.draw(*toolbox.testButton2->getSprite());
    toolbox.window.draw(*toolbox.testButton3->getSprite());

    //Draws each tile to the window
    for(int j = 0; j < toolbox.board.size(); ++j) {
        for(int k = 0; k < toolbox.board.at(0).size(); ++k) {
            toolbox.gameState->getTile(k, j)->draw();
        }
    }
}

//Define the function that defines all Toolbox variables once the program is run, and calls the gameLoop() function to
//run the game loop
int launch() {
    Toolbox& toolbox = Toolbox::getInstance();

    //Call the default constructor for GameState()
    toolbox.gameState = new GameState();

    //Sets each button's position as well as their functions (for the debug and new game button uses the respective global functions
    //and uses lambda functions for the test buttons)
    toolbox.debugButton = new Button(sf::Vector2f(496, 512), toggleDebugMode);
    toolbox.newGameButton = new Button(sf::Vector2f(368, 512), restart);
    toolbox.testButton1 = new Button(sf::Vector2f(560, 512),
                                     []() ->void {
        delete Toolbox::getInstance().gameState;
        Toolbox::getInstance().gameState = new GameState("boards/testboard1.brd");
        if(getDebugMode()) { toggleDebugMode(); }
    });
    toolbox.testButton2 = new Button(sf::Vector2f(624, 512),
                                     []()->void {
        delete Toolbox::getInstance().gameState;
        Toolbox::getInstance().gameState = new GameState("boards/testboard2.brd");
        if(getDebugMode()) { toggleDebugMode(); }
    });
    toolbox.testButton3 = new Button(sf::Vector2f(688, 512),
                                     []()->void {
        delete Toolbox::getInstance().gameState;
        Toolbox::getInstance().gameState = new GameState("boards/testboard3.brd");
        if(getDebugMode()) { toggleDebugMode(); }
    });

    //Call the game loop function
    toolbox.gameLoop();
    return 0;
}

//Launches the game
int main() { return launch(); }