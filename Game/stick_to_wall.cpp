#include "stick_to_wall.hpp"

stick_to_wall::stick_to_wall(GameDataReference data): game_data(data){
    _characterSprite.setTexture(game_data->assets.GetTexture("character 1"));
}
void stick_to_wall::Draw() {
    game_data->window.draw(_characterSprite);
    game_data->window.display()
}

