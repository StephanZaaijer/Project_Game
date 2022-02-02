#ifndef PROJECT_GAME_OBSTACLE_CONTAINER_H
#define PROJECT_GAME_OBSTACLE_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"
#include "Spike.hpp"
#include "Deathwall.hpp"

class ObstacleContainer {
private:
    GameDataReference gameData;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
public:
    ObstacleContainer(GameDataReference gameData);
    const std::vector<std::unique_ptr<Obstacle>> & getObstacle();
    void spawn_Obstacle_On_Wall(const sf::RectangleShape& wall);
    void moveObstacle(sf::Vector2f moveBy);
    void draw_Obstacle();

};

#endif //PROJECT_GAME_OBSTACLE_CONTAINER_H
