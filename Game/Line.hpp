#ifndef PROJECT_GAME_LINE_HPP
#define PROJECT_GAME_LINE_HPP

#include "SFML/Graphics.hpp"

struct axisIntersection{
    bool x;
    bool y;
};

struct formula{
    float rc;
    float x;
    float offset;

    float get_Y_axis_intersection() {
        return offset;
    }

    float get_X_axis_intersection() {
        float right = (offset *= -1);
        return right/rc;
    }
};


class Line {
private:
    sf::Vector2f A;
    sf::Vector2f B;

public:
    Line();
    Line(const sf::Vector2f & pointA, const sf::Vector2f & pointB);

    void setPointA(const sf::Vector2f & pointA);
    void setPointA(const float & x, const float & y);

    void setPointB(const sf::Vector2f & pointB);
    void setPointB(const float & x, const float & y);

    formula calculateFormula(const sf::Vector2f & zero_point);

    axisIntersection intersects(const sf::Vector2f & reference_point);



};


#endif //PROJECT_GAME_LINE_H
