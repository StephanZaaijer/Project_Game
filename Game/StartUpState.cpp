#include "StartUpState.hpp"
#include "MainGameState.hpp"
StarUpState::StarUpState(GameDataReference data) : game_data(data) {}

void StarUpState::Init() {
//    game_data->assets.loadTextureFromFile("StartUp State Background", "D:/TI_SOFTWARE/Project_Game2/Project_Game/Project_Game/Game/Assets/fire.jpg");
//    _background.setTexture(this->game_data->assets.GetTexture("StartUp State Background"));
}

void StarUpState::HandleInput() {
    sf::Event event;

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
    }
}

void StarUpState::Update(float delta) {
    if (_clock.getElapsedTime().asSeconds() > 3) {
        game_data->machine.AddGameState(GameStateReference(new MainGameState(game_data)));
    }
}

void StarUpState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.display();
}