#include "Spike.hpp"
#include <iostream>
#include <utility>
#include "Definitions.hpp"

Spike::Spike(GameDataReference gameData, Spike_facing facing, sf::Vector2f position):
    Obstacle(identifier::spike),
    gameData(std::move(gameData)),
    facing (facing),
    position (position)
{
    spawn();
}

sf::Vector2f Spike::getPosition(){
    return Triangle.getPosition();
}

void Spike::spawn(){
    Triangle.setPointCount(3);

    if(facing == left){
        Triangle.setPoint(0, sf::Vector2f{ 0, 0 } );
        Triangle.setPoint(1, sf::Vector2f{ -SPIKE_SIZE, SPIKE_SIZE/2.0f } );
        Triangle.setPoint(2, sf::Vector2f{ 0, SPIKE_SIZE } );
        Triangle.setPosition(position);
        Triangle.setFillColor(gameData->json.getObstacleColor());
    }
    else{
        Triangle.setPoint(0, sf::Vector2f{ 0, 0 } );
        Triangle.setPoint(1, sf::Vector2f{ SPIKE_SIZE, SPIKE_SIZE/2.0f } );
        Triangle.setPoint(2, sf::Vector2f{ 0, SPIKE_SIZE } );
        Triangle.setPosition(position);
        Triangle.setFillColor(gameData->json.getObstacleColor());
    }
}

void Spike::move(sf::Vector2f moveBy){
    Triangle.move(moveBy);
}

void Spike::draw() const{
    gameData -> window.draw(Triangle);
}

sf::FloatRect Spike::getBounds(){
    return Triangle.getGlobalBounds();
}

Spike_facing Spike::getFace() {
    return facing;
}

sf::Vector2f Spike::get_point(const int &index) {
    return Triangle.getPoint(index);
}
