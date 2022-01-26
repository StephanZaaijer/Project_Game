#ifndef PROJECT_GAME_SPIKE_H
#define PROJECT_GAME_SPIKE_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>
#include "Obstacle.hpp"
#include "Game.hpp"

class Spike : public Obstacle {
private:
    GameDataReference game_data;
    sf::CircleShape Triangle = sf::CircleShape(SPIKE_SIZE, 3);
    Spike_facing facing;
    sf::Vector2f position;
public:
    Spike(GameDataReference game_data, Spike_facing facing, sf::Vector2f position);
    sf::Vector2f getPosition() override;
    void spawn() override;
    void move(sf::Vector2f move_by) override;
    void draw() override;
    sf::FloatRect getBounds() override;

};


#endif //PROJECT_GAME_SPIKE_H
