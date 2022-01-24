#include "Wall.hpp"
#include "iostream"
#include <cstdlib>
#include <ctime>
#include <utility>
#include <random>

Wall::Wall(GameDataReference data):
    game_data (std::move(data))
{}

std::vector<wall_obstacles> &Wall::getWalls() {
    return walls;
}

void Wall::generate_Wall(float x_position, float start_y_offset){
    wall_obstacles tmp;
    tmp.wall.setSize(sf::Vector2f(WALL_WIDTH, WALL_HEIGHT));
    tmp.wall.setPosition(x_position - tmp.wall.getSize().x / 2 ,start_y_offset - tmp.wall.getSize().y);
    tmp.wall.setFillColor(sf::Color::Green);
    tmp.contains_obstacles = false;
    walls.push_back(tmp);
}

void Wall::spawn_Wall(float start_y_offset){
    srand (time(nullptr));
    int random = rand() % 4 + 1;

    if (random == 1){
        generate_Wall(SCREEN_WIDTH / 2.0f, start_y_offset);
    }
    else if (random == 2){
        generate_Wall(SCREEN_WIDTH / 3.0f, start_y_offset);
        generate_Wall((SCREEN_WIDTH / 3.0f) * 2, start_y_offset);
    }
    else if (random == 3){
        generate_Wall(SCREEN_WIDTH / 3.0f, start_y_offset);
    }
    else{
        generate_Wall((SCREEN_WIDTH / 3.0f) * 2, start_y_offset);
    }
}

void Wall::move_Wall(sf::Vector2f move_by){
    for(unsigned int i = 0; i < walls.size(); i++){
        walls[i].wall.move(move_by);
        if (walls[i].wall.getPosition().y >= SCREEN_HEIGHT){
            walls.erase(walls.begin() + i);
        }
    }
}

void Wall::draw_Wall(){
    for(auto & wall : walls){
        game_data->window.draw(wall.wall);
    }
}

void Wall::setContainObstacleTrue(int index){
    walls[index].contains_obstacles = true;
}






