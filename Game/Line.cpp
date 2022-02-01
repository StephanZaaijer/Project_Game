#include "Line.hpp"


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

formula Line::calculateFormula() {
//    std::cout << "zero_point : \t" << "(" << zero_point.x << ", " << zero_point.y << ")" << "\n\n";
    std::cout << "pointA_original : \t" << "(" << A.x << ", " << A.y << ")" << "\n";
    std::cout << "pointB_original : \t" << "(" << B.x << ", " << B.y << ")" << "\n\n";



//    float distance_to_origin_x = A.x - zero_point.x;
//    float distance_to_origin_y = A.y - zero_point.y;
//    sf::Vector2f A_to_origin = {distance_to_origin_x, distance_to_origin_y};
//    std::cout << "point A: \t" << "(" << A_to_origin.x << ", " << A_to_origin.y << ")" << "\n";
//
//    distance_to_origin_x = B.x - zero_point.x;
//    distance_to_origin_y = B.y - zero_point.y;
//    sf::Vector2f B_to_origin = {distance_to_origin_x, distance_to_origin_y};
//    std::cout << "point B: \t" << "(" << B_to_origin.x << ", " << B_to_origin.y << ")" << "\n";



    float dx = A.x - B.x;
    float dy = A.y - B.y;

    float rc = dy/dx;
    std::cout << "RC: \t" << dy << " / " << dx << " = " << rc << "\n";

    float offset = A.y + ( ( rc * A.x ) * -1 );
    std::cout << "offset: \t" << A.y << " + " << " -(" << rc << " * " << A.x << ") = " << offset << "\n\n\n";


    return {rc, offset};
}


axisIntersection Line::intersects(const sf::Vector2f & reference_point){
    formula f = calculateFormula();

    float result_x = f.get_x_intersection(reference_point);
    float result_y = f.get_y_intersection(reference_point);

    bool x = result_x > reference_point.x;
    bool y = result_y < reference_point.y; // lower than because y-axis is inverted. lower y means higher up in the screen.

//    std::cout << f.get_Y_axis_intersection() << "\n";
    std::cout << x << " " << y << "\n";

    return {x, y};
}
