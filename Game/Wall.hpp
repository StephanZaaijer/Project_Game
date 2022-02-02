#ifndef PROJECT_GAME_WALL_H
#define PROJECT_GAME_WALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "ObstaclesContainer.hpp"

struct WallObstacles{
    sf::RectangleShape wall;
    bool containsObstacles = false;
};

class Wall {
private:
    GameDataReference gameData;
    std::vector<WallObstacles> walls;

    sf::RectangleShape leftBoundary;
    sf::RectangleShape rightBoundary;

public:
    Wall(GameDataReference gameData);
    std::vector<WallObstacles> & getWalls();
    std::vector<sf::RectangleShape> getAllRectangles();
    void generateWall(float xPosition, float startYoffset);
    void spawnWall(float startYoffset = 0);
    void moveWall(sf::Vector2f moveBy);
    void drawWall();
    void setContainObstacleTrue(int index);
};


#endif //PROJECT_GAME_WALL_H
