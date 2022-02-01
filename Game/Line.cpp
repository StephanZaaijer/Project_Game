#include "Line.hpp"


Line::Line(const sf::Vector2f &pointA, const sf::Vector2f &pointB):
    A(pointA),
    B(pointB)
{

}

formula Line::calculateFormula() {
    std::cout << "pointA_original : \t" << "(" << A.x << ", " << A.y << ")" << "\n";
    std::cout << "pointB_original : \t" << "(" << B.x << ", " << B.y << ")" << "\n\n";


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

    float result_x = f.get_x_intersection(reference_point.x);
    float result_y = f.get_y_intersection(reference_point.y);

    bool x = result_x > reference_point.x;
    bool y = result_y < reference_point.y; // lower than because y-axis is inverted. lower y means higher up in the screen.

//    std::cout << f.get_Y_axis_intersection() << "\n";
    std::cout << x << " " << y << "\n";

    return {x, y};
}

std::vector<sf::Vector2f> &Line::get_points() {
    formula f = calculateFormula();
    int amount = A.x > B.x ? A.x - B.x : B.x - A.x;
    int start_x = A.x < B.x ? A.x : B.x;
    for (int i = 1; i < amount+1; i++) {
        float x = start_x + i;
        points_array.push_back({ x, f.get_y_intersection(x) });
    }
    return points_array;
}
