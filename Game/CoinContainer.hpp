#ifndef PROJECT_COIN_CONTAINER_H
#define PROJECT_COIN_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"
#include <vector>
#include "Coin.hpp"

class CoinContainer{
private:
    GameDataReference gameData;
    std::vector<std::unique_ptr<Coin>> coins;
public:
    CoinContainer(GameDataReference gameData);
    std::vector<std::unique_ptr<Coin>> & getcoins();
    void spawn();
    void move(sf::Vector2f moveBy);
    void draw();
};

#endif //PROJECT_COIN_CONTAINER_H