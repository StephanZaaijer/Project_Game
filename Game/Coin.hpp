#ifndef PROJECT_COIN_H
#define PROJECT_COIN_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"

/// @file Coin.hpp
/// @brief
/// Project_Game: Defines a coin object

/// @brief
/// Coin class which contains information of the coin.
class Coin {
private:
    GameDataReference gameData;
    sf::Sprite coin;
public:

    /// @brief
    /// Used to construct coin object.
    /// @details
    /// Used to construct coin object and initializes the object with a texture and scale
    /// \param gameData is a shared pointer to the GameDataReference where information of the game is stored
    Coin(GameDataReference gameData);

    /// @brief
    /// Used to move coin object.
    /// @details
    /// Used to move coin object by an offset given in the parameter.
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate
    void move(sf::Vector2f moveBy);

    /// @brief
    /// Used to position the coin object.
    /// @details
    /// Used to overwrite the position of the coin with the given the parameter.
    /// \param position is a sf::Vector2f which contains a X and Y coordinate
    void setPosition(sf::Vector2f position);

    /// @brief
    /// Returns coin sprite.
    /// \return Returns the sf::sprite of coin.
    sf::Sprite getCoin();

    /// @brief
    /// Returns the global bounds of coin.
    /// \return Returns a sf::Floatrect of the sprite coin.
    sf::FloatRect getBounds();

    /// @brief
    /// Returns the position of the coin sprite.
    /// \return Returns a sf::Vector2f with the coordinates of the sprite coin.
    sf::Vector2f getPosition();

    /// @brief
    /// Used to draw coin object in the window.
    void draw();
};

#endif //PROJECT_COIN_H