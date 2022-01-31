#include "StartUpState.hpp"
#include "MainMenuState.hpp"
#include <utility>

StartUpState::StartUpState(GameDataReference data) : game_data(std::move(data)) {}

void StartUpState::Init() {
    game_data->assets.loadTextureFromFile("Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("StartUp State Image", GAME_IMAGE_PATH);
    game_data->assets.loadTextureFromFile("Banner", GAME_TITLE_PATH);
    game_data->assets.loadTextureFromFile("Groep6 Banner", GROEP_6_BANNER_PATH);
    _background.setTexture(game_data->assets.GetTexture("Background"));
    _logo.setTexture(game_data->assets.GetTexture("StartUp State Image"));
    _title.setTexture(game_data->assets.GetTexture("Banner"));
    _banner.setTexture(game_data->assets.GetTexture("Groep6 Banner"));

    _title.setPosition((SCREEN_WIDTH / 2.0f - (_title.getGlobalBounds().width / 2)),
                       _title.getGlobalBounds().height / 2);
    _logo.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _banner.setPosition((SCREEN_WIDTH / 2.0f - (_banner.getGlobalBounds().width / 2)),
                        SCREEN_HEIGHT - _banner.getGlobalBounds().height * 1.5);
}

void StartUpState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
    }
}

void StartUpState::Update(float delta) {
    if (_clock.getElapsedTime().asSeconds() > START_UP_TIME) {
        game_data->machine.AddGameState(GameStateReference(new MainMenuState(game_data)), true);
    }
}

void StartUpState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_title);
    game_data->window.draw(_logo);
    game_data->window.draw(_banner);
    game_data->window.display();
}