#ifndef PROJECT_COIN_CONTAINER_H
#define PROJECT_COIN_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"
#include <vector>
#include "Coin.hpp"

class Coin_Container{
private:
    GameDataReference game_data;
    std::vector<std::unique_ptr<Coin>> coins;
public:
    Coin_Container(GameDataReference game_data);
    std::vector<std::unique_ptr<Coin>> & getCoins();
    void spawn();
    void move(sf::Vector2f move_by);
    void draw();
};

#endif //PROJECT_COIN_CONTAINER_H