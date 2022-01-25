//
// Created by Franky on 20-1-2022.
//

#ifndef PROJECT_GAME_DEATHWALL_H
#define PROJECT_GAME_DEATHWALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"

class Deathwall : public Obstacle {
private:
    GameDataReference game_data;
    sf::RectangleShape deathwall;
    sf::Vector2f position;
public:
    Deathwall(GameDataReference game_data, sf::Vector2f position);
    sf::Vector2f getPosition() override;
    void spawn() override;
    void move(sf::Vector2f move_by) override;
    void draw() override;
};


#endif //PROJECT_GAME_DEATHWALL_H
