#ifndef PROJECT_COIN_CONTAINER_H
#define PROJECT_COIN_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"
#include <vector>
#include "Coin.hpp"

/// @file CoinContainer.hpp
/// @brief
/// Project_Game: Defines a Coin container

/// @brief
/// Container class used to store Coin pointers.
class CoinContainer{
private:
    GameDataReference gameData;
    std::vector<std::unique_ptr<Coin>> coins;
public:
    /// @brief
    /// Used to construct container object.
    /// \param game_data is a shared pointer to the GameDataReference where information of the game is stored
    CoinContainer(GameDataReference gameData);

    /// @brief
    /// Returns vector containing pointers to Coin objects.
    /// \return Returns a std::vector<std::unique_ptr<Coin>> coins of the container.
    std::vector<std::unique_ptr<Coin>> & getCoins();

    /// @brief
    /// Used to spawn coin.
    /// @details
    /// Used to spawn coins at randomized positions.
    void spawn();

    /// @brief
    /// Used to move every coin object in the container.
    /// @details
    /// Used to move every coin object in the container by an offset given in the parameter.
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate.
    void move(sf::Vector2f moveBy);

    /// @brief
    /// Used to draw every coin object in the container.
    void draw();
};

#endif //PROJECT_COIN_CONTAINER_H