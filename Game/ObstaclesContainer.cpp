#include "ObstaclesContainer.hpp"
#include <cstdlib>
#include <utility>
#include <vector>
#include "Deathwall.hpp"

Obstacle_Container::Obstacle_Container(GameDataReference data):
    game_data (std::move(data))
{}

void Obstacle_Container::spawn_Obstacle_On_Wall(const sf::RectangleShape& wall){
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
            obstacles.push_back(new Spike(game_data, left, sf::Vector2f(
                    Coordinates_Left_Obstacle.x - SPIKE_SIZE / 2.0f,
                    Coordinates_Left_Obstacle.y + SPIKE_SIZE )));
        }
        else if (Wall_Left_Side_obstacles == 2){
            obstacles.push_back(new Deathwall(game_data, sf::Vector2f(
//                    Coordinates_Left_Obstacle.x - WALL_WIDTH / 8.0f,
                    Coordinates_Left_Obstacle.x - 1,
                    Coordinates_Left_Obstacle.y - WALL_OBSTACLE_HEIGHT_1)));
        }
    }

    for(auto & Coordinates_Right_Obstacle : Coordinates_Right_Obstacles) {
        if (Wall_right_Side_obstacles == 1) {
            obstacles.push_back(new Spike(game_data, right, sf::Vector2f(
                    Coordinates_Right_Obstacle.x + SPIKE_SIZE / 2.0f,
                    Coordinates_Right_Obstacle.y - SPIKE_SIZE )));
        }
        else if (Wall_right_Side_obstacles == 2){
            obstacles.push_back(new Deathwall(game_data, sf::Vector2f(
//                    Coordinates_Right_Obstacle.x - WALL_WIDTH / 8.0f * 3 ,
                    Coordinates_Right_Obstacle.x - WALL_WIDTH / 2 + 1 ,
                    Coordinates_Right_Obstacle.y - WALL_OBSTACLE_HEIGHT_1)));
        }
    }
}

void Obstacle_Container::move_Obstacle(sf::Vector2f move_by){
    std::for_each(obstacles.begin(),obstacles.end(), [&move_by ](Obstacle* &x ){
        x->move(move_by);
    });

    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](Obstacle* &x){
        return (x->getPosition().y >= SCREEN_HEIGHT);
    }), obstacles.end());
}

void Obstacle_Container::draw_Obstacle(){
    for(auto obstacle : obstacles){
        obstacle -> draw();
    }
}

std::vector<Obstacle *> Obstacle_Container::getObstacle() {
    return obstacles;
}

Obstacle_Container::~Obstacle_Container() {
    for (auto& object : obstacles) {
        delete object;
    }
}




