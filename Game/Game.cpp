#include "Game.hpp"
#include "StartUpState.hpp"
#include "IconArray.hpp"

Game::Game(const int &screenWidth, const int &screenHeight, const std::string &gameTitle) {
    gameData->window.create(sf::VideoMode(SCREEN_WIDTH, screenHeight), gameTitle, sf::Style::Close | sf::Style::Titlebar);
    gameData->window.setIcon(100,100, iconArray2);
    gameData->machine.AddGameState(GameStateReference(new StartUpState(gameData)));
    start();
}

void Game::start() {
    float new_time, frameTime;
    float current_time = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0;
    while (gameData->window.isOpen()) {
        gameData->machine.ProcessGameStateChanges();
        new_time = clock.getElapsedTime().asSeconds();
        frameTime = new_time - current_time;
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        current_time = new_time;
        accumulator += frameTime;

        while (accumulator >= delta) {
            gameData->machine.GetActiveGameState()->handleInput();
            gameData->machine.GetActiveGameState()->update();
            accumulator -= delta;
        }
        gameData->machine.GetActiveGameState()->draw();
        sf::sleep(sf::milliseconds(20));
        gameData->json.update();
    }
    gameData->json.directWrite();
}

