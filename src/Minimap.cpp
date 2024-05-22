#include "../include/MiniMap.hpp"

void MiniMap::render(sf::RenderWindow& window, int playerPosX, int playerPosY) {
    sf::RectangleShape background(sf::Vector2f(map.getWidth() * tileSize / 1.5, map.getHeight() * tileSize / 1.5));
    background.setFillColor(sf::Color(139, 69, 19));
    background.setPosition(miniMapOffset);
    window.draw(background);

    for(int x = 0; x < map.getWidth(); x++) {
        for(int y = 0; y < map.getHeight(); y++) {
            int flippedX = map.getWidth() - 1 - x;

            if(map.getMap()[x][y] != 0) {
                sf::RectangleShape rectangle(sf::Vector2f(tileSize / 1.5, tileSize / 1.5));
                rectangle.setFillColor(sf::Color(105, 105, 105));
                rectangle.setPosition(miniMapOffset.x + flippedX * tileSize / 1.5, miniMapOffset.y + y * tileSize / 1.5);
                window.draw(rectangle);
            }

            if (x == playerPosX && y == playerPosY) {
                sf::RectangleShape player(sf::Vector2f(tileSize / 1.5, tileSize / 1.5));
                player.setFillColor(sf::Color::Red);
                player.setPosition(miniMapOffset.x + flippedX * tileSize / 1.5, miniMapOffset.y + y * tileSize / 1.5);
                window.draw(player);
            }
        }
    }
}


