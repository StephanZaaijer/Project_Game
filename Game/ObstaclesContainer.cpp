#include "ObstaclesContainer.hpp"
#include <cstdlib>
#include <utility>
#include <vector>
#include "Deathwall.hpp"
#include <ctime>

ObstacleContainer::ObstacleContainer(GameDataReference gameData):
    gameData (std::move(gameData))
{}

void ObstacleContainer::spawnObstacleOnWall(const sf::RectangleShape& wall){
    srand (time(nullptr));
    int wallLeftSide = rand() % 4 + 1;
    int wallRightSide = rand() % 4 + 1;
    int wallLeftSideObstacles = rand() % 2 + 1;
    int wallRightSideObstacles = rand() % 2 + 1;
    std::vector<sf::Vector2f> coordinatesLeftObstacles;
    std::vector<sf::Vector2f> coordinatesRightObstacles;

    if(wallLeftSide == 1){
        coordinatesLeftObstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
    }
    else if(wallLeftSide == 2){
        coordinatesLeftObstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_2);
    }
    else if(wallLeftSide == 3){
        coordinatesLeftObstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }
    else{
        coordinatesLeftObstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
        coordinatesLeftObstacles.emplace_back(
                wall.getPosition().x,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }

    if(wallRightSide == 1){
        coordinatesRightObstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
    }
    else if(wallRightSide == 2){
        coordinatesRightObstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_2);
    }
    else if(wallRightSide == 3){
        coordinatesRightObstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }
    else{
        coordinatesRightObstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_1);
        coordinatesRightObstacles.emplace_back(
                wall.getPosition().x + WALL_WIDTH,
                wall.getPosition().y + WALL_OBSTACLE_HEIGHT_3);
    }

    for(auto & Coordinates_Left_Obstacle : coordinatesLeftObstacles) {
        if (wallLeftSideObstacles == 1) {
            obstacles.push_back(std::unique_ptr<Obstacle>(new Spike(gameData, left, sf::Vector2f(
                    Coordinates_Left_Obstacle.x,
                    Coordinates_Left_Obstacle.y - SPIKE_SIZE/2.0f ))));
        }
        else if (wallLeftSideObstacles == 2){
            obstacles.push_back(std::unique_ptr<Obstacle>(new Deathwall(gameData, sf::Vector2f(
                    Coordinates_Left_Obstacle.x - 1,
                    Coordinates_Left_Obstacle.y - WALL_OBSTACLE_HEIGHT_1))));
        }
    }

    for(auto & Coordinates_Right_Obstacle : coordinatesRightObstacles) {
        if (wallRightSideObstacles == 1) {
            obstacles.push_back(std::unique_ptr<Obstacle>(new Spike(gameData, right, sf::Vector2f(
                    Coordinates_Right_Obstacle.x,
                    Coordinates_Right_Obstacle.y - SPIKE_SIZE/2.0f))));
        }
        else if (wallRightSideObstacles == 2){
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

void ObstacleContainer::drawObstacle(){
    for(const auto & obstacle : obstacles){
        obstacle -> draw();
    }
}

const std::vector<std::unique_ptr<Obstacle>> & ObstacleContainer::getObstacle() {
    return obstacles;
}





