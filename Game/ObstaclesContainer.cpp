#include "ObstaclesContainer.hpp"
#include <cstdlib>
#include <utility>
#include <vector>
#include "Deathwall.hpp"
#include <time.h>

#include <iostream>

ObstacleContainer::ObstacleContainer(GameDataReference gameData):
    gameData (std::move(gameData))
{}

void ObstacleContainer::spawn_Obstacle_On_Wall(const sf::RectangleShape& wall){
    srand (time(NULL));
    int Wall_Left_Side = rand() % 4 + 1;
    int Wall_Right_Side = rand() % 4 + 1;
    int Wall_Left_Side_obstacles = rand() % 2 + 1;
    int Wall_right_Side_obstacles = rand() % 2 + 1;
    std::vector<sf::Vector2f> Coordinates_Left_Obstacles;
    std::vector<sf::Vector2f> Coordinates_Right_Obstacles;

    if(Wall_Left_Side == 1){
        Coordinates_Left_Obstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);

    }
    else if(Wall_Left_Side == 2){
        Coordinates_Left_Obstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_2);
    }
    else if(Wall_Left_Side == 3){
        Coordinates_Left_Obstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }
    else{
        Coordinates_Left_Obstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
        Coordinates_Left_Obstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }

    if(Wall_Right_Side == 1){
        Coordinates_Right_Obstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
    }
    else if(Wall_Right_Side == 2){
        Coordinates_Right_Obstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_2);
    }
    else if(Wall_Right_Side == 3){
        Coordinates_Right_Obstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }
    else{
        Coordinates_Right_Obstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
        Coordinates_Right_Obstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }

    for(auto & Coordinates_Left_Obstacle : Coordinates_Left_Obstacles) {
        if (Wall_Left_Side_obstacles == 1) {
            obstacles.push_back(std::unique_ptr<Obstacle>(new Spike(gameData, left, sf::Vector2f(
                    Coordinates_Left_Obstacle.x,
                    Coordinates_Left_Obstacle.y - SPIKE_SIZE/2.0f ))));
        }
        else if (Wall_Left_Side_obstacles == 2){
            obstacles.push_back(std::unique_ptr<Obstacle>(new Deathwall(gameData, sf::Vector2f(
                    Coordinates_Left_Obstacle.x - 1,
                    Coordinates_Left_Obstacle.y - WALL_OBSTACLE_HEIGHT_1))));
        }
    }

    for(auto & Coordinates_Right_Obstacle : Coordinates_Right_Obstacles) {
        if (Wall_right_Side_obstacles == 1) {
            obstacles.push_back(std::unique_ptr<Obstacle>(new Spike(gameData, right, sf::Vector2f(
                    Coordinates_Right_Obstacle.x,
                    Coordinates_Right_Obstacle.y - SPIKE_SIZE/2.0f))));
        }
        else if (Wall_right_Side_obstacles == 2){
            obstacles.push_back(std::unique_ptr<Obstacle>(new Deathwall(gameData, sf::Vector2f(
                    Coordinates_Right_Obstacle.x - WALL_WIDTH / 2.0f ,
                    Coordinates_Right_Obstacle.y - WALL_OBSTACLE_HEIGHT_1))));
        }
    }
}

void ObstacleContainer::moveObstacle(sf::Vector2f moveBy){
    std::for_each(obstacles.begin(),obstacles.end(), [&moveBy](std::unique_ptr<Obstacle> &x ){
        x->move(moveBy);
    });

    obstacles.erase(std::remove_if( obstacles.begin(), obstacles.end(), [](std::unique_ptr<Obstacle> & x){
        return (x -> getPosition().y >= SCREEN_HEIGHT + x->getBounds().height);
    }), obstacles.end());

}

void ObstacleContainer::draw_Obstacle(){
    for(const auto & obstacle : obstacles){
        obstacle -> draw();
    }
}

const std::vector<std::unique_ptr<Obstacle>> & ObstacleContainer::getObstacle() {
    return obstacles;
}





