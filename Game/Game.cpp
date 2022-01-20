#include "Game.hpp"
#include "StartUpState.hpp"
#include "IconArray.hpp"

Game::Game(const int &screen_width, const int &screen_height, const std::string &game_title) {
    game_data->window.create(sf::VideoMode(screen_width, screen_height), game_title, sf::Style::Close | sf::Style::Titlebar);
    game_data->window.setIcon(50,50, iconArray);

    game_data->machine.AddGameState(GameStateReference(new StarUpState(game_data)), false);
    start();
}

void Game::start(){
    float new_time, frameTime;

    float current_time = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0;

    while(game_data->window.isOpen()){
        game_data->machine.ProcessGameStateChanges();
        new_time = clock.getElapsedTime().asSeconds();
        frameTime = new_time - current_time;
        if (frameTime > 0.25){
            frameTime = 0.25;
        }
        current_time = new_time;
        accumulator += frameTime;

        while (accumulator>=delta){
            game_data->machine.GetActiveGameState()->HandleInput();
            game_data->machine.GetActiveGameState()->Update(delta);
            accumulator -= delta;
        }
        game_data -> machine.GetActiveGameState()->Draw(accumulator / delta);
    }
}


