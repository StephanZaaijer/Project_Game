#include "Spike.hpp"
#include <iostream>
#include <utility>
#include "Definitions.hpp"

Spike::Spike(GameDataReference game_data, Spike_facing facing, sf::Vector2f position):
    game_data(std::move(game_data)),
    facing (facing),
    position (position)
{spawn();}

sf::Vector2f Spike::getPosition(){
    return Triangle.getPosition();
}

void Spike::spawn(){
    if(facing == left){
        Triangle.setPosition(sf::Vector2f(position.x - Triangle.getRadius(),position.y ));
        Triangle.setFillColor(game_data->json.Get_ObstacleColor());
        Triangle.setRotation(270);
    }
    else{
        Triangle.setPosition(sf::Vector2f(position.x + Triangle.getRadius(),position.y ));
        Triangle.setFillColor(game_data->json.Get_ObstacleColor());
        Triangle.setRotation(90);
    }
}

void Spike::move(sf::Vector2f move_by){
    Triangle.move(move_by);
}
void Spike::draw() const{
    game_data -> window.draw(Triangle);
}

sf::FloatRect Spike::getBounds(){
    return Triangle.getGlobalBounds();
}