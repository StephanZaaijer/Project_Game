#ifndef PROJECT_GAME_DEATHWALL_H
#define PROJECT_GAME_DEATHWALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include <utility>
#include "Obstacle.hpp"

/// @file Deathwall.hpp
/// @brief
/// Project_Game: Defines a Deathwall that derives from obstacle

/// @brief
/// Deathwall class which derives from Obstacle.
class Deathwall : public Obstacle {
private:
    GameDataReference gameData;
    sf::RectangleShape deathwall;
    sf::Vector2f position;
public:
    /// @brief
    /// Used to construct deathwall object.
    /// @details
    /// initializes the value of je object with the spawn method.
    /// \param game_data is a shared pointer to the GameDataReference where information of the game is stored
    /// \param position is a sf::Vector2f which contains a X and Y coordinate and is used to set the position of the deathwall
    Deathwall(GameDataReference gameData, sf::Vector2f position);

    /// @brief
    /// Returns the position of the deathwall.
    /// \return Returns a sf::Vector2f with the coordinates of the deathwall.
    sf::Vector2f getPosition() override;

    /// @brief
    /// Used to initialize the deathwall with a position, size and color.
    void spawn() override;

    /// @brief
    /// Used to move deathwall object.
    /// @details
    /// Used to move deathwall object by an offset given in the parameter.
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate
    void move(sf::Vector2f moveBy) override;

    /// @brief
    /// Used to draw deathwall object in the window.
    void draw() const override;

    /// @brief
    /// Returns the global bounds of deathwall.
    /// \return Returns a sf::Floatrect of the sf::RectangleShape deathwall.
    sf::FloatRect getBounds() override;
};

#endif //PROJECT_GAME_DEATHWALL_H
