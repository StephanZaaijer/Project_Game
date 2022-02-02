#include "Line.hpp"


Line::Line(const sf::Vector2f &pointA, const sf::Vector2f &pointB):
    A(pointA),
    B(pointB)
{}

formula Line::calculateFormula() const {
    float dx = A.x - B.x;
    float dy = A.y - B.y;

    float rc = dy/dx;
    float offset = A.y + ( ( rc * A.x ) * -1 );

    return {rc, offset};
}

std::vector<sf::Vector2f> &Line::get_points() {
    formula f = calculateFormula();
    int amount = A.x > B.x ? A.x - B.x : B.x - A.x;
    int start_x = A.x < B.x ? A.x : B.x;

    for (int i = 1; i < amount+1; i++) {
        float x = start_x + i;
        points_array.emplace_back( x, f.get_y_intersection(x) );
    }
    return points_array;
}
