/*
 * Authored by Adam Cheng
 * Minesweeper
 * COP3504C
 * Complete on 5 December 2023
 */

#include "Button.h"

//Button constructor that sets the position and the function to the position and function parameters respectively
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    position = _position;
    ptrOnClick = _onClick;
}

//Returns the position of the Button
sf::Vector2f Button::getPosition() {
    return position;
}

//Returns the pointer to the Sprite of the Button
sf::Sprite* Button::getSprite() {
    return sprite;
}

//Sets the Sprite pointer to the parameter Sprite Pointer
void Button::setSprite(sf::Sprite* _sprite) {
    sprite = _sprite;
}

//Calls the function that was given from the constructor
void Button::onClick() {
    ptrOnClick();
}

//Deletes the Sprite that was pointed to
Button::~Button() {
    delete sprite;
}
