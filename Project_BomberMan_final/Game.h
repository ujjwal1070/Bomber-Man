#ifndef GAME_H
#define GAME_H

#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System.hpp>
#include <cctype>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>


class Game
{
    public:
        int Sc=0;
        Game();
        void playGame();
        void maploader();
        void timeManager();
        void spriteManager();
        void antiSpriteManager();
        void bomb();
        void score();
       std::string playername();
        std::string NumtoStr(int);
        virtual ~Game();

    protected:
    sf::Texture allTexture,fireTexture,antiBomberTexture;
    sf::Sprite bomberSprite, fireSprite,bombSprite,antiBomberSprite, concreteWallSprite[60];
    sf::Sprite breakableWallSprite[60];
    sf::Vector2i counter= sf::Vector2i(0,0);
    sf::Vector2f bomberSpritePosition, bombSpritePosition,fireSpritePosition,antiBomberSpritePosition, bombPlantingPosition;
    sf::RenderWindow window;
    sf::Text timeText;
    sf::Font timeFont;
    sf::Time time;
    sf::Event event;
    char mapping[13][17];
    int mapx,mapy;
    int spriteMovementCounter=0,antiSpriteMovementCounter=0;
    int r= rand()%4;
    sf::FloatRect bomberSpriteBound, antiBomberSpriteBound,concreteWallSpriteBound[60], breakableWallSpriteBound[60];
    sf::FloatRect additionalBound;
    sf::Time bombTime;
    sf::Time time1=sf::seconds(2),time2;
    sf::Clock clock1;
    int count=0;
    int n=0;
    int bombActive=0,explosion=1;

    sf::RectangleShape timer;
    sf::Time slowTime=sf::seconds(1),oneSec=sf::milliseconds(100),elapsedTime,clockTime=sf::milliseconds(180000);
    sf::Clock CLOCK;

    bool rightActive=false, leftActive=false, upActive=false, downActive=false;// to show tile location for bomb to appear
    bool rightBombAllowance=true, leftBombAllowance=true, upBombAllowance=true, downBombAllowance=true;

    bool breakableWallDestroy[60]={false};
                            //to draw or not after the animation of bombing
    sf::Music explosionSound;
    sf::Music gameSound;
    bool explosionStart=false; // for sound

    //int h=60;
    int a=0;
    private:
};

#endif // GAME_H

