#ifndef MENU_H
#define MENU_H

// main menu
class Menu
{
public:
    sf::Text text;
    sf::Font font;
    sf::Sprite btn;
    sf::Texture btnt;

    // constructor 
    Menu()
    {
        btnt.loadFromFile("images/btn.png");
        btn.setTexture(btnt);
        btn.setPosition(375, 400);

        font.loadFromFile("fonts/font.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(50);
        text.setString("SPACE SHOOTER");
        text.setPosition(200, 200);
    }

    void update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};


// restart menu

class Restart
{
public:
    sf::Text text;
    sf::Font font;
    sf::Sprite btn;
    sf::Texture btnt;
    std::ostringstream ss;

    sf::Text pkkt;

    Restart()
    {
        btnt.loadFromFile("images/btn1.png");
        btn.setTexture(btnt);
        btn.setPosition(375, 300);

        font.loadFromFile("fonts/font.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(50);
        text.setString("GAME OVER");
        text.setPosition(300, 200);

        font.loadFromFile("fonts/font.ttf");
        pkkt.setFont(font);
        pkkt.setFillColor(sf::Color::Red);
        pkkt.setCharacterSize(50);

        pkkt.setPosition(320, 500);
    }

    void draw(sf::RenderWindow &window);
};

// background

class BackGround
{
public:
    BackGround()
    {
        txt.loadFromFile("images/tlo1.png");
        aster.setTexture(txt);
    }
    sf::Texture txt;
    sf::Sprite aster;
    std::vector<sf::Sprite> asters;
    void draw(sf::RenderWindow &window);
    void update();
};

//pkt

class Points
{
public:
    sf::Font font;
    sf::Text text;
    std::ostringstream ss;

    Points()
    {
        font.loadFromFile("fonts/font.ttf");
        text.setFont(font);
        text.setString("");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(10, 10);
    }
    void update();
    void draw(sf::RenderWindow &window, std::ostringstream &ss, sf::Text &text);
};

#endif