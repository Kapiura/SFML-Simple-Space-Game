#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <array>

using namespace std;
using namespace sf;

const int h = 800;
const int w = 1000;
class Player;
class Bullet;
class Enemy;

class Enemy
{
public:
    short x;
    short y;
    short kol;
    int ruch;
    Texture txt;
    Sprite enemy;
    vector<Sprite> enemies;

    void init()
    {
        short size_pocz = 50;
        short temp_y = 5;
        int temp_x = 44;
        txt.loadFromFile("enemy1.png");
        enemy.setTexture(txt);
        enemy.setTextureRect(IntRect(0, 0, 32, 40));
        for (int i = 0; i < size_pocz; i++)
        {
            enemies.push_back(enemy);
            if (i % 10 == 0)
            {
                temp_y += 50;
                temp_x = 66;
            }
            else
            {
                temp_x += 66;
            }
            enemies[i].setPosition(temp_x, temp_y);
        }
        kol = 0;
        
    }

    void update()
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            if (kol == 0)
            {
                ruch = 2;
            }
            else
            {
                ruch = -2;
            }
            enemies[i].move(ruch, 0.f);
            short temp_x = enemies[i].getPosition().x;
            if (temp_x < 0 or temp_x > w - 33)
            {
                kol = 1 - kol;
                for (int j = 0; j <= enemies.size(); j++)
                {
                    enemies[j].move(0, 20.f);
                }
            }
        }
    }

    void draw(RenderWindow &window)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i]);
        }
    }
};

class Bullet
{
public:
    Texture txt;
    Sprite bullet;
    vector<Sprite> bullets;
    Text text;
    Font font;
    int lb;
    unsigned char relod;
    int relod_time;

    void init()
    {
        txt.loadFromFile("bullet.png");
        bullet.setTexture(txt);
        bullet.setTextureRect(IntRect(0, 0, 14, 20));
        font.loadFromFile("font.ttf");
        text.setFont(font);
        text.setFillColor(Color::Red);
        text.setCharacterSize(50);
        text.setPosition(0, 50);
        relod = 0;
        relod_time = 73;
    }

    void draw(RenderWindow &window)
    {

        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }
        window.draw(text);
    }

    void update()
    {
        // usuwanie niepotrzebnych bulletow
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(0.f, -10.f);
            int temp_y = bullets[i].getPosition().y;
            if (temp_y < 0)
            {
                bullets.erase(bullets.begin() + i);
            }
            lb = bullets.size();
            string n = to_string(lb);
            text.setString(n);
        }
    }
};

class Player
{

public:
    Texture statek;
    Sprite ziut;
    short left = 0;
    short right = 0;

    void init()
    {
        statek.loadFromFile("ziut.png");
        ziut.setTexture(statek);
        ziut.setTextureRect(IntRect(0, 0, 64, 64));
        ziut.setPosition(w / 2 - 7, h - 64);
    }

    void update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Left))
            ziut.move(-10, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right))
            ziut.move(10, 0);
    }

    void kolizja()
    {
        short x = ziut.getPosition().x;
        short y = ziut.getPosition().y;
        if (x > w - 64)
            ziut.move(-10, 0);
        if (x <= 0)
            ziut.move(10, 0);
    }

    void draw(RenderWindow &i_window)
    {
        i_window.draw(ziut);
    }
};

int main()
{
    // tworzenie okna z danym tytułem i rozmiarem
    RenderWindow window(VideoMode(w, h), "INWAZJA OBCYCH - POWRÓT WYRAZEN ALGEBRAICZNYCH");

    // ustawienie limitu fps na 60
    window.setFramerateLimit(60);

    // tworzenie gracza i pociskuw uwu
    Bullet pocisk;
    pocisk.init();
    Player player;
    player.init();
    Enemy enemy;
    enemy.init();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            // wychodzenie z okna krzyzykiem i esc
            if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        // strzelanie
        if (0 == pocisk.relod)
        {
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                pocisk.relod = pocisk.relod_time;
                pocisk.bullet.setPosition(player.ziut.getPosition().x + 32-7, player.ziut.getPosition().y);
                pocisk.bullets.push_back(pocisk.bullet);
            }
        }
        else
        {
            pocisk.relod--;
        }
        player.update();
        pocisk.update();
        enemy.update();
        player.kolizja();

        window.clear();
        pocisk.draw(window);
        player.draw(window);
        enemy.draw(window);
        window.display();
    }
}