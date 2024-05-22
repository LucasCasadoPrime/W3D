#ifndef MINIMAP_HPP
#define MINIMAP_HPP

#include "Map.hpp"


class MiniMap {
public:
    // Constructor
    MiniMap(const Map& map, sf::RenderWindow& window, int tileSize, sf::Vector2f miniMapOffset)
        : map(map), window(window), tileSize(tileSize), miniMapOffset(miniMapOffset) {}

    // Destructor
    ~MiniMap() = default;

    // Getters
    int getPlayerPosX() const { return playerPosX; }
    int getPlayerPosY() const { return playerPosY; }
    const Map& getMap() const { return map; }
    bool getIsDisplayed() const { return isDisplayed; }

    // Setters
    void setPlayerPosX(int playerPosX) { this->playerPosX = playerPosX; }
    void setPlayerPosY(int playerPosY) { this->playerPosY = playerPosY; }
    void setIsDisplayed(bool isDisplayed) { this->isDisplayed = isDisplayed; }

    // Methods
    void render(sf::RenderWindow& window, int playerPosX, int playerPosY);

private:
    int playerPosX;
    int playerPosY;
    const Map& map;
    sf::RenderWindow& window;
    int tileSize;
    sf::Vector2f miniMapOffset;
    bool isDisplayed;
};

#endif // MINIMAP_HPP