#include "Game.h"
#include"Menu.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::playGame(){


       std::string name=playername();
       std::cout<<name;
    sf::Font namefont;
    sf::RectangleShape nameBox;
    sf::Text NameText;

    NameText.setFont(namefont);
    NameText.setCharacterSize(20);
    NameText.setFillColor(sf::Color::White);
    NameText.setPosition(300,10);

    nameBox.setFillColor(sf::Color::Blue);
    nameBox.setPosition(300,10);
    nameBox.setSize(sf::Vector2f(250,40));
    NameText.setString(name);

    window.create(sf::VideoMode(850,650),"BomberMan");
    allTexture.loadFromFile("allTexture.png");
    bomberSprite.setTexture(allTexture);
    bomberSprite.setTextureRect(sf::IntRect(0,0,50,50));
    bomberSprite.setPosition(sf::Vector2f(50,50));
    bomberSprite.setColor(sf::Color::White);
    bombSprite.setTexture(allTexture);
    bombSprite.setTextureRect(sf::IntRect(150,100,50,50));
    antiBomberTexture.loadFromFile("antiSprite.png");
    antiBomberSprite.setTexture(antiBomberTexture);
    antiBomberSpriteBound=antiBomberSprite.getGlobalBounds();
    antiBomberSpritePosition=antiBomberSprite.getPosition();
    antiBomberSprite.setTextureRect(sf::IntRect(0,0,50,50));
    antiBomberSprite.setPosition(sf::Vector2f(rand()%10 *50, rand()%10 *50));
    fireTexture.loadFromFile("fire.png");
    fireSprite.setTexture(fireTexture);
    fireSprite.setTextureRect(sf::IntRect(0,0,57,60));
    fireSprite.setScale(sf::Vector2f(1.0f, 1.0f));
   // breakableWallDraw[=1;
    explosionSound.openFromFile("explosion.wav");
  //  gameSound.openFromFile("gameSound.wav");
//gameSound.play();
    while(window.isOpen())
    {

        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.clear();
                window.close();
            }

        }

        window.clear(sf::Color(64,64,64));
        spriteManager();

        bomb();
        window.draw(bomberSprite);
        maploader();
        antiSpriteManager();
        window.draw(antiBomberSprite);
        timeManager();
        score();
         window.draw(nameBox);
         window.draw(NameText);

        window.display();
        bombActive=0; // once initiated to one after space pressed and done.. just for bomb to take the bomber position when space pressed


    }
}

