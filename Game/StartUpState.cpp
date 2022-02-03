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
    logo.setTexture(gameData->assets.getTexture("StartUp State Image"));
    title.setTexture(gameData->assets.getTexture("Banner"));
    banner.setTexture(gameData->assets.getTexture("Groep6 Banner"));

    title.setPosition((SCREEN_WIDTH / 2.0f - (title.getGlobalBounds().width / 2)),
                       title.getGlobalBounds().height / 2);
    logo.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    banner.setPosition((SCREEN_WIDTH / 2.0f - (banner.getGlobalBounds().width / 2)),
                        SCREEN_HEIGHT - banner.getGlobalBounds().height * 1.5);
}

void StartUpState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
    }
}

void StartUpState::draw() {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(title);
    gameData->window.draw(logo);
    gameData->window.draw(banner);
    gameData->window.display();
}