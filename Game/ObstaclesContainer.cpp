//
// Created by Franky on 20-1-2022.
//

#include "ObstaclesContainer.hpp"
#include <iostream>

Obstacle_Container::Obstacle_Container(GameDataReference data):
    game_data(data)
{}
void Obstacle_Container::spawn_Obstacle(Obstacle_objects object){
    if(object == Spike_Object){
        obstacles.push_back(new Spike(game_data, left));
    }
}

void Obstacle_Container::move_Obstacle(sf::Vector2f move_by){
    for (auto obstacle : obstacles){
        obstacle ->move(move_by);
    }
}

void Obstacle_Container::draw_Obstacle(){
    for(auto obstacle : obstacles){
        std::cout << "enter draw loop" << std::endl;
        obstacle -> draw();
    }
}