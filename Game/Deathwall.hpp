#ifndef PROJECT_GAME_DEATHWALL_H
#define PROJECT_GAME_DEATHWALL_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include <utility>
#include "Obstacle.hpp"

class Deathwall : public Obstacle {
private:
    GameDataReference game_data;
    sf::RectangleShape deathwall;
public:
    Deathwall(GameDataReference game_data, sf::Vector2f position);
    sf::Vector2f getPosition() override;
//    void spawn() override;
    void move(sf::Vector2f move_by) override;
    void draw() const override;
    sf::FloatRect getBounds() override;
};


#endif //PROJECT_GAME_DEATHWALL_H
