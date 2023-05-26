#include "headers/menu.h"

// main menu
void Menu::update(sf::RenderWindow& window)
{
    // checking in menu if user clicked play button
    // if yes, then game state is going to case 2 - start playing
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int px = btn.getPosition().x + (250 / 2);
        int py = btn.getPosition().y + (150 / 2);
        int mx = sf::Mouse::getPosition(window).x;
        int my = sf::Mouse::getPosition(window).y;
        if ((px - mx) * (px - mx) + (py - my) * (py - my) < 250 * 150)
        {
            game_state_number = 1;
        }
    }
}
// function that draw main menu on user's screen
void Menu::draw(sf::RenderWindow& window)
{
    window.draw(text);
    window.draw(btn);
}

// restart menu
// It is like main menu but it appears when user die
void Restart::draw(sf::RenderWindow& window)
{
    std::string str = "Punkty: " + std::to_string(points);
    pkkt.setString(str);
    window.draw(text);
    window.draw(pkkt);
    window.draw(btn);
}

// background
// drawing funky fresh particles
void BackGround::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < asters.size(); i++)
    {
        window.draw(asters[i]);
    }
}

// functions that create and deleting sliding parcitles in background
void BackGround::update()
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

//points
// updaing string of user's points
void Points::update()
{
    std::string str = "Punkty: " + std::to_string(points);
    text.setString(str);
}
// drawing them on screen
void Points::draw(sf::RenderWindow& window, std::ostringstream& ss, sf::Text& text)
{
    window.draw(text);
}