#ifndef PROJECT_GAME_OBSTACLE_H
#define PROJECT_GAME_OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Definitions.hpp"
#include <vector>

class Obstacle {
private:
    identifier I;

public:
    Obstacle(const identifier & I): I(I) {}

    virtual sf::Vector2f getPosition() = 0;
    virtual void spawn() = 0;
    virtual void move(sf::Vector2f moveBy) = 0;
    virtual void draw() const = 0;
    virtual sf::FloatRect getBounds() = 0;

    virtual sf::Vector2f get_point(const int & index){
        return {};
    }
    virtual Spike_facing getFace(){
        return neither;
    }
    identifier getID(){
        return I;
    }
};



#endif //PROJECT_GAME_OBSTACLE_H
