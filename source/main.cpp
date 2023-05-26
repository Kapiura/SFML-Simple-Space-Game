#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <random>
#include <string>
#include <sstream>

// global variables
const int h = 800; //height of window
const int w = 1000; //width of window
int game_state_number; //kinda enum 
int points = 0; // user's points
int asterspeed = 5; // speed of asteroids

#include "menu.cpp"
#include "objects_in_game.cpp"
#include "functions.cpp"

int main()
{
    // setting enum game state on 0 = main menu
    game_state_number = 0;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(w, h), "Space game - SFML");

    // setting 60 fps 
    window.setFramerateLimit(60);
    
    // creating all of objects we need in game
    Points *points_obj = new Points;
    Bullet *bullet = new Bullet;
    Player *player = new Player;
    Aster *aster = new Aster;
    Menu *menu = new Menu;
    Restart *res = new Restart;
    BackGround *back = new BackGround;
    Medkit *med = new Medkit;
    
    // game loop
    while (window.isOpen())
    {
        //checking if user clicked cross on window of escape
        //if yes, then programm is ending
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        // enum case of game state
        switch (game_state_number)
        {
        case 0: //main menu
            back->update();
            window.clear(sf::Color{64, 92, 133, 150});
            back->draw(window);
            menu->update(window);
            menu->draw(window);
            window.display();
            break;
        case 1: // playing - game
            aster->aster.setPosition((rand() % ((w - 64) + 1)), -64);
            if ((rand() % (50 + 1)) % 47 == 0)
            {
                aster->asters.push_back(aster->aster);
            }

            player->update();
            bullet->update(*player);
            aster->update();
            back->update();
            points_obj->update();
            collision_bullet_asteroid(*bullet, *aster);
            collision_ship_asteroid(*aster, *player);
            med->update();
            med->collision(*player);

            window.clear(sf::Color{80, 49, 97, 255});
            med->draw(window);
            back->draw(window);
            points_obj->draw(window, points_obj->ss, points_obj->text);
            bullet->draw(window);
            player->draw(window);
            aster->draw(window);
            window.display();
            break;
        case 2: // restart menu/game over
            back->update();
            window.clear(sf::Color{64, 92, 133, 255});
            back->draw(window);
            res->draw(window);
            window.display();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                int px = res->btn.getPosition().x + (250 / 2);
                int py = res->btn.getPosition().y + (150 / 2);
                int mx = sf::Mouse::getPosition(window).x;
                int my = sf::Mouse::getPosition(window).y;
                if ((px - mx) * (px - mx) + (py - my) * (py - my) < 250 * 150)
                {
                    game_state_number = 1;
                    points = 0;
                    player->hp = 3;
                    restart(*aster, *bullet, *player, *med);
                }
            }
            break;
        }
    }
}
