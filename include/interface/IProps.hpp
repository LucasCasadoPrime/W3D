#ifndef IPROPS_HPP
#define IPROPS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class IProps {
public:
    virtual ~IProps() {}

    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual int getTexture() const = 0;

    virtual void setX(double x) = 0;
    virtual void setY(double y) = 0;
    virtual void setTexture(int texture) = 0;

    double x;
    double y;
    int texture;
};

#endif // IPROPS_HPP
