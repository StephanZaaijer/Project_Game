//
// Created by Franky on 19-1-2022.
//

#include <SFML/Graphics.hpp>
#include "Game.hpp"

#ifndef PROJECT_GAME_WALL_H
#define PROJECT_GAME_WALL_H

class Wall {
private:
    GameDataReference game_data;
    std::vector<sf::RectangleShape> walls;
public:
    Wall(GameDataReference data);
    void draw_Wall();
};


#endif //PROJECT_GAME_WALL_H
