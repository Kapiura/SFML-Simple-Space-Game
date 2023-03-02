#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <array>
#include <random>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

const int h = 800;
const int w = 1000;
class Player;
class Bullet;
class Aster;
class Apteczka;
int gra;
int pkt;
int asterspeed = 5;

class Aster
{
public:
    Texture txt;
    Sprite aster;
    vector<Sprite> asters;

    void init()
    {
        txt.loadFromFile("aster.png");
        aster.setTexture(txt);
    }

    void draw(RenderWindow &window)
    {

        for (int i = 0; i < asters.size(); i++)
        {
            window.draw(asters[i]);
        }
    }

    void update()
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
};
class Player
{

public:
    Texture statek;
    Sprite ziut;
    short left = 0;
    short right = 0;
    short hp = 3;

    Sprite health;
    Texture hpp;

    short sy;

    void init()
    {
        statek.loadFromFile("ziut.png");
        ziut.setTexture(statek);
        ziut.setTextureRect(IntRect(0, 0, 64, 64));
        ziut.setPosition(w / 2 - 7, h - 64);

        hpp.loadFromFile("health.png");
        health.setTexture(hpp);
        sy = 0;
        health.setTextureRect(IntRect(0, sy, 26, 7));
        health.setPosition(10, 54);
        health.scale(5, 5);
    }

    void update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Left))
            ziut.move(-10, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right))
            ziut.move(10, 0);
        short x = ziut.getPosition().x;
        short y = ziut.getPosition().y;
        if (x > w - 64)
            ziut.move(-10, 0);
        if (x <= 0)
            ziut.move(10, 0);
        health.setTextureRect(IntRect(0, sy, 26, 7));
    }

    void draw(RenderWindow &window)
    {
        window.draw(ziut);
        window.draw(health);
    }
};

class Bullet
{
public:
    Texture txt;
    Sprite bullet;
    vector<Sprite> bullets;
    int lb;
    unsigned char relod;
    int relod_time;

    void init()
    {
        txt.loadFromFile("bullet.png");
        bullet.setTexture(txt);
        bullet.setTextureRect(IntRect(0, 0, 14, 20));
        relod = 0;
        relod_time = 40;
    }

    void draw(RenderWindow &window)
    {

        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }
    }

    void update(Player &player)
    {
        // strzelanie
        if (0 == relod)
        {
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                relod = relod_time;
                bullet.setPosition(player.ziut.getPosition().x + 25, player.ziut.getPosition().y);
                bullets.push_back(bullet);
            }
        }
        else
        {
            relod--;
        }
        // usuwanie niepotrzebnych bulletow
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
};

void kolba(Bullet &pocisk, Aster &aster)
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
                    pkt += 1;
                }
            }
        }
    }
}
void kolsa(Aster &aster, Player &player)
{
    for (int z = 0; z < 64; z++)
    {
        int temp_xb = player.ziut.getPosition().x + z;
        int temp_yb = player.ziut.getPosition().y + z;
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
    if (player.hp <= 0)
    {
        gra = 2;
    }
}

class Pkt
{
public:
    Font font;
    Text text;
    std::ostringstream ss;

    void init()
    {

        font.loadFromFile("font.ttf");
        text.setFont(font);
        text.setString("Hello World");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(10, 10);
    }
    void update()
    {
        std::string str = "Punkty: " + std::to_string(pkt);
        text.setString(str);
    }
    void draw(RenderWindow &window, std::ostringstream &ss, Text &text)
    {
        window.draw(text);
    }
};

class Menu
{
public:
    Text text;
    Font font;
    Sprite btn;
    Texture btnt;

    void init()
    {
        btnt.loadFromFile("btn.png");
        btn.setTexture(btnt);
        btn.setPosition(375, 400);

        font.loadFromFile("font.ttf");
        text.setFont(font);
        text.setFillColor(Color::Red);
        text.setCharacterSize(50);
        text.setString("SPACE SHOOTER");
        text.setPosition(200, 200);
    }

    void update(RenderWindow &window)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            int px = btn.getPosition().x + (250 / 2);
            int py = btn.getPosition().y + (150 / 2);
            int mx = Mouse::getPosition(window).x;
            int my = Mouse::getPosition(window).y;
            if ((px - mx) * (px - mx) + (py - my) * (py - my) < 250 * 150)
            {
                gra = 1;
            }
        }
    }
    void draw(RenderWindow &window)
    {
        window.draw(text);
        window.draw(btn);
    }
};

class Restart
{
public:
    Text text;
    Font font;
    Sprite btn;
    Texture btnt;
    std::ostringstream ss;

    Text pkkt;

