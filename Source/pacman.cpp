#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

int main()
{
    Text text;
    Font font;
    Sprite btn;
    Texture btnt;

    btnt.loadFromFile("btn.png");
    btn.setTexture(btnt);
    btn.setPosition(375, 400);

    font.loadFromFile("font.ttf");
    text.setFont(font);
    text.setFillColor(Color::Red);
    text.setCharacterSize(50);
    text.setString("SPACE SHOOTER");
    text.setPosition(200, 200);

    RenderWindow window(VideoMode(1000, 800), "Lista nr 7");
    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        window.clear(Color::White);
        window.draw(text);
        window.draw(btn);
        window.display();
    }
    return 0;
}