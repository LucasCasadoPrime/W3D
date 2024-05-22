#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

#include "../include/Level.hpp"
#include "../include/Player.hpp"
#include <cmath>
#include <algorithm>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>

class RayCaster {
public:
    void sortSprites(int* order, double* dist, int amount);
    void castRays(sf::RenderWindow& window, Level& level, Player& player);
    void castFloorAndCeiling(sf::RenderWindow& window, Player& player, Level& level);
    void castSprites(sf::RenderWindow& window, Level& level, Player& player);
    void updateSpriteDistances(Level& level, Player& player);
    void castWalls(sf::RenderWindow& window, Level& level, Player& player);
    void transformSprite(const Player& player, const Props& sprite, double& transformX, double& transformY, int& spriteScreenX, Level& level);
    void drawSprite(int spriteScreenX, double transformY, const Props& sprite, Level& level);
};

#endif // RAYCASTER_HPP
