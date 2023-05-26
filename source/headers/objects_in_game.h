#ifndef OBJECTS_IN_GAME_H
#define OBJECTS_IN_GAME_H

//player

class Player
{
public:
    short left, right, hp, sy;
    sf::Sprite ship, health;
    sf::Texture ship_image, health_image;
    Player()
        : left{0}, right{0}, hp{3}
    {
        ship_image.loadFromFile("images/ship.png");
        ship.setTexture(ship_image);
        ship.setTextureRect(sf::IntRect(0, 0, 64, 64));
        ship.setPosition(w / 2 - 7, h - 64);

        health_image.loadFromFile("images/health.png");
        health.setTexture(health_image);
        sy = 0;
        health.setTextureRect(sf::IntRect(0, sy, 26, 7));
        health.setPosition(10, 54);
        health.scale(5, 5);
    }
    void update();
    void draw(sf::RenderWindow &window);
    
};

// asteroids

class Aster
{
public:
    Aster()
    {
        txt.loadFromFile("images/aster.png");
        aster.setTexture(txt);
    }

    sf::Texture txt;
    sf::Sprite aster;
    std::vector<sf::Sprite> asters;

    void draw(sf::RenderWindow &window);
    void update();
};

// medkits

class Medkit
{
public:
    Medkit()
    {
        txt.loadFromFile("images/medkit.png");
        aster.setTexture(txt);
    }

    sf::Texture txt;
    sf::Sprite aster;
    std::vector<sf::Sprite> asters;

    void draw(sf::RenderWindow &window);
    void update();
    void collision(Player &player);
};

// bullets

class Bullet
{
public:
    sf::Texture txt;
    sf::Sprite bullet;
    std::vector<sf::Sprite> bullets;
    int lb;
    unsigned char reload;
    int reload_time;

    Bullet()
    {
        txt.loadFromFile("images/bullet.png");
        bullet.setTexture(txt);
        bullet.setTextureRect(sf::IntRect(0, 0, 14, 20));
        reload_time = 40;
        reload = 0;
    }
    void draw(sf::RenderWindow &window);
    void update(Player &player);
};

#endif