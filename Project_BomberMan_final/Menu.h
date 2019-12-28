#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Game.h"

class Menu
{
    public:
        Menu();
        void showMenu();
        void textEdit();
        virtual ~Menu();

    protected:
        Game game;
        sf::Texture menuPic;
        sf::Sprite  menuPicSprite;
        sf::Font font;
        sf::Text play, instruction, exit;
        sf::Music menuMusic;
        //sf::Vector2i pointerPosition;

    private:
};

#endif // MENU_H

