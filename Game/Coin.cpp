#include "Coin.hpp"

Coin::Coin(GameDataReference game_data):
    game_data (game_data)
{
    _coin.setTexture(game_data -> assets.GetTexture("_coin"));
    _coin.setScale(COIN_SCALE, COIN_SCALE);
}

void Coin::move(sf::Vector2f move_by){
    _coin.move(move_by);
}

void Coin::set_position(sf::Vector2f position){
    _coin.setPosition(position);
}

sf::Sprite Coin::get_coin(){
    return _coin;
}

sf::FloatRect Coin::getBounds(){
    return _coin.getGlobalBounds();
}

void Coin::draw(){
    game_data -> window.draw(_coin);
}
