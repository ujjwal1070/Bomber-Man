  #include"Game.h"
  #include <SFML/System/Clock.hpp>
  void Game::bomb()
  {
  if(explosion)
      {

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
       {
           clock1.restart();
            a=1;                    // to let program know that space has been pressed
            bombActive=1;            // to stop the bomb follow the bomber
            n=0;                    // to stop the explosion animation
            explosion=0;            // to wait for clock to restart until explosion
           time2=sf::seconds(clock1.getElapsedTime().asSeconds());
        }
      }
       if(operator==(time2, sf::seconds(2)))
       {
           a=0;  // to let program know that now is the time to stop animation
       }
       time2=sf::seconds(clock1.getElapsedTime().asSeconds());
        if(a && operator< (  time2, time1))
           {
               if(bombActive)
               {
                   if(rightActive )
                   {
                       bombSprite.setPosition(bomberSpritePosition.x+50, bomberSpritePosition.y);
                    for(int i=0; i<40; i++)
                    {
                        if(bombSprite.getGlobalBounds().intersects(concreteWallSpriteBound[i]))
                             bombSprite.setPosition(concreteWallSprite[i].getPosition().x-50, concreteWallSprite[i].getPosition().y );
                           if(bombSprite.getGlobalBounds().intersects(breakableWallSpriteBound[i]))
                            {

                                bombSprite.setPosition(breakableWallSprite[i].getPosition().x-50, breakableWallSprite[i].getPosition().y );
                            }
                    }

                   }
                   else if(leftActive )
                    {
                        bombSprite.setPosition(bomberSpritePosition.x-50, bomberSpritePosition.y);
                         for(int i=0; i<40; i++)
                    {
                        if(bombSprite.getGlobalBounds().intersects(concreteWallSpriteBound[i]))
                          bombSprite.setPosition(concreteWallSprite[i].getPosition().x+50, concreteWallSprite[i].getPosition().y );

                           if( bombSprite.getGlobalBounds().intersects(breakableWallSpriteBound[i]))
                           {

                                bombSprite.setPosition(breakableWallSprite[i].getPosition().x+50, breakableWallSprite[i].getPosition().y );
                           }

                    }
                    }
                    else if(upActive )
                        {bombSprite.setPosition(bomberSpritePosition.x, bomberSpritePosition.y-50);
                         for(int i=0; i<40; i++)
                    {
                        if(bombSprite.getGlobalBounds().intersects(concreteWallSpriteBound[i]))
                            bombSprite.setPosition(concreteWallSprite[i].getPosition().x, concreteWallSprite[i].getPosition().y+50 );
                           if(bombSprite.getGlobalBounds().intersects(breakableWallSpriteBound[i]))
                            {
                            bombSprite.setPosition(breakableWallSprite[i].getPosition().x, breakableWallSprite[i].getPosition().y+50 );
                            }

                    }
                        }
                    else if(downActive )
                       {
                           bombSprite.setPosition(bomberSpritePosition.x, bomberSpritePosition.y +50);
                         for(int i=0; i<40; i++)
                    {
                        if(bombSprite.getGlobalBounds().intersects(concreteWallSpriteBound[i]))
                            bombSprite.setPosition(concreteWallSprite[i].getPosition().x, concreteWallSprite[i].getPosition().y-50 );
                         if( bombSprite.getGlobalBounds().intersects(breakableWallSpriteBound[i]))
                            {
                            bombSprite.setPosition(breakableWallSprite[i].getPosition().x, breakableWallSprite[i].getPosition().y-50 );
                            }

                    }
                       }
                       else
                       {
                           bombSprite.setPosition(bomberSpritePosition.x+50, bomberSpritePosition.y);// for initial condition

                       }

               }
               window.draw(bombSprite);

           }




        if(a && operator> (time2, time1))
        {
             if(n<1)
            {
                if(count>=4)
                {
                    count=0;
                    n++;
                }

            fireSprite.setTextureRect(sf::IntRect(count*57,60,57,60));
             window.draw(fireSprite);
                count++;

            }
            if(n==1)
            {explosion=1;
                if(bomberSpriteBound.intersects(fireSprite.getGlobalBounds()))
                {
                    window.clear();
                    std::cout<<"collided";
                    //window.close();
                }
                for(int i=0; i<40; i++)
                {
                    if(fireSprite.getGlobalBounds().intersects(breakableWallSpriteBound[i]))
                        breakableWallDestroy[i]=true;
                }
                 bombSprite.setPosition(sf::Vector2f(0,0));
                 std::cout<<bombSpritePosition.x<<std::endl;
                //breakableWallDraw=0;
            }
        }


        //explosionSound.play();

    fireSprite.setPosition(bombSpritePosition);
    fireSpritePosition=fireSprite.getPosition();
  }


