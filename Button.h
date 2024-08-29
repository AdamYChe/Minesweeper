/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include <SFML/Graphics.hpp>
#include <functional>
#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H

//Declare the Button class
class Button {
public:

    //Declare the constructor for Button, which takes in a position and function parameter
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);

    //Getter methods for Button
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();

    //Setter method for the Sprite
    void setSprite(sf::Sprite* _sprite);

    //Declares the function that is called when the Button is clicked
    void onClick();

    //Overrides the default destructor for Button, to get rid of the dynamically allocated Sprite
    ~Button();
private:

    //Declare private variables for the position, sprite pointer, and function of a Button
    sf::Vector2f position;
    sf::Sprite* sprite;
    std::function<void(void)> ptrOnClick;

};


#endif //MINESWEEPER_BUTTON_H
