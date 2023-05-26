#include "headers/functions.h"

// function that restart all asteroids, bullets, player position, health, points and medkits
void restart(Aster& aster, Bullet& pocisk, Player& player, Medkit& apt)
{
    aster.asters.clear();
    pocisk.bullets.clear();
    apt.asters.clear();
    player.ship.setPosition(w / 2 - 7, h - 64);
    player.sy = 0;
}

// checking collision of bullet with asteroids
// it is checking all xy of bullets and asteroids
// not optimal but works 
// i could do it easier and better for comupter
// but i wanted avoid situations like bullet inside of asteroid 
// if bullet meet asteroid, then both of them disapear
void collision_bullet_asteroid(Bullet &pocisk, Aster &aster)
{
    for (int b = 0; b < pocisk.bullets.size(); b++)
    {
        int temp_xb = pocisk.bullets[b].getPosition().x + 7;
        int temp_yb = pocisk.bullets[b].getPosition().y + 10;
        for (int a = 0; a < aster.asters.size(); a++)
        {
            int temp_xa = aster.asters[a].getPosition().x;
            int temp_ya = aster.asters[a].getPosition().y;
            if (temp_xb >= temp_xa && temp_xb <= (temp_xa + 64))
            {
                if (temp_yb >= temp_ya && temp_yb <= temp_ya + 64)
                {
                    aster.asters.erase(aster.asters.begin() + a);
                    pocisk.bullets.erase(pocisk.bullets.begin() + b);
                    points += 1;
                }
            }
        }
    }
}
// checking collision of player's ship with asteroids
// works like function above
void collision_ship_asteroid(Aster &aster, Player &player)
{
    for (int z = 0; z < 64; z++)
    {
        int temp_xb = player.ship.getPosition().x + z;
        int temp_yb = player.ship.getPosition().y + z;
        for (int a = 0; a < aster.asters.size(); a++)
        {
            int temp_xa = aster.asters[a].getPosition().x;
            int temp_ya = aster.asters[a].getPosition().y;
            if (temp_xb >= temp_xa && temp_xb <= (temp_xa + 64))
            {
                if (temp_yb >= temp_ya && temp_yb <= temp_ya + 64)
                {
                    aster.asters.erase(aster.asters.begin() + a);
                    player.hp--;
                    player.sy += 7;
                }
            }
        }
    }
    // if player's health is equal 0, then player dies
    // and game is going to restart menu/game over menu
    if (player.hp <= 0)
    {
        game_state_number = 2;
    }
}