void Game::maploader(){

    char mapping[13][17]={
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*', 0 , 2 , 0 , 2 , 0 ,'*','*','*','*','*','*','*','*','*','*'},
        {'*', 1 ,'x', 3 ,'x', 0 ,'x','*','x', 0 ,'x', 1 ,'x', 0 ,'x', 0 ,'*'},
        {'*', 3 , 0 , 1 , 0 , 0 , 0 ,'*', 0 , 0 , 0 , 1 , 0 , 3 , 2 , 0 ,'*'},
        {'*', 3 ,'x', 2 ,'x', 1 ,'x', 2 ,'x', 3 ,'x', 0 ,'x', 0 ,'x', 3 ,'*'},
        {'*', 1 , 2 , 3 , 0 , 0 , 0 , 1 , 0 , 3 , 0 , 3 , 0 , 2 , 0 , 2 ,'*'},
        {'*', 2 ,'x', 0 ,'x', 2 ,'x', 2 ,'x', 1 ,'x', 0 ,'x', 3 ,'x', 3 ,'*'},
        {'*', 2 , 2 , 0 , 3 , 1 , 0 , 1 , 3 , 2 , 2 , 2 , 0 , 1 , 0 , 3 ,'*'},
        {'*', 0 ,'x', 3 ,'x', 0 ,'x', 0 ,'x', 3 ,'x', 0 ,'x', 0 ,'x', 1 ,'*'},
        {'*', 1 , 1 , 2 , 3 , 3 , 2 , 1 , 2 , 0 , 1 , 0 , 0 , 0 , 0 , 2 ,'*'},
        {'*', 2 ,'x', 0 ,'x', 2 ,'x', 2 ,'x', 1 ,'x', 1 ,'x', 0 ,'x', 2 ,'*'},
        {'*', 1 , 2 , 2 , 2 , 1 , 0 , 3 , 0 , 0 , 1 , 0 , 3 , 0 , 3 , 0 ,'*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}
                        };

    int i=0;
    for (mapx=0; mapx<13; mapx++)
    {
        for(mapy=0; mapy<17; mapy++)
        {
            if(mapping[mapx][mapy]=='x')
            {
                concreteWallSprite[i].setTexture(allTexture);
                concreteWallSprite[i].setTextureRect(sf::IntRect(150,50,50,50));
                concreteWallSprite[i].setPosition(mapy*50, mapx*50);
                window.draw(concreteWallSprite[i]);
                i++;
            }

            if(mapping[mapx][mapy]==r)
            {
                breakableWallSprite[i].setTexture(allTexture);
                breakableWallSprite[i].setTextureRect(sf::IntRect(150,0,50,50));
                breakableWallSprite[i].setPosition(mapy*50, mapx*50);
                if(!breakableWallDestroy[i])
                window.draw(breakableWallSprite[i]);
                i++;
            }
        }

    }
    sf::RectangleShape rectangleLeft(sf::Vector2f(50,650));
    sf::RectangleShape rectangleUp(sf::Vector2f(850,50));
    sf::RectangleShape rectangleRight(sf::Vector2f(50,650));
    rectangleRight.setPosition(sf::Vector2f(800,0));
    sf::RectangleShape rectangleDown(sf::Vector2f(850, 50));
    rectangleDown.setPosition(sf::Vector2f(0,600));
    rectangleUp.setFillColor(sf::Color(52,25,0));
    rectangleRight.setFillColor(sf::Color(52,25,0));
    rectangleLeft.setFillColor(sf::Color(52,25,0));
    rectangleDown.setFillColor(sf::Color(52,25,0));
    //rectangle.setPosition(sf::Vector2f(0,0,0,650));
    window.draw(rectangleLeft);
    window.draw(rectangleUp);
    window.draw(rectangleRight);
    window.draw(rectangleDown);

    //timeManager();
}


std::string Game::NumtoStr(int remain){

    std::ostringstream ss;
    ss<<remain;
    return ss.str();
  }

void Game::timeManager(){

           CLOCK.restart();
           elapsedTime=sf::seconds(CLOCK.getElapsedTime().asSeconds());

    int remainingTime;
    std::string displayTime;

    timer.setPosition(sf::Vector2f(600, 15));
    timer.setFillColor(sf::Color::White);
    timer.setSize(sf::Vector2f(240,30));


    timeFont.loadFromFile("timeFont.ttf");
    timeText.setFont(timeFont);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::Red);
    timeText.setPosition(sf::Vector2f(600, 15));


    clockTime=sf::operator-(clockTime,oneSec);
    remainingTime=clockTime.asMilliseconds();
  // while(operator== (elapsedTime, slowTime)){

    displayTime="Time Remaining:   "+ NumtoStr(remainingTime/60000)+ " : " + NumtoStr((remainingTime/1000)%60);
    timeText.setString(displayTime);

    //std::cout<<displayTime<<std::endl;
    window.draw(timer);
    window.draw(timeText);


//    }
//    */
}

