//
// Created by Franky on 19-1-2022.
//

#include "Wall.hpp"
#include "iostream"
#include <stdlib.h>
#include <time.h>

Wall::Wall(GameDataReference data):
    game_data (data)
{}

std::vector<sf::RectangleShape> Wall::getWalls(){
    return walls;
}

std::vector<bool> Wall::getContainsObstacles(){
    return contains_obstacles;
}

void Wall::generate_Wall(float x_position, float start_y_offset){
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(WALL_WIDTH, WALL_HEIGHT));
    rectangle.setPosition(sf::Vector2f(
            x_position - rectangle.getSize().x / 2 ,
            start_y_offset - rectangle.getSize().y));
    rectangle.setFillColor(sf::Color::Green
    );
    walls.push_back(rectangle);
    contains_obstacles.push_back(false);
}

void Wall::spawn_Wall(float start_y_offset){
    srand (time(NULL));
    int random = rand() % 4 + 1;\

    if (random == 1){
        generate_Wall(SCREEN_WIDTH / 2, start_y_offset);
    }
    else if (random == 2){
        generate_Wall(SCREEN_WIDTH / 3, start_y_offset);
        generate_Wall((SCREEN_WIDTH / 3) * 2, start_y_offset);
    }
    else if (random == 3){
        generate_Wall(SCREEN_WIDTH / 3, start_y_offset);
    }
    else{
        generate_Wall((SCREEN_WIDTH / 3) * 2, start_y_offset);
    }
}

void Wall::move_Wall(sf::Vector2f move_by){
    for(unsigned int i = 0; i < walls.size(); i++){
        walls[i].move(move_by);
        if (walls[i].getPosition().y >= SCREEN_HEIGHT){
            walls.erase(walls.begin() + i);
            contains_obstacles.erase(contains_obstacles.begin() + i);
        }
    }
}

void Wall::draw_Wall(){
    for(unsigned int i = 0; i < walls.size(); i++){
        game_data->window.draw(walls[i]);
    }
}

void Wall::setContainObstacleTrue(int index){
    contains_obstacles[index] = true;
}