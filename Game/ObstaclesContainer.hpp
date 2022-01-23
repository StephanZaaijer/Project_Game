//
// Created by Franky on 19-1-2022.
//

#ifndef PROJECT_GAME_OBSTACLE_CONTAINER_H
#define PROJECT_GAME_OBSTACLE_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"
#include "Spike.hpp"

class Obstacle_Container {
private:
    GameDataReference game_data;
    std::vector<Obstacle*> obstacles;
public:
    Obstacle_Container(GameDataReference data);
//    void spawn_Obstacle(Obstacle_objects object);
    void spawn_Obstacle_On_Wall(sf::RectangleShape wall);
    void move_Obstacle(sf::Vector2f move_by);
    void draw_Obstacle();

};

#endif //PROJECT_GAME_OBSTACLE_CONTAINER_H
