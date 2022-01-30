#include "Wall.hpp"
#include <cstdlib>
#include <ctime>
#include <utility>
#include <random>

Wall::Wall(GameDataReference data):
    game_data (std::move(data))
{
    left_boundary.setPosition(0.0, 0.0);
    left_boundary.setSize( {SCREEN_WIDTH/6.0f, SCREEN_HEIGHT} );
    left_boundary.setFillColor( game_data->json.Get_OuterWallColor() );

    right_boundary.setPosition(SCREEN_WIDTH/6.0f * 5.0f, 0.0);
    right_boundary.setSize( {(SCREEN_WIDTH/6.0f), SCREEN_HEIGHT} );
    right_boundary.setFillColor( game_data->json.Get_OuterWallColor() );
}

std::vector<wall_obstacles> &Wall::getWalls() {
    return walls;
}

std::vector<sf::RectangleShape> Wall::getAllRectangles() {
    std::vector<wall_obstacles> tmp = walls;
    tmp.push_back({left_boundary, false});
    tmp.push_back({right_boundary, false});

    std::vector<sf::RectangleShape> hitboxes;
    std::for_each(tmp.begin(), tmp.end(), [&hitboxes](const wall_obstacles& x){
        hitboxes.push_back(x.wall);
    });
    return hitboxes;
}

void Wall::generate_Wall(float x_position, float start_y_offset){
    wall_obstacles tmp;
    tmp.wall.setSize(sf::Vector2f(WALL_WIDTH, WALL_HEIGHT));
    tmp.wall.setPosition(x_position - tmp.wall.getSize().x / 2 ,start_y_offset - tmp.wall.getSize().y);
    tmp.wall.setFillColor(game_data->json.Get_WallColor());
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
        generate_Wall( ((SCREEN_WIDTH / 5.0f) * 2) - WALL_WIDTH/4 *3, start_y_offset);
        generate_Wall(((SCREEN_WIDTH / 5.0f) * 3) + WALL_WIDTH/4 *3, start_y_offset);
    }
    else if (random == 3){
        generate_Wall(((SCREEN_WIDTH / 5.0f) * 2) - WALL_WIDTH/4 *3, start_y_offset);
    }
    else{
        generate_Wall(((SCREEN_WIDTH / 5.0f) * 3) + WALL_WIDTH/4 *3, start_y_offset);
    }
}

void Wall::move_Wall(sf::Vector2f move_by){
    std::for_each(walls.begin(),walls.end(), [&move_by ](wall_obstacles &x ){
        x.wall.move(move_by);
    });

    walls.erase(std::remove_if(walls.begin(), walls.end(), [](wall_obstacles &x){
        return (x.wall.getPosition().y >= SCREEN_HEIGHT);
    }), walls.end());
}

void Wall::draw_Wall(){
    for(auto & wall : walls){
        game_data->window.draw(wall.wall);
    }
    game_data->window.draw(left_boundary);
    game_data->window.draw(right_boundary);
}

void Wall::setContainObstacleTrue(int index){
    walls[index].contains_obstacles = true;
}






