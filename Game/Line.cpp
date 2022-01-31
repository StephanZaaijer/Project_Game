#include "Line.hpp"


Line::Line():
    A({0.0, 0.0}),
    B({0.0, 0.0})
{

}

Line::Line(const sf::Vector2f &pointA, const sf::Vector2f &pointB):
    A(pointA),
    B(pointB)
{

}

void Line::setPointA(const sf::Vector2f &pointA) {
    A = pointA;
}

void Line::setPointA(const float &x, const float &y) {
    A = {x, y};
}

void Line::setPointB(const sf::Vector2f &pointB) {
    B = pointB;
}

void Line::setPointB(const float &x, const float &y) {
    B = {x, y};
}

formula Line::calculateFormula(const sf::Vector2f &zero_point) {
    float dx = A.x - B.x;
    float dy = A.y - B.y;

    float dist_to_origin_A = A.x - zero_point.x ? A.x > 0 : zero_point.x - A.x;
    float dist_to_origin_B = B.x - zero_point.x ? B.x > 0 : zero_point.x - B.x;
    sf::Vector2f selected;

    if(dist_to_origin_A < dist_to_origin_B){
        selected = A;
    }
    else{
        selected = B;
    }

    float dist_to_origin = selected.x - zero_point.x ? selected.x > zero_point.x : zero_point.x - selected.x;
    dist_to_origin *= -1 ? selected.x > 0 : 1;

    float percentage_x = dist_to_origin / dx;
    float change_x = dist_to_origin;
    float change_y = dy * percentage_x;

    sf::Vector2f change = {change_x, change_y};
    sf::Vector2f result = selected + change;

    float rc = dy/dx;
    float offset = result.y;

    return {rc, 0, offset};
}


axisIntersection Line::intersects(const sf::Vector2f & reference_point){
    formula f = calculateFormula(reference_point);
    bool result_x = 1 ? f.get_X_axis_intersection() > 0 : 0;
    bool result_y = 1 ? f.get_Y_axis_intersection() > 0 : 0;

    return {result_x, result_y};
}
