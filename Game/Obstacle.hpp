//
// Created by Franky on 20-1-2022.
//

#ifndef PROJECT_GAME_OBSTACLE_H
#define PROJECT_GAME_OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>

class Obstacle {
public:
    virtual sf::Vector2f getPosition() = 0;
    virtual void spawn() = 0;
    virtual void move(sf::Vector2f move_by) = 0;
    virtual void draw() = 0;
};


#endif //PROJECT_GAME_OBSTACLE_H