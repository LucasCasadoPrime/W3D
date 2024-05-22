#include "../include/StartMenu.hpp"

StartMenu::StartMenu(sf::RenderWindow &window) {
    const int width = window.getSize().x;
    const int height = window.getSize().y;


    if (!titleFont.loadFromFile("./assets/ttf/title.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if (!otherFont.loadFromFile("./assets/ttf/other.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if (!backgroundImage.loadFromFile("./assets/images/menu.jpg")) {
        std::cerr << "Error loading image" << std::endl;
    }

    if (!music.openFromFile("./assets/music/menu.ogg")) {
        std::cerr << "Error loading music" << std::endl;
    }
    music.setLoop(true);
    music.play();

    backgroundTexture.loadFromImage(backgroundImage);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(width / backgroundSprite.getLocalBounds().width, height / backgroundSprite.getLocalBounds().height);

    sf::Text title;
    title.setFont(titleFont);
    title.setString("LucasTer");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(width / 2 - 150, height / (MAX_NUMBER_OF_ITEMS + 1) * 0.5));

    sf::Text startGame;
    startGame.setFont(otherFont);
    startGame.setString("Start Game");
    startGame.setCharacterSize(24);
    startGame.setFillColor(sf::Color::Red);
    startGame.setPosition(sf::Vector2f(width / 2 - 80, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    sf::Text options;
    options.setFont(otherFont);
    options.setString("Options");
    options.setCharacterSize(24);
    options.setFillColor(sf::Color::White);
    options.setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    sf::Text exit;
    exit.setFont(otherFont);
    exit.setString("Exit");
    exit.setCharacterSize(24);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(sf::Vector2f(width / 2 - 30, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menuItems.push_back(title);
    menuItems.push_back(startGame);
    menuItems.push_back(options);
    menuItems.push_back(exit);

    selectedItemIndex = 1;
}

StartMenu::~StartMenu() {
}

void StartMenu::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
    for (int i = 0; i < menuItems.size(); i++) {
        window.draw(menuItems[i]);
    }
}

void StartMenu::moveUp() {
    if (selectedItemIndex - 1 >= 1) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void StartMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int StartMenu::getSelectedItemIndex() {
    return selectedItemIndex;
}