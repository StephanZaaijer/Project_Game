//
// Created by Franky on 19-1-2022.
//

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>

#ifndef PROJECT_GAME_WALL_H
#define PROJECT_GAME_WALL_H

class Wall {
private:
    GameDataReference game_data;
    std::vector<sf::RectangleShape> walls;
    std::vector<bool> contains_obstacles;
public:
    Wall(GameDataReference data);
    std::vector<sf::RectangleShape> getWalls();
    std::vector<bool> getContainsObstacles();
    void generate_Wall(float x_position, float start_y_offset);
    void spawn_Wall(float start_y_offset = 0);
    void move_Wall(sf::Vector2f move_by);
    void draw_Wall();
    void setContainObstacleTrue(int index);

};


#endif //PROJECT_GAME_WALL_H
