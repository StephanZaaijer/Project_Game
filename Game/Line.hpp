#ifndef PROJECT_GAME_LINE_HPP
#define PROJECT_GAME_LINE_HPP

#include "SFML/Graphics.hpp"

/// @file Line.hpp
/// @brief
/// Project_Game: This Line enables us to find intersections with diagonal lines.

/// @brief Line to create a formula between 2 points.
class Line {
private:
    /// @brief
    /// This Formula struct is used to store information of a calculated formula.
    /// @details
    /// This struct stores the directional coefficient and the offset from origin.
    /// These are used to calculate equations as a formula.
    struct Formula {
        float rc;
        float offset;

        /// @brief
        /// This function calculates the Y value of a point on the line corresponding to a given X value.
        /// \param x This is the X value of the the point you want to calculate.
        ///
        /// \return A float value representing the Y value of the point.
        float getYaxisIntersection(const float & x) const{
            float y = (rc * x) + offset;
            return y;
        }

        /// @brief
        /// This function calculates the X value of a point on the line corresponding to a given Y value.
        /// \param y This is the Y value of the the point you want to calculate.
        ///
        /// \return A float value representing the X value of the point.
        float getXaxisIntersection(const float & y) const {
            float x = (y + (offset * -1)) / rc;
            return x;
        }
    };

    /// @brief
    /// This function calculates the directional coefficient and the offset to create a formula.
    /// \return this function returns a complete formula.
    Line::Formula calculateFormula() const;

    std::vector<sf::Vector2f> pointsArray = {};
    sf::Vector2f A;
    sf::Vector2f B;
public:

    /// @brief
    /// This constructor constructs an object of the Line class.
    /// \param pointA This is the first point of the line.
    /// \param pointB This is the second point of the line.
    explicit Line(const sf::Vector2f & pointA = sf::Vector2f {0.0, 0.0}, const sf::Vector2f & pointB = sf::Vector2f {0.0, 0.0});

    /// @brief
    /// This function creates a vector of a list of points on the line.
    /// @details
    /// This function calculates for every X value between the points a point on the line.
    std::vector<sf::Vector2f> & getPoints();

};


#endif //PROJECT_GAME_LINE_HPP