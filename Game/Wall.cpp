//
// Created by Franky on 19-1-2022.
//

#include "Wall.h"

Wall::Wall(GameDataReference data):
    game_data (data)
{}

void Wall::draw_Wall(){
    for(unsigned int i = 0; i < walls.size(); i++){
        game_data->window.draw(walls[i]);
    }
}