#include "headers/objects_in_game.h"

// player
// checking if user clicked left or right arrow
// if yes, then ship moves 10 pixels
// and also checking if ship is next to end of screen
// if yes then is not moving -  cant get out of screen
void Player::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        ship.move(-10, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        ship.move(10, 0);
    short x = ship.getPosition().x;
    short y = ship.getPosition().y;
    if (x > w - 64)
        ship.move(-10, 0);
    if (x <= 0)
        ship.move(10, 0);
    health.setTextureRect(sf::IntRect(0, sy, 26, 7));
}
// drawing user's ship on screen
void Player::draw(sf::RenderWindow& window)
{
    window.draw(ship);
    window.draw(health);
}

// asteroids
// drawing asteroids on screen
void Aster::draw(sf::RenderWindow& window)
{
    for(auto& as : asters)
    {
        window.draw(as);
    }
}
//if asteroid is out of screen range then is deleting
void Aster::update()
{
    for (int i = 0; i < asters.size(); i++)
    {
        asters[i].move(0.f, asterspeed);
        int temp_y = asters[i].getPosition().y;
        if (temp_y > h)
        {
            asters.erase(asters.begin() + i);
        }
    }
}

// medkits
// drawing medkits on screen
void Medkit::draw(sf::RenderWindow& window)
{

    for(auto& as : asters)
    {
        window.draw(as);
    }
}
void Medkit::update()
{
    aster.setPosition((rand() % ((w - 64) + 1)), 0);
    if ((rand() % (500 + 1)) % 500 == 0)
    {
        asters.push_back(aster);
    }
    for (int i = 0; i < asters.size(); i++)
    {
        asters[i].move(0.f, 6.f);
        int temp_y = asters[i].getPosition().y;
        if (temp_y > h)
        {
            asters.erase(asters.begin() + i);
        }
    }
}
// checkig collision of medkits with player then getting points if yes
void Medkit::collision(Player& player)
{
    for (int z = 0; z < 64; z++)
    {
        int temp_xb = player.ship.getPosition().x + z;
        int temp_yb = player.ship.getPosition().y + z;
        for (int a = 0; a < asters.size(); a++)
        {
            int temp_xa = asters[a].getPosition().x;
            int temp_ya = asters[a].getPosition().y;
            if (temp_xb >= temp_xa && temp_xb <= (temp_xa + 64))
            {
                if (temp_yb >= temp_ya && temp_yb <= temp_ya + 64)
                {
                    asters.erase(asters.begin() + a);
                    if (player.hp < 3)
                        player.hp++;
                    if (player.sy > 0)
                        player.sy -= 7;
                    points += 3;
                }
            }
        }
    }
}

// bullets
// drawing bullets
void Bullet::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets[i]);
    }
}
// function that
// gives bullets velocity
// checking if user clicked space
// if yes then bullet is creating in front of ship
// if it meets wall, then disapear 
void Bullet::update(Player& player)
{
    if (0 == reload)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            reload = reload_time;
            bullet.setPosition(player.ship.getPosition().x + 25, player.ship.getPosition().y);
            bullets.push_back(bullet);
        }
    }
    else
    {
        reload--;
    }
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].move(0.f, -14.f);
        int temp_y = bullets[i].getPosition().y;
        if (temp_y < -20)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}