#include "Coin.hpp"

Coin::Coin(GameDataReference gameData):
    gameData(gameData)
{
    coin.setTexture(gameData -> assets.GetTexture("Coin"));
    coin.setScale(COIN_SCALE, COIN_SCALE);
}

void Coin::move(sf::Vector2f moveBy){
    coin.move(moveBy);
}

void Coin::setPosition(sf::Vector2f position){
    coin.setPosition(position);
}

sf::Sprite Coin::getCoin(){
    return coin;
}

sf::FloatRect Coin::getBounds(){
    return coin.getGlobalBounds();
}

sf::Vector2f Coin::getPosition(){
    return coin.getPosition();
}

void Coin::draw(){
    gameData -> window.draw(coin);
}
