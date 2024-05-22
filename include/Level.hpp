#ifndef LEVELTWO_HPP
#define LEVELTWO_HPP

#include "ILevel.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

class Level : public ILevel {
public:
    Level(const std::vector<std::string> textureFiles, Map map) {

        this->map = map;
        loadTextures(textureFiles);
    }

    // Getters
    
    Map getMap() const {
        return map;
    }

    int getTexHeight() const {
        return texHeight;
    }

    int getTexWidth() const {
        return texWidth;
    }

    int getScreenHeight() const {
        return screenHeight;
    }

    int getScreenWidth() const {
        return screenWidth;
    }

    sf::Uint32** getBuffer() {
        return (sf::Uint32**)buffer;
    }

    const int* getSpriteOrder() const {
        return spriteOrder;
    }

    const double* getSpriteDistance() const {
        return spriteDistance;
    }

    // Setters

    void setMap(Map map) {
        this->map = map;
    }

    void setTexHeight(int texHeight) {
        this->texHeight = texHeight;
    }

    void setTexWidth(int texWidth) {
        this->texWidth = texWidth;
    }

    void setScreenHeight(int screenHeight) {
        this->screenHeight = screenHeight;
    }

    void setScreenWidth(int screenWidth) {
        this->screenWidth = screenWidth;
    }

    void setBuffer(sf::Uint32 buffer[SCREEN_WIDTH][SCREEN_HEIGHT]) {
        for(int x = 0; x < screenWidth; x++) {
            for(int y = 0; y < screenHeight; y++) {
                this->buffer[x][y] = buffer[x][y];
            }
        }
    }

    void setSpriteOrder(int* spriteOrder) {
        for(int i = 0; i < 19; i++) {
            this->spriteOrder[i] = spriteOrder[i];
        }
    }

    void setSpriteDistance(double* spriteDistance) {
        for(int i = 0; i < 19; i++) {
            this->spriteDistance[i] = spriteDistance[i];
        }
    }

    void loadTextures(const std::vector<std::string> textureFiles) {
        for(int i = 0; i < textureFiles.size(); i++) {
            sf::Image img;
            img.loadFromFile(textureFiles[i]);
            textures[i].resize(texHeight * texWidth);
            for(int y = 0; y < texHeight; y++) {
                for(int x = 0; x < texWidth; x++) {
                    textures[i][texWidth * y + x] = img.getPixel(x, y).toInteger();
                }
            }
        }
    }

    private:

    int getIndex(std::vector<std::string> textureFiles, std::string texture) {
        for(int i = 0; i < textureFiles.size(); i++) {
            if(textureFiles[i] == texture) {
                return i;
            }
        }
        return -1;
    }

};
#endif // LEVELTWO_HPP
