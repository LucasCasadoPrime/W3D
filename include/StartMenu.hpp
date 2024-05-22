#ifndef STARTMENU_HPP
#define STARTMENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#define MAX_NUMBER_OF_ITEMS 3

enum MenuOption {
    START_GAME,
    OPTIONS,
    EXIT,
    NONE
};

class StartMenu {
public:
    StartMenu(sf::RenderWindow &window);
    ~StartMenu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex();

private:
    int selectedItemIndex;
    std::vector<sf::Text> menuItems;
    sf::Font titleFont;
    sf::Font otherFont;
    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 
    sf::Music music;
};

#endif // STARTMENU_HPP