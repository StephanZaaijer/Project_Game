#include "Spike.hpp"
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
    return triangle.getPosition();
}

void Spike::spawn(){
    triangle.setPointCount(3);

    if(facing == left){
        triangle.setPoint(0, sf::Vector2f{ 0, 0 } );
        triangle.setPoint(1, sf::Vector2f{ -SPIKE_SIZE, SPIKE_SIZE/2.0f } );
        triangle.setPoint(2, sf::Vector2f{ 0, SPIKE_SIZE } );
        triangle.setPosition(position);
        triangle.setFillColor(gameData->json.getObstacleColor());
    }
    else{
        triangle.setPoint(0, sf::Vector2f{ 0, 0 } );
        triangle.setPoint(1, sf::Vector2f{ SPIKE_SIZE, SPIKE_SIZE/2.0f } );
        triangle.setPoint(2, sf::Vector2f{ 0, SPIKE_SIZE } );
        triangle.setPosition(position);
        triangle.setFillColor(gameData->json.getObstacleColor());
    }
}

void Spike::move(sf::Vector2f moveBy){
    triangle.move(moveBy);
}

void Spike::draw() const{
    gameData -> window.draw(triangle);
}

sf::FloatRect Spike::getBounds(){
    return triangle.getGlobalBounds();
}

Spike_facing Spike::getFace() {
    return facing;
}

sf::Vector2f Spike::getPoint(const int &index) {
    return triangle.getPoint(index);
}
