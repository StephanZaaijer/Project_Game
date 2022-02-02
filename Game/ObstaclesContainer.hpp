#ifndef PROJECT_GAME_OBSTACLE_CONTAINER_H
#define PROJECT_GAME_OBSTACLE_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"
#include "Spike.hpp"
#include "Deathwall.hpp"

/// @file CoinContainer.hpp
/// @brief
/// Project_Game: Defines an Obstacle container

/// @brief
/// Container class used to store Obstacle pointers.
class ObstacleContainer {
private:
    GameDataReference gameData;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
public:
    /// @brief
    /// Used to construct container object.
    /// \param game_data is a shared pointer to the GameDataReference where information of the game is stored
    ObstacleContainer(GameDataReference gameData);

    /// @brief
    /// Returns vector containing pointers to Obstacle objects.
    /// \return Returns a std::vector<std::unique_ptr<Obstacle>> obstacles of the container.
    const std::vector<std::unique_ptr<Obstacle>> & getObstacle();

    /// @brief
    /// Used to spawn obstacles on a wall.
    /// @details
    /// Randomizes and spawns obstacles on the wall given as parameter.
    /// Uses time as seed for randomization of spawn location and obstacles.
    /// \param wall is a reference to a sf::RectangleShape within the class Wall
    void spawnObstacleOnWall(const sf::RectangleShape& wall);

    /// @brief
    /// Used to move every obstacle object in the container.
    /// @details
    /// Used to move every obstacle object in the container by an offset given in the parameter.
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate.
    void moveObstacle(sf::Vector2f moveBy);

    /// @brief
    /// Used to draw every obstacle object in the container.
    void drawObstacle();

};

#endif //PROJECT_GAME_OBSTACLE_CONTAINER_H
