#ifndef PROJECT_GAME_OBSTACLE_H
#define PROJECT_GAME_OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>

/// @file Obstacle.hpp
/// @brief
/// Project_Game: Defines the abstract class Obstacle

/// @brief
/// Abstract base class for objects that are obstacles.
class Obstacle {
private:
    identifier I;

public:
    /// @brief
    /// Obstacle constructor.
    /// \param I is an identifier used to identify the deriving object
    Obstacle(const identifier & I): I(I) {}

    /// @brief
    /// Returns the position of the object.
    /// @details
    /// This is a virtual function which has to be implemented by deriving classes
    /// \return Returns a sf::Vector2f with the coordinates of the object.
    virtual sf::Vector2f getPosition() = 0;

    /// @brief
    /// Used to initialize the values of the object.
    /// @details
    /// This is a virtual function which has to be implemented by deriving classes to define what values should be initialized
    virtual void spawn() = 0;

    /// @brief
    /// Used to move the object.
    /// @details
    /// This is a virtual function which has to be implemented by deriving classes to define how the object should be moving with given parameter
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate
    virtual void move(sf::Vector2f moveBy) = 0;

    /// @brief
    /// Used to draw the object.
    /// @details
    /// This is a virtual function which has to be implemented by deriving classes to define how the object should be drawn
    virtual void draw() const = 0;

    /// @brief
    /// Returns the global bounds of the object.
    /// @details
    /// This is a virtual function which has to be implemented by deriving classes
    /// \return Returns a sf::Floatrect of the object.
    virtual sf::FloatRect getBounds() = 0;

    // TODO: Write doxygen
    virtual sf::Vector2f getPoint(const int & index){
        return {};
    }

    // TODO: Write doxygen
    virtual Spike_facing getFace(){
        return neither;
    }

    /// @brief
    /// Returns the identifier of the deriving class to identify the object.
    /// \return Returns the identifier of the object.
    identifier getID(){
        return I;
    }
};

#endif //PROJECT_GAME_OBSTACLE_H
