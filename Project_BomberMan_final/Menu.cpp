#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}

void Menu::showMenu(){
    sf::RenderWindow window(sf::VideoMode(850,650), "BomberMan");
    menuPic.loadFromFile("Bomberman.png");
    menuPicSprite.setTexture(menuPic);
    //menuMusic.openFromFile("menuSound.wav");

    //menuPicSprite.setPosition(sf::Vector2f(2,0));
    textEdit();
    while(window.isOpen())
        {

        sf::Event event;
        sf::Vector2i pointerPosition= sf::Mouse::getPosition(window);
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (pointerPosition.x>=150 &&pointerPosition.x<=246 &&pointerPosition.y>= 300 && pointerPosition.y<=325){
                play.setFillColor(sf::Color::Red);
                if(event.type==sf::Event::MouseButtonPressed){
                //   game.playername();
                    game.playGame();
                }
            }
            else if(pointerPosition.x>=150 &&pointerPosition.x<=414 &&pointerPosition.y>= 350 && pointerPosition.y<=375){
                instruction.setFillColor(sf::Color::Red);
                if(event.type==sf::Event::MouseButtonPressed){

                }
            }
            else if(pointerPosition.x>=150 &&pointerPosition.x<=246 &&pointerPosition.y>= 400 && pointerPosition.y<=425){
                exit.setFillColor(sf::Color::Red);
                if(event.type==sf::Event::MouseButtonPressed)
                    window.close();
            }
            else{
                play.setFillColor(sf::Color::Blue);
                instruction.setFillColor(sf::Color::Blue);
                exit.setFillColor(sf::Color::Blue);
            }
        }
    window.clear(sf::Color::Black);
    window.draw(menuPicSprite);
    window.draw(play);
    window.draw(instruction);
    window.draw(exit);
    window.display();
    }
}

void Menu::textEdit(){
    font.loadFromFile("Font.ttf");

    play.setFont(font);
    play.setString("Play");
    play.setCharacterSize(24);
    play.setFillColor(sf::Color::Blue);
    play.setPosition(sf::Vector2f(150, 300));

    instruction.setFont(font);
    instruction.setString("Instruction");
    instruction.setCharacterSize(24);
    instruction.setFillColor(sf::Color::Blue);
    instruction.setPosition(sf::Vector2f(150, 348));

    exit.setFont(font);
    exit.setString("Exit");
    exit.setCharacterSize(24);
    exit.setFillColor(sf::Color::Blue);
    exit.setPosition(sf::Vector2f(150, 396));
}

