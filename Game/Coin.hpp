#ifndef PROJECT_COIN_H
#define PROJECT_COIN_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"

class Coin{
private:
    GameDataReference game_data;
    sf::Sprite _coin;

public:
    Coin(GameDataReference game_data);
    void move(sf::Vector2f move_by);
    void set_position(sf::Vector2f position);
    sf::Sprite get_coin();
    sf::FloatRect getBounds();
    void draw();
};

#endif //PROJECT_COIN_H