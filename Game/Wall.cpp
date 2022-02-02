#include "Wall.hpp"
#include <cstdlib>
#include <ctime>
#include <utility>
#include <random>

Wall::Wall(GameDataReference gameData):
    gameData (std::move(gameData))
{
    leftBoundary.setPosition(0.0, 0.0);
    leftBoundary.setSize( {SCREEN_WIDTH/6.0f, SCREEN_HEIGHT} );
    leftBoundary.setFillColor( sf::Color::Black );

    rightBoundary.setPosition(SCREEN_WIDTH/6.0f * 5.0f, 0.0);
    rightBoundary.setSize( {(SCREEN_WIDTH/6.0f), SCREEN_HEIGHT} );
    rightBoundary.setFillColor( sf::Color::Black );
}

std::vector<WallObstacles> &Wall::getWalls() {
    return walls;
}

std::vector<sf::RectangleShape> Wall::getAllRectangles() {
    std::vector<WallObstacles> tmp = walls;
    tmp.push_back({leftBoundary, false});
    tmp.push_back({rightBoundary, false});

    std::vector<sf::RectangleShape> hitboxes;
    std::for_each(tmp.begin(), tmp.end(), [&hitboxes](const WallObstacles& x){
        hitboxes.push_back(x.wall);
    });
    return hitboxes;
}

void Wall::generateWall(float xPosition, float startYoffset){
    WallObstacles tmp;
    tmp.wall.setSize(sf::Vector2f(WALL_WIDTH, WALL_HEIGHT));
    tmp.wall.setPosition(xPosition - tmp.wall.getSize().x / 2 ,startYoffset - tmp.wall.getSize().y);
    tmp.wall.setFillColor(gameData->json.getWallColor());
    tmp.containsObstacles = false;
    walls.push_back(tmp);
}

void Wall::spawnWall(float startYoffset){
    srand (time(nullptr));
    int random = rand() % 4 + 1;

    if (random == 1){
        generateWall(SCREEN_WIDTH / 2.0f, startYoffset);
    }
    else if (random == 2){
        generateWall( ((SCREEN_WIDTH / 5.0f) * 2) - WALL_WIDTH/4.0f *3.0f, startYoffset);
        generateWall(((SCREEN_WIDTH / 5.0f) * 3) + WALL_WIDTH/4.0f *3.0f, startYoffset);
    }
    else if (random == 3){
        generateWall(((SCREEN_WIDTH / 5.0f) * 2) - WALL_WIDTH/4.0f *3.0f, startYoffset);
    }
    else{
        generateWall(((SCREEN_WIDTH / 5.0f) * 3) + WALL_WIDTH/4.0f *3.0f, startYoffset);
    }
}

void Wall::moveWall(sf::Vector2f moveBy){
    std::for_each(walls.begin(),walls.end(), [&moveBy ](WallObstacles &x ){
        x.wall.move(moveBy);
    });

    walls.erase(std::remove_if(walls.begin(), walls.end(), [](WallObstacles &x){
        return (x.wall.getPosition().y >= SCREEN_HEIGHT);
    }), walls.end());
}

void Wall::drawWall(){
    for(auto & wall : walls){
        gameData->window.draw(wall.wall);
    }
    gameData->window.draw(leftBoundary);
    gameData->window.draw(rightBoundary);
}

void Wall::setContainObstacleTrue(int index){
    walls[index].containsObstacles = true;
}






