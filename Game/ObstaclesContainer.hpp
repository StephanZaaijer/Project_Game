#ifndef PROJECT_GAME_OBSTACLE_CONTAINER_H
#define PROJECT_GAME_OBSTACLE_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"
#include "Spike.hpp"
#include "Deathwall.hpp"

class Obstacle_Container {
private:
    struct Coordinates_Obstacles;
    GameDataReference game_data;
    std::vector<Obstacle*> obstacles;
public:
    Obstacle_Container(GameDataReference data);
    ~Obstacle_Container();
    std::vector<Obstacle*> getObstacle();
    void spawn_Obstacle_On_Wall(const sf::RectangleShape& wall);
    void move_Obstacle(sf::Vector2f move_by);
    void draw_Obstacle();

};

#endif //PROJECT_GAME_OBSTACLE_CONTAINER_H
