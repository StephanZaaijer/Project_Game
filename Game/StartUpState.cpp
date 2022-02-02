#include "StartUpState.hpp"
#include "MainMenuState.hpp"
#include <utility>

StartUpState::StartUpState(GameDataReference gameData) : gameData(std::move(gameData)) {}

void StartUpState::init() {
    gameData->assets.loadTextureFromFile("Background", BACKGROUND_PATH);
    gameData->assets.loadTextureFromFile("StartUp State Image", GAME_IMAGE_PATH);
    gameData->assets.loadTextureFromFile("Banner", GAME_TITLE_PATH);
    gameData->assets.loadTextureFromFile("Groep6 Banner", GROEP_6_BANNER_PATH);
    background.setTexture(gameData->assets.getTexture("Background"));
    _logo.setTexture(gameData->assets.getTexture("StartUp State Image"));
    _title.setTexture(gameData->assets.getTexture("Banner"));
    _banner.setTexture(gameData->assets.getTexture("Groep6 Banner"));

    _title.setPosition((SCREEN_WIDTH / 2.0f - (_title.getGlobalBounds().width / 2)),
                       _title.getGlobalBounds().height / 2);
    _logo.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _banner.setPosition((SCREEN_WIDTH / 2.0f - (_banner.getGlobalBounds().width / 2)),
                        SCREEN_HEIGHT - _banner.getGlobalBounds().height * 1.5);
}

void StartUpState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
    }
}

void StartUpState::update(float delta) {
    if (_clock.getElapsedTime().asSeconds() > START_UP_TIME) {
        gameData->machine.AddGameState(GameStateReference(new MainMenuState(gameData)), true);
    }
}

void StartUpState::draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(_title);
    gameData->window.draw(_logo);
    gameData->window.draw(_banner);
    gameData->window.display();
}