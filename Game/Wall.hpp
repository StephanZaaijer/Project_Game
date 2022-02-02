#ifndef PROJECT_GAME_WALL_H
#define PROJECT_GAME_WALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "ObstaclesContainer.hpp"

struct wall_obstacles{
    sf::RectangleShape wall;
    bool contains_obstacles = false;
};

class Wall {
private:
    GameDataReference gameData;
    std::vector<wall_obstacles> walls;

    sf::RectangleShape left_boundary;
    sf::RectangleShape right_boundary;

public:
    Wall(GameDataReference gameData);
    std::vector<wall_obstacles> & getWalls();
    std::vector<sf::RectangleShape> getAllRectangles();
    void generate_Wall(float x_position, float start_y_offset);
    void spawn_Wall(float start_y_offset = 0);
    void move_Wall(sf::Vector2f moveBy);
    void draw_Wall();
    void setContainObstacleTrue(int index);
};


#endif //PROJECT_GAME_WALL_H
