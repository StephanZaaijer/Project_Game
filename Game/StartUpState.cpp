#include "StartUpState.hpp"
#include "MainGameState.hpp"
StartUpState::StartUpState(GameDataReference data) : game_data(data) {}

void StartUpState::Init() {
//    game_data->assets.loadTextureFromFile("StartUp State Background", "D:/TI_SOFTWARE/Project_Game2/Project_Game/Project_Game/Game/Assets/fire.jpg");
//    _background.setTexture(this->game_data->assets.GetTexture("StartUp State Background"));
}

void StartUpState::HandleInput() {
    sf::Event event;

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
    }
}

void StartUpState::Update(float delta) {
    if (_clock.getElapsedTime().asSeconds() > 5) {
        game_data->machine.AddGameState(GameStateReference(new MainGameState(game_data)));
    }
}

void StartUpState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.display();
}