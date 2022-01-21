//
// Created by Franky on 20-1-2022.
//

#include "Spike.hpp"
#include <iostream>

Spike::Spike(GameDataReference game_data, Spike_facing facing):
    game_data(game_data),
    facing (facing)
{spawn();}


void Spike::spawn(){
    if(facing == left){
        std::cout << "init position";
        Triangle.setPosition(sf::Vector2f(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2));
        Triangle.setFillColor(sf::Color::Black);
    }
    else{
        Triangle.setPosition(sf::Vector2f(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2));
        Triangle.setFillColor(sf::Color::Black);
    }
}

void Spike::move(sf::Vector2f move_by){
    Triangle.move(move_by);
}
void Spike::draw(){
    std::cout << "draw triangle" << std::endl;
    std::cout << Triangle.getRadius() << std::endl;
    std::cout << Triangle.getPointCount () << std::endl;
    std::cout << Triangle.getPosition().x << std::endl;
    std::cout << Triangle.getPosition().y << std::endl;
    game_data -> window.draw(Triangle);
    std::cout << "draw succes" << std::endl;
}