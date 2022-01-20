//
// Created by coenc on 20/01/2022.
//

#include "MainMenuState.hpp"

MainMenuState::MainMenuState(GameDataReference data) : game_data(data) {}

void MainMenuState::Init() {
    game_data->assets.loadTextureFromFile("StartUp State Background", BACKGROUND_PATH);

    _background.setTexture(this->game_data->assets.GetTexture("StartUp State Background"));
}

void MainMenuState::HandleInput() {
    sf::Event event;

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
    }
}

void MainMenuState::Update(float delta) {

}

void MainMenuState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.display();
}