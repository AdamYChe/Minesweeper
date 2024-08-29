/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include "Toolbox.h"
#include "minesweeper.h"

//Define the Toolbox() constructor, which initializes the window as well as loads in all textures
Toolbox::Toolbox() {

    //Creates the desired window with the correct size and title
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, <Adam Cheng>");

    //Sets the dynamic memory to nullptr, and will be set later once a game has been created
    gameState = nullptr;
    debugButton = nullptr;
    newGameButton = nullptr;
    testButton1 = nullptr;
    testButton2 = nullptr;
    testButton3 = nullptr;

    //Sets the default debug mode to false
    isDebugMode = false;

    //Loads in all of the Textures from their designated files
    tileHidden.loadFromFile("images/tile_hidden.png");
    tileRevealed.loadFromFile("images/tile_revealed.png");

    flag.loadFromFile("images/flag.png");
    mine.loadFromFile("images/mine.png");

    one.loadFromFile("images/number_1.png");
    two.loadFromFile("images/number_2.png");
    three.loadFromFile("images/number_3.png");
    four.loadFromFile("images/number_4.png");
    five.loadFromFile("images/number_5.png");
    six.loadFromFile("images/number_6.png");
    seven.loadFromFile("images/number_7.png");
    eight.loadFromFile("images/number_8.png");

    happy.loadFromFile("images/face_happy.png");
    win.loadFromFile("images/face_win.png");
    lose.loadFromFile("images/face_lose.png");

    digits.loadFromFile("images/digits.png");

    debug.loadFromFile("images/debug.png");

    testOne.loadFromFile("images/test_1.png");
    testTwo.loadFromFile("images/test_2.png");
    testThree.loadFromFile("images/test_3.png");
}

//Define the gameLoop() method that will read for click events, and call functions to activate on clicks
//Also calls render() to display the window each time a new click event has been activated
int Toolbox::gameLoop() {

    //Get a reference to the instance of the toolbox
    Toolbox& toolbox = Toolbox::getInstance();

    //Sets the condition for the program to run while the window is open
    while(toolbox.window.isOpen()) {
        sf::Event event;

        //Checks for events based on user input
        while (toolbox.window.pollEvent(event)) {

            //Closes the window if the user clicks on the x
            if (event.type == sf::Event::Closed) {
                toolbox.window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePosition = sf::Mouse::getPosition(toolbox.window);

                //Functionality for if the user left clicks
                if(event.mouseButton.button == sf::Mouse::Left) {

                    //Activates the debugButton if the user has left clicked over it
                    if(mousePosition.x >= 496 && mousePosition.x <= 560 && mousePosition.y >= 510 && mousePosition.y <= 574) {
                        toolbox.debugButton->onClick();
                    }

                        //Declare variables to find the specific tile a user clicks on
                        int xSize = toolbox.board.at(0).size();
                        int ySize = toolbox.board.size();
                        int xTileCoord = mousePosition.x / 32;
                        int yTileCoord = mousePosition.y / 32;

                        //Activates the Tile if the user has left clicked over it
                        if(xTileCoord < xSize && yTileCoord < ySize && gameState->getPlayStatus() == GameState::PLAYING) {
                            toolbox.gameState->getTile(xTileCoord, yTileCoord)->onClickLeft();
                        }

                        //Activates the newGameButton if the user has left clicked over it
                        if(mousePosition.x >= 368 && mousePosition.x <= 432 && mousePosition.y >= 510 && mousePosition.y <= 574) {
                            toolbox.newGameButton->onClick();
                        }

                        //Activates the first testButton if the user has left clicked over it
                        if(mousePosition.x >= 560 && mousePosition.x <= 624 && mousePosition.y >= 510 && mousePosition.y <= 574) {
                            toolbox.testButton1->onClick();
                        }

                        //Activates the second testButton if the user has left clicked over it
                        if(mousePosition.x >= 624 && mousePosition.x <= 688 && mousePosition.y >= 510 && mousePosition.y <= 574) {
                            toolbox.testButton2->onClick();
                        }

                        //Activates the third testButton if the user has left clicked over it
                        if(mousePosition.x >= 688 && mousePosition.x <= 752 && mousePosition.y >= 510 && mousePosition.y <= 574) {
                            toolbox.testButton3->onClick();
                        }

                        //If the user has clicked on an exploded mine, sets the PlayStatus to LOSS, and
                        //explodes all other mines on the board
                        for(int j = 0; j < board.size(); ++j) {
                            for(int k = 0; k < board.at(0).size(); ++k) {
                                if(gameState->getTile(k, j)->getState() == Tile::EXPLODED) {
                                    gameState->setPlayStatus(GameState::PlayStatus::LOSS);

                                    for(int j = 0; j < board.size(); ++j) {
                                        for (int k = 0; k < board.at(0).size(); ++k) {
                                            if(board.at(j).at(k)) {
                                                gameState->getTile(k, j)->setState(Tile::EXPLODED);
                                            }
                                        }
                                    }

                                    break;
                                }
                            }
                        }

                        //Defines the logic to check if a user has won by checking if all non-mine tiles have been revealed
                        bool hasWon = true;
                        for(int j = 0; j < board.size(); ++j) {
                            for(int k = 0; k < board.at(0).size(); ++k) {
                                if(gameState->getTile(k, j)->getState() != Tile::REVEALED && !board.at(j).at(k)) {
                                    hasWon = false;
                                    break;
                                }
                            }
                        }
                        if(hasWon) {
                            gameState->setPlayStatus(GameState::PlayStatus::WIN);
                        }
                }

                //Functionality for if the user right clicks
                if(event.mouseButton.button == sf::Mouse::Right) {

                    //Sets variables to make it easier to determine which tile has been selected
                    int xSize = toolbox.board.at(0).size();
                    int ySize = toolbox.board.size();
                    int xTileCoord = mousePosition.x / 32;
                    int yTileCoord = mousePosition.y / 32;

                    //Generates a flag on a tile
                    if(xTileCoord < xSize && yTileCoord < ySize && gameState->getPlayStatus() == GameState::PLAYING) {
                        toolbox.gameState->getTile(xTileCoord, yTileCoord)->onClickRight();
                    }
                }
            }
        }

        //Set the window color to white while clearing the previous window display
        toolbox.window.clear(sf::Color::White);

        //Calls render() to draw all sprites to the window
        render();

        //Displays the window to the screen
        toolbox.window.display();
    }

    return 0;
}

//Deletes all dynamic memory of the Toolbox instance
Toolbox::~Toolbox() {
    delete gameState;
    delete debugButton;
    delete newGameButton;
    delete testButton1;
    delete testButton2;
    delete testButton3;
}