void Game::spriteManager(){
    window.setFramerateLimit(10);

    bomberSpriteBound=bomberSprite.getGlobalBounds();
    bomberSpritePosition=bomberSprite.getPosition();

    bombSpritePosition=bombSprite.getPosition();
    int rightMove=1; // for collision
    int leftMove=1;
    int upMove=1;
    int downMove=1;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                rightActive=true;
                    upActive=false;
                    leftActive=false;
                    downActive=false;

                    bomberSprite.setTextureRect(sf::IntRect(spriteMovementCounter*50,150,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(bomberSpritePosition.x == concreteWallSpriteBound[i].left-50 &&bomberSpritePosition.y<=concreteWallSpriteBound[i].top
                        +48 &&bomberSpritePosition.y>= concreteWallSpriteBound[i].top-48)
                        {
                            bomberSprite.move(0,0);
                            rightMove =0;
                        }

                    if( !breakableWallDestroy[i] &&bomberSpritePosition.x == breakableWallSpriteBound[i].left-50 &&bomberSpritePosition.y<=breakableWallSpriteBound[i].top
                        +48 &&bomberSpritePosition.y>= breakableWallSpriteBound[i].top-48)
                        {
                            bomberSprite.move(0,0);
                            rightMove =0;
                        }
                     if(bombSprite.getGlobalBounds().intersects(bomberSpriteBound))
                {
                    std::cout<<"hehehe";
                    rightMove=0;
                    bomberSprite.move(0,0);
                }


                }

                if (rightMove!=0)
                {
                    if(bomberSpritePosition.x<750 )
                    {
                        bomberSprite.move(5,0);

                    }
                }

            }
            else

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                rightActive=false;
                    upActive=false;
                    leftActive=true;
                    downActive=false;
                bomberSprite.setTextureRect(sf::IntRect(spriteMovementCounter*50,100,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(bomberSpritePosition.x -50 == concreteWallSpriteBound[i].left
                            &&bomberSpritePosition.y <= concreteWallSpriteBound[i].top+48 && bomberSpritePosition.y>= concreteWallSpriteBound[i].top-48)
                    {
                        bomberSprite.move(0,0);
                        leftMove =0;
                    }
                     if(!breakableWallDestroy[i] &&bomberSpritePosition.x -50 ==breakableWallSpriteBound[i].left
                            &&bomberSpritePosition.y <= breakableWallSpriteBound[i].top+48 && bomberSpritePosition.y>= breakableWallSpriteBound[i].top-48)
                    {
                        bomberSprite.move(0,0);
                        leftMove =0;
                    }
                }
                  if(bombSprite.getGlobalBounds().intersects(bomberSpriteBound))
                {
                    std::cout<<"hehehe";
                    leftMove=0;
                    bomberSprite.move(0,0);
                }


                if(leftMove!=0)
                {
                    if(bomberSpritePosition.x>50)
                    {
                        bomberSprite.move(-5,0);

                    }
                }
            }
            else
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {


                 rightActive=false;
                    upActive=true;
                    leftActive=false;
                    downActive=false;
                bomberSprite.setTextureRect(sf::IntRect(spriteMovementCounter*50,50,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(bomberSpritePosition.y == concreteWallSpriteBound[i].top+50
                        &&bomberSpritePosition.x <= concreteWallSpriteBound[i].left + 48 && bomberSpritePosition.x >= concreteWallSpriteBound[i].left -48)
                    {
                        bomberSprite.move(0,0);
                        upMove=0;
                    }
                     if(!breakableWallDestroy[i] && bomberSpritePosition.y == breakableWallSpriteBound[i].top+50
                        &&bomberSpritePosition.x <= breakableWallSpriteBound[i].left + 48 && bomberSpritePosition.x >= breakableWallSpriteBound[i].left -48)
                    {
                        bomberSprite.move(0,0);
                        upMove=0;
                    }
                }
                  if(bombSprite.getGlobalBounds().intersects(bomberSpriteBound))
                {
                    std::cout<<"hehehe";
                    upMove=0;
                    bomberSprite.move(0,0);
                }

                if(upMove!=0)
                {
                    if(bomberSpritePosition.y>=52 )
                    {
                        bomberSprite.move(0,-5);

                    }
                }
            }
            else
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                rightActive=false;
                        upActive=false;
                        leftActive=false;
                        downActive=true;

                bomberSprite.setTextureRect(sf::IntRect(spriteMovementCounter*50,0,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(bomberSpritePosition.y == concreteWallSpriteBound[i].top-50
                        && bomberSpritePosition.x <= concreteWallSpriteBound[i].left+48 && bomberSpritePosition.x>= concreteWallSpriteBound[i].left -48)
                    {
                        bomberSprite.move(0,0);
                        downMove=0;
                    }
                     if(!breakableWallDestroy[i] && bomberSpritePosition.y == breakableWallSpriteBound[i].top-50
                        && bomberSpritePosition.x <= breakableWallSpriteBound[i].left+48 && bomberSpritePosition.x>= breakableWallSpriteBound[i].left -48)
                    {
                        bomberSprite.move(0,0);
                        downMove=0;
                    }
                }
                  if(bombSprite.getGlobalBounds().intersects(bomberSpriteBound))
                {
                    std::cout<<"hehehe";
                    downMove=0;
                    bomberSprite.move(0,0);
                }


                if(downMove!=0)
                {
                    if(bomberSpritePosition.y<=548)
                    {
                        bomberSprite.move(0,5);

                    }
                }
            }
    spriteMovementCounter++;
    if(spriteMovementCounter==3)
    {
        spriteMovementCounter=0;
    }
   /* if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Clock clock;
        bombTime= sf::Clock::getElapsedTime()
        std::cout<<bombTime;
    }*/
}
void Game::antiSpriteManager()
{
    window.setFramerateLimit(10);
    antiBomberSpriteBound=antiBomberSprite.getGlobalBounds();
    antiBomberSpritePosition=antiBomberSprite.getPosition();

    int rightMove=1;
    int leftMove=1;
    int upMove=1;
    int downMove=1;


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {

                 antiBomberSprite.setTextureRect(sf::IntRect(antiSpriteMovementCounter*50,150,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(antiBomberSpritePosition.x == concreteWallSpriteBound[i].left-50 &&antiBomberSpritePosition.y<=concreteWallSpriteBound[i].top
                        +48 &&antiBomberSpritePosition.y>= concreteWallSpriteBound[i].top-48)
                        {
                            antiBomberSprite.move(0,0);
                            rightMove =0;
                        }
                    if(antiBomberSpritePosition.x == breakableWallSpriteBound[i].left-50 &&antiBomberSpritePosition.y<=breakableWallSpriteBound[i].top
                        +48 &&antiBomberSpritePosition.y>= breakableWallSpriteBound[i].top-48)
                        {
                            antiBomberSprite.move(0,0);
                            rightMove =0;
                        }

                }
                if (rightMove!=0)
                {
                    if(antiBomberSpritePosition.x<750 )
                    {
                        antiBomberSprite.move(5,0);
                    }
                }
            }
            else

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                antiBomberSprite.setTextureRect(sf::IntRect(antiSpriteMovementCounter*50,100,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(antiBomberSpritePosition.x -50 == concreteWallSpriteBound[i].left
                            &&antiBomberSpritePosition.y <= concreteWallSpriteBound[i].top+48 && antiBomberSpritePosition.y>= concreteWallSpriteBound[i].top-48)
                    {
                        antiBomberSprite.move(0,0);
                        leftMove =0;
                    }
                     if(antiBomberSpritePosition.x -50 ==breakableWallSpriteBound[i].left
                            &&antiBomberSpritePosition.y <= breakableWallSpriteBound[i].top+48 && antiBomberSpritePosition.y>= breakableWallSpriteBound[i].top-48)
                    {
                        antiBomberSprite.move(0,0);
                        leftMove =0;
                    }
                }

                if(leftMove!=0)
                {
                    if(antiBomberSpritePosition.x>50)
                    {
                        antiBomberSprite.move(-5,0);
                    }
                }
            }
            else
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                antiBomberSprite.setTextureRect(sf::IntRect(antiSpriteMovementCounter*50,50,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(antiBomberSpritePosition.y == concreteWallSpriteBound[i].top+50
                        &&antiBomberSpritePosition.x <= concreteWallSpriteBound[i].left + 48 && antiBomberSpritePosition.x >= concreteWallSpriteBound[i].left -48)
                    {
                        antiBomberSprite.move(0,0);
                        upMove=0;
                    }
                     if(antiBomberSpritePosition.y == breakableWallSpriteBound[i].top+50
                        &&antiBomberSpritePosition.x <= breakableWallSpriteBound[i].left + 48 && antiBomberSpritePosition.x >= breakableWallSpriteBound[i].left -48)
                    {
                        antiBomberSprite.move(0,0);
                        upMove=0;
                    }
                }
                if(upMove!=0)
                {
                    if(antiBomberSpritePosition.y>=52 )
                    {
                        antiBomberSprite.move(0,-5);
                    }
                }
            }
            else
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                antiBomberSprite.setTextureRect(sf::IntRect(antiSpriteMovementCounter*50,0,50,50));
                for(int i=0; i< 40; i++)
                {
                    concreteWallSpriteBound[i]=concreteWallSprite[i].getGlobalBounds();
                    breakableWallSpriteBound[i]=breakableWallSprite[i].getGlobalBounds();
                    if(antiBomberSpritePosition.y == concreteWallSpriteBound[i].top-50
                        && antiBomberSpritePosition.x <= concreteWallSpriteBound[i].left+48 && antiBomberSpritePosition.x>= concreteWallSpriteBound[i].left -48)
                    {
                        antiBomberSprite.move(0,0);
                        downMove=0;
                    }
                     if(antiBomberSpritePosition.y == breakableWallSpriteBound[i].top-50
                        && antiBomberSpritePosition.x <= breakableWallSpriteBound[i].left+48 && antiBomberSpritePosition.x>= breakableWallSpriteBound[i].left -48)
                    {
                        antiBomberSprite.move(0,0);
                        downMove=0;
                    }
                }

                if(downMove!=0)
                {
                    if(antiBomberSpritePosition.y<=548)
                    {
                        antiBomberSprite.move(0,5);
                    }
                }
            }
    antiSpriteMovementCounter++;
    if(antiSpriteMovementCounter==3)
    {
        antiSpriteMovementCounter=0;
    }
}



std::string Game::playername(){


    std::string playerName;
    sf::Font font;
    sf::RectangleShape questionBox,answerBox;
    sf::Text askNameText,playerNameText;
    bool quit=false;
    sf::RenderWindow window(sf::VideoMode(640,480),"Name Entering Menu");

    font.loadFromFile("timeFont.ttf");

    askNameText.setString("Before we begin, please enter your name:");
    askNameText.setFont(font);
    askNameText.setCharacterSize(20);
    askNameText.setPosition(sf::Vector2f(100,100));

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(25);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(100,200);

    questionBox.setFillColor(sf::Color::Black);
    questionBox.setPosition(0,100);
    questionBox.setSize(sf::Vector2f(640,40));

    answerBox.setFillColor(sf::Color::White);
    answerBox.setPosition(0,200);
    answerBox.setSize(sf::Vector2f(640,40));

    while (!quit){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type==sf::Event::Closed){
                quit=true;
            }
            if (event.type==sf::Event::KeyPressed){
                if (event.key.code==sf::Keyboard::Return)
                    quit=true;
            }
            if (event.type==sf::Event::TextEntered){
                if ((event.text.unicode>64 and event.text.unicode<91) or (event.text.unicode>96 and event.text.unicode<123) or event.text.unicode==32  ){
                    playerName+=char(event.text.unicode);
                }
                else if (event.text.unicode==8){
                    if (!playerName.empty())
                        playerName.pop_back();
                }
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(questionBox);
        window.draw(answerBox);
        window.draw(askNameText);
        playerNameText.setString(playerName);
        window.draw(playerNameText);
        window.display();

    }

    std::cout<<"Name entered: "<<playerName<<std::endl;
    return playerName;
}


 void Game::score(){

    std::string Score;

    sf::Font font;
    font.loadFromFile("timeFont.ttf");
    sf::RectangleShape ScoreBox;
    sf::Text ScoreText;

    ScoreBox.setFillColor(sf::Color::White);
    ScoreBox.setPosition(75,10);
    ScoreBox.setSize(sf::Vector2f(150,40));

    ScoreText.setFont(font);
    ScoreText.setCharacterSize(25);
    ScoreText.setFillColor(sf::Color::Black);
    ScoreText.setPosition(75,10);
    Sc=Sc+1;

     Score="SCORE  :   "+ NumtoStr(Sc);
     ScoreText.setString(Score);

     window.draw(ScoreBox);
     window.draw(ScoreText);
}




