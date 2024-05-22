#ifndef IMAP_HPP
#define IMAP_HPP

#include "Props.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

class IMap {
public:

    // Getters
    virtual int getHeight() const = 0;
    virtual int getWidth() const = 0;
    virtual int getPlayerStartPosX() const = 0;
    virtual int getPlayerStartPosY() const = 0;
    virtual int** getMap() const = 0;
    virtual int getIndexFloorTexture() const = 0;
    virtual int getIndexCeilingTexture() const = 0;
    virtual std::vector<Props> getProps() const = 0;

    // Setters
    virtual void setHeight(int height) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setPlayerStartPosX(int playerStartPosX) = 0;
    virtual void setPlayerStartPosY(int playerStartPosY) = 0;
    virtual void setMap(int** map) = 0;
    virtual void setIndexFloorTexture(int indexFloorTexture) = 0;
    virtual void setIndexCeilingTexture(int indexCeilingTexture) = 0;
    virtual void setProps(std::vector<Props> props) = 0;

    int** map;
    int playerStartPosX;
    int playerStartPosY;
    int width;
    int height;
    int floorTexture;
    int ceilingTexture;
    std::vector<Props> props;
};

#endif // IMAP_HPP