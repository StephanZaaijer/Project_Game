#ifndef PROJECT_GAME_WALL_H
#define PROJECT_GAME_WALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "ObstaclesContainer.hpp"

/// @file Wall.hpp
/// @brief
/// Project_Game: This wall is used to play the game. It creates the walls shown in the game.

/// @brief
/// Wall class that creates all walls rendered on the screen

class Wall {
private:
    /// @brief
    /// wallObstacles struct that contains data of walls it contains the sf::RectangleShape and a boolean if it has Obstacles
    struct WallObstacles{
        sf::RectangleShape wall;
        bool containsObstacles = false;
    };
    GameDataReference gameData;
    std::vector<WallObstacles> walls;

    sf::RectangleShape leftBoundary;
    sf::RectangleShape rightBoundary;

public:
    /// @brief
    /// Used to construct container object.
    /// \param gameData is a shared pointer to the GameDataReference where information of the game is stored
    Wall(GameDataReference gameData);

    /// @brief
    /// Returns vector containing WallObstacles structs.
    /// \return Returns the private member walls of the type std::vector<WallObstacles>.
    std::vector<WallObstacles> & getWalls();

    /// @brief
    /// Returns vector containing all the wall of type sf::RectangleShape of WallObstacles.
    /// \return Returns a std::vector<sf::RectangleShape> walls.
    std::vector<sf::RectangleShape> getAllRectangles();

    /// @brief
    /// Used to generate a wall
    /// @details
    /// This function generates a wall and adds its to a private member vector
    /// \param xPosition The x position on the screen to draw the wall
    /// \param startYoffset The startYoffset is used to draw the walls just above the screen
    void generateWall(float xPosition, float startYoffset);

    /// @brief
    /// Used to spawn a wall.
    /// @details
    /// Randomizes wall spawn locations.
    /// Uses time as seed for randomization of spawn location.
    /// \param startYoffset is the value by which to offset the spawn of the wall
    void spawnWall(float startYoffset = 0);

    /// @brief
    /// Used to spawn the first walls.
    /// @details
    /// Spawns the first walls
    /// \param startYoffset is the value by which to offset the spawn of the wall
    void spawnFirstWall(float startYoffset = 0);

    /// @brief
    /// Used to move every wall object in the container.
    /// @details
    /// Used to move every wall object in the container by an offset given in the parameter.
    /// \param moveBy is a sf::Vector2f which contains a X and Y coordinate.
    void moveWall(sf::Vector2f moveBy);

    /// @brief
    /// Used to draw every wall object in the container.
    void drawWall();

    /// @brief
    /// Used set the boolean of a specific index.
    /// \param index is an integer which is used to determine where the value should be changed.
    void setContainObstacleTrue(int index);
};


#endif //PROJECT_GAME_WALL_H
