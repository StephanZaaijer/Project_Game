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
    GameDataReference gameData;
    sf::ConvexShape Triangle;

    Spike_facing facing;
    sf::Vector2f position;

public:
    Spike(GameDataReference gameData, Spike_facing facing, sf::Vector2f position);
    sf::Vector2f getPosition() override;
    void spawn() override;
    void move(sf::Vector2f move_by) override;
    void draw() const override;
    sf::FloatRect getBounds() override;
    Spike_facing getFace() override;
    sf::Vector2f get_point(const int & index) override;


};


#endif //PROJECT_GAME_SPIKE_H
