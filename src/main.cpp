#include "../include/Level.hpp"
#include "../include/RayCaster.hpp"
#include "../include/MiniMap.hpp"
#include "../include/StartMenu.hpp"
#include "../include/Player.hpp"
#include "../include/Props.hpp"
#include <../include/Map.hpp>
#include <iostream>

#define screenWidth 640
#define screenHeight 480

Level initLevelOne() {

    const std::vector<std::string> allTextures = {
        "./assets/textures/wall/bluestone.png",
        "./assets/textures/wall/colorstone.png",
        "./assets/textures/wall/eagle.png",
        "./assets/textures/wall/greystone.png",
        "./assets/textures/wall/mossy.png",
        "./assets/textures/wall/purplestone.png",
        "./assets/textures/wall/redbrick.png",
        "./assets/textures/wall/wood.png",
        "./assets/textures/props/barrel.png",
        "./assets/textures/props/greenlight.png",
        "./assets/textures/props/pillar.png"
    };
    

    std::vector<Props> props = {
        {22.5, 11.5, 10},
        {18.5,4.5, 10},
        {10.0,4.5, 10},
        {10.0,12.5,10},
        {3.5, 6.5, 10},
        {3.5, 20.5,10},
        {3.5, 14.5,10},
        {14.5,20.5,10},

        //row of pillars in front of wall: fisheye test
        {18.5, 10.5, 9},
        {18.5, 11.5, 9},
        {18.5, 12.5, 9},

        //some barrels around the map
        {21.5, 1.5, 8},
        {15.5, 1.5, 8},
        {16.0, 1.8, 8},
        {16.2, 1.2, 8},
        {3.5,  2.5, 8},
        {9.5, 15.5, 8},
        {10.0, 15.1,8},
        {10.5, 15.8,8}
    };

    Map map("./assets/maps/2.txt", 7, 3, props);
    Level level(allTextures, map);

    return level;
}


std::vector<Level> initLevels() {

    Level levelOne = initLevelOne();
    std::vector<Level> levels = {levelOne};

    return levels;
}

void update(sf::RenderWindow& window, Level& level, Player& player, RayCaster& rayCaster) {

    for(int x = 0; x < level.getScreenWidth(); x++) {
        for(int y = 0; y < level.getScreenHeight(); y++) {
            level.buffer[x][y] = 0;
        }
    }

    rayCaster.castRays(window, level, player);
}


void render(sf::Uint8* pixels, Level level, MiniMap miniMap, sf::RenderWindow& window) {
    for(int x = 0; x < level.getScreenWidth(); x++) {
        for(int y = 0; y < level.getScreenHeight(); y++) {
            pixels[(x + y * level.getScreenWidth()) * 4] = (sf::Uint8)(level.buffer[x][y] >> 24);
            pixels[(x + y * level.getScreenWidth()) * 4 + 1] = (sf::Uint8)(level.buffer[x][y] >> 16);
            pixels[(x + y * level.getScreenWidth()) * 4 + 2] = (sf::Uint8)(level.buffer[x][y] >> 8);
            pixels[(x + y * level.getScreenWidth()) * 4 + 3] = (sf::Uint8)(level.buffer[x][y]);
        }
    }
}

void GameLoop(sf::RenderWindow& window) {
    std::vector<Level> levels = initLevels();
    Level currentLevel = levels[0];

    MiniMap miniMap(currentLevel.map, window, 7, sf::Vector2f(10, 10));
    Player player(currentLevel.map.getPlayerStartPosX(), currentLevel.map.getPlayerStartPosY(),-1, 0, 0, 0.66);
    RayCaster rayCaster;

    sf::Texture texture;
    texture.create(screenWidth, screenHeight);
    sf::Sprite sprite(texture);
    sf::Uint8* pixels = new sf::Uint8[screenWidth * screenHeight * 4];

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    miniMap.setIsDisplayed(!miniMap.getIsDisplayed());
                }
            }
        }
        
        update(window, currentLevel, player, rayCaster);
        render(pixels, currentLevel, miniMap, window);
        
        texture.update(pixels);
        window.draw(sprite);

        if (miniMap.getIsDisplayed()) {
            miniMap.render(window, player.posX, player.posY);
        }

        player.setWeapon(Weapon::SHOTGUN);
        window.draw(player.getCurrentWeaponSprite());


        window.display();
    
    }

}

int main() {
    int state = 0;
    
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "RayCaster");

    StartMenu startMenu(window);

    // afficher le menu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    startMenu.moveUp();
                }

                if (event.key.code == sf::Keyboard::Down) {
                    startMenu.moveDown();
                }

                if (event.key.code == sf::Keyboard::Return) {
                    if (startMenu.getSelectedItemIndex() == 1) {
                        state = 1;
                    } else if (startMenu.getSelectedItemIndex() == 3) {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        startMenu.draw(window);
        window.display();

        if (state == 1) {
            GameLoop(window);
        }
    }

    return 0;
}