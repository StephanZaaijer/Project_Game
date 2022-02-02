#include "CoinContainer.hpp"

Coin_Container::Coin_Container(GameDataReference game_data):
    game_data (game_data)
{}

std::vector<std::unique_ptr<Coin>> & Coin_Container::getCoins(){
    return coins;
}

void Coin_Container::spawn(){
    srand (time(NULL));
    int Coin_X_Position = rand() % 4 + 1;
    coins.push_back(std::unique_ptr<Coin>(new Coin(game_data)));
    std::unique_ptr<Coin> & coin = coins[coins.size() -1];
    float coin_size = coin -> get_coin().getGlobalBounds().width;

    if (Coin_X_Position == 1) {
        coin -> set_position(sf::Vector2f((SCREEN_WIDTH / 20.0f) * 9, 0 - WALL_HEIGHT / 2 - coin_size / 2));
    }
    else if (Coin_X_Position == 2) {
        coin -> set_position(sf::Vector2f((SCREEN_WIDTH / 20.0f) * 11, 0 - WALL_HEIGHT / 2 - coin_size / 2));
    }
    else if (Coin_X_Position == 3) {
        coin -> set_position(sf::Vector2f(BORDER_WALL_WIDTH + 50, 0 - WALL_HEIGHT / 2 - coin_size / 2));
    }
    else{
        coin -> set_position(sf::Vector2f(BORDER_WALL_2_START - 50 - coin_size, 0 - WALL_HEIGHT / 2 - coin_size / 2));
    }
}

void Coin_Container::move(sf::Vector2f move_by){
    for(auto & Coin : coins){
        Coin -> move(move_by);
    }

    coins.erase(std::remove_if( coins.begin(), coins.end(), [](std::unique_ptr<Coin> & x){
        return (x -> getPosition().y >= SCREEN_HEIGHT + x-> getBounds().height);
    }), coins.end());
}

void Coin_Container::draw(){
    for(auto & Coin : coins){
        Coin -> draw();
    }
}