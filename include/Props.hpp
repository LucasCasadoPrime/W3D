#ifndef PROPS_HPP
#define PROPS_HPP

#include "IProps.hpp"

class Props : public IProps {
public:
    Props(double x, double y, int texture) {
        this->x = x;
        this->y = y;
        this->texture = texture;
    }

    ~Props() {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    int getTexture() const {
        return texture;
    }

    void setX(double x) {
        this->x = x;
    }

    void setY(double y) {
        this->y = y;
    }

    void setTexture(int texture) {
        this->texture = texture;
    }
};

#endif // PROPS_HPP