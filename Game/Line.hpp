#ifndef PROJECT_GAME_LINE_HPP
#define PROJECT_GAME_LINE_HPP

#include "SFML/Graphics.hpp"
#include <iostream>

struct Formula {
    float rc;
    float offset;

    float getYaxisIntersection(const float & x) const{
        float y = (rc * x) + offset;
        return y;
    }

    float getXaxisIntersection(const float & y) const {
        float x = (y + (offset * -1)) / rc;
        return x;
    }
};

class Line {
private:
    std::vector<sf::Vector2f> pointsArray = {};

    sf::Vector2f A;
    sf::Vector2f B;

public:
    Line(const sf::Vector2f & pointA = sf::Vector2f {0.0, 0.0}, const sf::Vector2f & pointB = sf::Vector2f {0.0, 0.0});
    Formula calculateFormula() const;
    std::vector<sf::Vector2f> & getPoints();

};


#endif //PROJECT_GAME_LINE_HPP