#ifndef ILEVEL_HPP
#define ILEVEL_HPP

#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

class ILevel {
public:
    virtual Map getMap() const = 0;
    virtual int getTexHeight() const = 0;
    virtual int getTexWidth() const = 0;
    virtual int getScreenHeight() const = 0;
    virtual int getScreenWidth() const = 0;
    virtual sf::Uint32** getBuffer() = 0;
    virtual const int* getSpriteOrder() const = 0;
    virtual const double* getSpriteDistance() const = 0;

    virtual void setMap(Map map) = 0;
    virtual void setTexHeight(int texHeight) = 0;
    virtual void setTexWidth(int texWidth) = 0;
    virtual void setScreenHeight(int screenHeight) = 0;
    virtual void setScreenWidth(int screenWidth) = 0;
    virtual void setBuffer(sf::Uint32 buffer[640][480]) = 0;
    virtual void setSpriteOrder(int* spriteOrder) = 0;
    virtual void setSpriteDistance(double* spriteDistance) = 0;
    
    virtual void loadTextures(const std::vector<std::string> textureFiles) = 0;

    virtual ~ILevel() {}
    
    Map map;
    int texWidth = TEX_WIDTH;
    int texHeight = TEX_HEIGHT;
    int screenHeight = SCREEN_HEIGHT;
    int screenWidth = SCREEN_WIDTH;
    sf::Uint32 buffer[SCREEN_WIDTH][SCREEN_HEIGHT];
    double ZBuffer[SCREEN_WIDTH];
    int spriteOrder[19]; // todo the code can be optimized by using unfixed size
    double spriteDistance[19]; // todo the code can be optimized by using unfixed size
    std::vector<sf::Uint32> textures[11]; // todo the code can be optimized by using unfixed size
};

#endif // ILEVEL_HPP
