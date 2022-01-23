//
// Created by Franky on 20-1-2022.
//

#include "Spike.hpp"
#include <iostream>
#include "Definitions.hpp"

Spike::Spike(GameDataReference game_data, Spike_facing facing, sf::Vector2f position):
    game_data(game_data),
    facing (facing),
    position (position)
{spawn();}

sf::Vector2f Spike::getPosition(){
    return position;
}

void Spike::spawn(){
    if(facing == left){
        Triangle.setPosition(sf::Vector2f(position.x - Triangle.getRadius(),position.y ));
        Triangle.setFillColor(sf::Color::Black);
        Triangle.setRotation(270);
    }
    else{
        Triangle.setPosition(sf::Vector2f(position.x + Triangle.getRadius(),position.y ));
        Triangle.setFillColor(sf::Color::Black);
        Triangle.setRotation(90);
    }
}

void Spike::move(sf::Vector2f move_by){
    Triangle.move(move_by);
}
void Spike::draw(){
    game_data -> window.draw(Triangle);
}