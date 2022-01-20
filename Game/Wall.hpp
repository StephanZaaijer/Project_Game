#ifndef PROJECT_GAME_WALL_H
#define PROJECT_GAME_WALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>

class Wall {
private:
    GameDataReference game_data;
    std::vector<sf::RectangleShape> walls;
public:
    Wall(GameDataReference data);
    void spawn_Wall();
    void move_Wall(sf::Vector2f new_position);

    void draw_Wall();
};


#endif //PROJECT_GAME_WALL_H
