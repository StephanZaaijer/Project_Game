//
// Created by Franky on 20-1-2022.
//

#include "Deathwall.hpp"
#include <iostream>
#include "Definitions.hpp"

Deathwall::Deathwall(GameDataReference game_data, sf::Vector2f position):
        game_data(game_data),
        position (position)
{spawn();}

sf::Vector2f Deathwall::getPosition(){
    return deathwall.getPosition();
}

void Deathwall::spawn(){
    deathwall.setPosition(sf::Vector2f(position.x, position.y ));
    deathwall.setSize(sf::Vector2f(WALL_WIDTH/2, WALL_HEIGHT/3));
    deathwall.setFillColor(sf::Color::Black);
}

void Deathwall::move(sf::Vector2f move_by){
    deathwall.move(move_by);
}
void Deathwall::draw(){
    game_data -> window.draw(deathwall);
}