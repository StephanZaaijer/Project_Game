#ifndef PROJECT_COIN_H
#define PROJECT_COIN_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"

class Coin{
private:
    GameDataReference gameData;
    sf::Sprite coin;

public:
    Coin(GameDataReference gameData);
    void move(sf::Vector2f moveBy);
    void setPosition(sf::Vector2f position);
    sf::Sprite getCoin();
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    void draw();
};

#endif //PROJECT_COIN_H