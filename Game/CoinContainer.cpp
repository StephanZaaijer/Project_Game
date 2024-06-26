#include "CoinContainer.hpp"

CoinContainer::CoinContainer(GameDataReference gameData):
    gameData (std::move(gameData))
{}

std::vector<std::unique_ptr<Coin>> & CoinContainer::getCoins(){
    return coins;
}

void CoinContainer::spawn(){
    srand (time(nullptr));
    int coinXposition = rand() % 4 + 1;
    coins.push_back(std::unique_ptr<Coin>(new Coin(gameData)));
    std::unique_ptr<Coin> & coin = coins[coins.size() -1];
    float coin_size = coin->getCoin().getGlobalBounds().width;

    if (coinXposition == 1) {
        coin->setPosition(sf::Vector2f((SCREEN_WIDTH / 20.0f) * 9, 0 - WALL_HEIGHT / 2.0f - coin_size / 2));
    }
    else if (coinXposition == 2) {
        coin->setPosition(sf::Vector2f((SCREEN_WIDTH / 20.0f) * 11, 0 - WALL_HEIGHT / 2.0f - coin_size / 2));
    }
    else if (coinXposition == 3) {
        coin->setPosition(sf::Vector2f(BORDER_WALL_WIDTH + 50, 0 - WALL_HEIGHT / 2.0f - coin_size / 2));
    }
    else{
        coin->setPosition(sf::Vector2f(BORDER_WALL_2_START - 50 - coin_size, 0 - WALL_HEIGHT / 2.0f - coin_size / 2));
    }
}

void CoinContainer::move(sf::Vector2f moveBy){
    for(auto & Coin : coins){
        Coin->move(moveBy);
    }

    coins.erase(std::remove_if( coins.begin(), coins.end(), [](std::unique_ptr<Coin> & x){
        return (x->getPosition().y >= SCREEN_HEIGHT + x-> getBounds().height);
    }), coins.end());
}

void CoinContainer::draw(){
    for(auto & Coin : coins){
        Coin->draw();
    }
}

