#ifndef PROJECT_GAME_SPIKE_H
#define PROJECT_GAME_SPIKE_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"
#include "Game.hpp"

/// @file Spike.hpp
/// @brief
/// Project_Game: Defines a Spike that derives from obstacle

/// @brief
/// Spike class which derives from Obstacle.
class Spike : public Obstacle {
private:
    GameDataReference gameData;
    sf::ConvexShape triangle;

    spikeFacing facing;
    sf::Vector2f position;

public:
    /// @brief
    /// Used to construct spike object.
    /// @details
    /// Construct and initializes the value of je object with the spawn method.
    /// \param gameData is a shared pointer to the GameDataReference where information of the game is stored.
    /// \param facing is used to define which way the spike is facing.
    /// \param position is a sf::Vector2f which contains a X and Y coordinate and is used to set the position of the deathwall.
    Spike(GameDataReference gameData, spikeFacing facing, sf::Vector2f position);

    /// @brief
    /// Returns the position of the deathwall.
    /// \return Returns a sf::Vector2f with the coordinates of the spike.
    sf::Vector2f getPosition() override;

    /// @brief
    /// Used to initialize the spike with a corner coordinates, position and color.
    void spawn() override;

    /// @brief
    /// Used to move spike object.
    /// @details
    /// Used to move spike object by an offset given in the parameter.
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate
    void move(sf::Vector2f moveBy) override;

    /// @brief
    /// Used to draw spike object in the window.
    void draw() const override;

    /// @brief
    /// Returns the global bounds of spike.
    /// \return Returns a sf::Floatrect of the sf::RectangleShape spike.
    sf::FloatRect getBounds() override;

    /// @brief
    /// Returns the spikeFacing of spike.
    /// \return Returns the spikeFacing of spike.
    spikeFacing getFace() override;

    /// @brief
    /// Get the position of a point.
    /// @details
    /// The returned point is a local coordinate of the shape.
    /// \param index The index of the point you want to extract starting from 0.
    ///
    /// \return Position of the index-th point of the object.
    sf::Vector2f getPoint(const int &index) override;

};


#endif //PROJECT_GAME_SPIKE_H
