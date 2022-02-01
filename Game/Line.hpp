#ifndef PROJECT_GAME_LINE_HPP
#define PROJECT_GAME_LINE_HPP

#include "SFML/Graphics.hpp"
#include <iostream>



struct axisIntersection{
    bool x;
    bool y;
};

struct formula{
    float rc;
    float offset;

    float get_y_intersection(const sf::Vector2f & reference_point) {
        float y = (rc * reference_point.x) + offset;

        return y;
    }

    float get_x_intersection(const sf::Vector2f & reference_point) {
//        rc * x + offset = reference_point.y;
//        rc * x = reference_point.y + (offset * -1);
        float x = (reference_point.y + (offset * -1)) / rc;

        return x;
    }
};


class Line {
private:
    sf::Vector2f A;
    sf::Vector2f B;

public:
    Line(const sf::Vector2f & pointA = sf::Vector2f {0.0, 0.0}, const sf::Vector2f & pointB = sf::Vector2f {0.0, 0.0});

    void setPointA(const sf::Vector2f & pointA);
    void setPointA(const float & x, const float & y);

    void setPointB(const sf::Vector2f & pointB);
    void setPointB(const float & x, const float & y);

    formula calculateFormula();

    axisIntersection intersects(const sf::Vector2f & reference_point);



};


#endif //PROJECT_GAME_LINE_H
