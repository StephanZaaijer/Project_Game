#ifndef PROJECT_COIN_H
#define PROJECT_COIN_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"

/// @file Coin.hpp
/// @brief
/// Project_Game: Defines a coin object

class Coin{
private:
    GameDataReference game_data;
    sf::Sprite _coin;

public:
    /// @brief
    /// Used to construct coin object.
    /// @details
    /// Used to construct coin object and initializes the object with a texture and scale
    /// \param game_data .
    /// \return The sf::Font that`s stored with that particular key.
    Coin(GameDataReference game_data);
    void move(sf::Vector2f move_by);
    void set_position(sf::Vector2f position);
    sf::Sprite get_coin();
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    void draw();
};

#endif //PROJECT_COIN_H