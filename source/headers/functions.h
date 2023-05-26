#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void restart(Aster &aster, Bullet &pocisk, Player &player, Medkit &apt);
void collision_bullet_asteroid(Bullet &pocisk, Aster &aster);
void collision_ship_asteroid(Aster &aster, Player &player);

#endif