    void init()
    {
        btnt.loadFromFile("btn1.png");
        btn.setTexture(btnt);
        btn.setPosition(375, 300);

        font.loadFromFile("font.ttf");
        text.setFont(font);
        text.setFillColor(Color::Red);
        text.setCharacterSize(50);
        text.setString("GAME OVER");
        text.setPosition(300, 200);

        font.loadFromFile("font.ttf");
        pkkt.setFont(font);
        pkkt.setFillColor(Color::Red);
        pkkt.setCharacterSize(50);

        pkkt.setPosition(320, 500);
    }

    void draw(RenderWindow &window)
    {
        std::string str = "Punkty: " + std::to_string(pkt);
        pkkt.setString(str);
        window.draw(text);
        window.draw(pkkt);
        window.draw(btn);
    }
};

class BackGround1
{
public:
    Texture txt;
    Sprite aster;
    vector<Sprite> asters;

    void init()
    {
        txt.loadFromFile("tlo1.png");
        aster.setTexture(txt);
    }

    void draw(RenderWindow &window)
    {

        for (int i = 0; i < asters.size(); i++)
        {
            window.draw(asters[i]);
        }
    }

    void update()
    {
        aster.setPosition((rand() % ((w - 64) + 1)), 0);
        if ((rand() % (50 + 1)) % 10 == 0)
        {
            asters.push_back(aster);
        }
        for (int i = 0; i < asters.size(); i++)
        {
            asters[i].move(0.f, 10.f);
            int temp_y = asters[i].getPosition().y;
            if (temp_y > h)
            {
                asters.erase(asters.begin() + i);
            }
        }
    }
};

class Apteczka
{
public:
    Texture txt;
    Sprite aster;
    vector<Sprite> asters;

    void init()
    {
        txt.loadFromFile("apteczka.png");
        aster.setTexture(txt);
    }

    void draw(RenderWindow &window)
    {

        for (int i = 0; i < asters.size(); i++)
        {
            window.draw(asters[i]);
        }
    }

    void update()
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

    void kolizja(Player &player)
    {
        for (int z = 0; z < 64; z++)
        {
            int temp_xb = player.ziut.getPosition().x + z;
            int temp_yb = player.ziut.getPosition().y + z;
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
                        pkt += 3;
                    }
                }
            }
        }
    }
};

void restart(Aster &aster, Bullet &pocisk, Player &player, Apteczka &apt)
{
    aster.asters.clear();
    pocisk.bullets.clear();
    apt.asters.clear();
    player.ziut.setPosition(w / 2 - 7, h - 64);
    player.sy = 0;
}

int main()
{
    gra = 0;
    srand(time(NULL));
    // tworzenie okna z danym tytułem i rozmiarem
    RenderWindow window(VideoMode(w, h), "Asteroidki i takie tam glupotki");

    // ustawienie limitu fps na 60
    window.setFramerateLimit(60);

    Pkt punkty;
    punkty.init();
    Bullet pocisk;
    pocisk.init();
    Player player;
    player.init();
    Aster aster;
    aster.init();
    Menu menu;
    menu.init();
    Restart res;
    res.init();
    BackGround1 back;
    back.init();
    Apteczka apt;
    apt.init();
    pkt = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            // wychodzenie z okna krzyzykiem i esc
            if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        switch (gra)
        {
        case 0:
            back.update();
            window.clear(sf::Color{64, 92, 133, 150});
            back.draw(window);
            menu.update(window);
            menu.draw(window);
            window.display();
            break;
        case 1:
            aster.aster.setPosition((rand() % ((w - 64) + 1)), -64);
            if ((rand() % (50 + 1)) % 47 == 0)
            {
                aster.asters.push_back(aster.aster);
            }

            player.update();
            pocisk.update(player);
            aster.update();
            back.update();
            punkty.update();
            kolba(pocisk, aster);
            kolsa(aster, player);
            apt.update();
            apt.kolizja(player);

            window.clear(sf::Color{80, 49, 97, 255});
            apt.draw(window);
            back.draw(window);
            punkty.draw(window, punkty.ss, punkty.text);
            pocisk.draw(window);
            player.draw(window);
            aster.draw(window);
            window.display();
            break;
        case 2:
            back.update();
            window.clear(sf::Color{64, 92, 133, 255});
            back.draw(window);
            res.draw(window);
            window.display();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                int px = res.btn.getPosition().x + (250 / 2);
                int py = res.btn.getPosition().y + (150 / 2);
                int mx = Mouse::getPosition(window).x;
                int my = Mouse::getPosition(window).y;
                if ((px - mx) * (px - mx) + (py - my) * (py - my) < 250 * 150)
                {
                    gra = 1;
                    pkt = 0;
                    player.hp = 3;
                    restart(aster, pocisk, player, apt);
                }
            }
            break;
        }
    }
}
