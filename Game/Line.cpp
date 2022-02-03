#include "Line.hpp"


Line::Line(const sf::Vector2f &pointA, const sf::Vector2f &pointB):
    A(pointA),
    B(pointB)
{}

Line::Formula Line::calculateFormula() const {
    float dx = A.x - B.x;
    float dy = A.y - B.y;

    float rc = dy/dx;
    float offset = A.y + ( ( rc * A.x ) * -1 );

    return {rc, offset};
}

std::vector<sf::Vector2f> &Line::getPoints() {
    Formula f = calculateFormula();
    int amount = A.x > B.x ? A.x - B.x : B.x - A.x;
    int startX = A.x < B.x ? A.x : B.x;

    for (int i = 1; i < amount+1; i++) {
        float x = startX + i;
        pointsArray.emplace_back( x, f.getYaxisIntersection(x) );
    }
    return pointsArray;
}
