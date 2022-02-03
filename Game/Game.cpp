#include "Game.hpp"
#include "StartUpState.hpp"
#include "IconArray.hpp"

Game::Game(const int &screenWidth, const int &screenHeight, const std::string &gameTitle) {
    gameData->window.create(sf::VideoMode(SCREEN_WIDTH, screenHeight), gameTitle, sf::Style::Close | sf::Style::Titlebar);
    gameData->window.setIcon(100,100, iconArray2);
    gameData->machine.addGameState(GameStateReference(new StartUpState(gameData)));
    start();
}

void Game::start() {
    float newTime, frameTime;
    float currentTime = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0;
    while (gameData->window.isOpen()) {
        gameData->machine.processGameStateChanges();
        newTime = clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= delta) {
            gameData->machine.getActiveGameState()->handleInput();
            gameData->machine.getActiveGameState()->update();
            accumulator -= delta;
        }
        gameData->machine.getActiveGameState()->draw();
        sf::sleep(sf::milliseconds(20));
        gameData->json.update();
    }
    gameData->json.directWrite();
}

