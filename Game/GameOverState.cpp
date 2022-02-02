#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include <utility>

GameOverState::GameOverState(GameDataReference gameData) : gameData(std::move(gameData)){}

void GameOverState::init() {
    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    deathSound.setBuffer(gameData->assets.getSoundBuffer("deathSound"));

    clickSound.setVolume(gameData->json.getSoundVolume());
    deathSound.setVolume(gameData->json.getSoundVolume());

    if(gameData->json.getSoundState()){
        deathSound.play();
    }

    background.setTexture(gameData->assets.getTexture("Background"));
    restartButton.setTexture(gameData->assets.getTexture("Restart Button"));
    mainMenuButton.setTexture(gameData->assets.getTexture("MainMenu Button"));

    gameOverText.setFont(gameData->assets.getFont("Bauhaus"));
    score.setFont(gameData->assets.getFont("Bauhaus"));
    highscore.setFont( gameData->assets.getFont("Bauhaus"));

    restartButton.setPosition(SCREEN_WIDTH - (restartButton.getGlobalBounds().width * 2.9),
                               SCREEN_HEIGHT - (restartButton.getGlobalBounds().height * 1.1));
    mainMenuButton.setPosition(SCREEN_WIDTH - (mainMenuButton.getGlobalBounds().width * 1.9),
                               SCREEN_HEIGHT - (mainMenuButton.getGlobalBounds().height * 1.1));

    gameOverText.setString("GAMEOVER!");
    score.setString("Score: " + std::to_string(gameData -> score));
    gameData->json.setHighscore(gameData -> score);
    highscore.setString("highscore: " + std::to_string(gameData->json.getHighscore()));
    gameData->json.setCoins(gameData -> json.getCoins() + gameData -> coins);

    gameOverText.setCharacterSize(TEXT_TITLE_SIZE);
    score.setCharacterSize(GAME_OVER_SCORE_TEXT_SIZE);
    highscore.setCharacterSize(GAME_OVER_SCORE_TEXT_SIZE);

    gameOverText.setFillColor(TEXT_COLOR);
    score.setFillColor(TEXT_COLOR);
    highscore.setFillColor(TEXT_COLOR);


    auto tmpRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(tmpRect.left + tmpRect.width/2,tmpRect.top  + tmpRect.height/2);

    tmpRect = score.getLocalBounds();
    score.setOrigin(tmpRect.left + tmpRect.width/2,tmpRect.top  + tmpRect.height/2);

    tmpRect = highscore.getLocalBounds();
    highscore.setOrigin(tmpRect.left + tmpRect.width/2,tmpRect.top  + tmpRect.height/2);

    gameOverText.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 8.0f);
    score.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 3.0f);
    highscore.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f);
}

void GameOverState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
    }
    if(gameData->input.isKeyPressed(sf::Keyboard::Space) and !prevKeyState) {
        if (gameData->json.getSoundState()) {
            deathSound.stop();
            clickSound.play();
        }
        gameData->machine.AddGameState(GameStateReference(new MainGameState(gameData)), true);
    }
    else if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
        if (!prevButtonState) {
            if (gameData->input.isSpriteClicked(restartButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.getSoundState()) {
                    deathSound.stop();
                    clickSound.play();
                }
                gameData->machine.AddGameState(GameStateReference(new MainGameState(gameData)), true);
            }
            else if (gameData->input.isSpriteClicked(mainMenuButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.getSoundState()) {
                    clickSound.play();
                }
                gameData->machine.AddGameState(GameStateReference(new MainMenuState(gameData)), true);
            }
        }
    }
    prevKeyState=gameData->input.isKeyPressed(sf::Keyboard::Space);
    prevButtonState=gameData->input.isButtonPressed(sf::Mouse::Left);
}

void GameOverState::update(float delta) {
}

void GameOverState::draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(gameOverText);
    gameData->window.draw(restartButton);
    gameData->window.draw(mainMenuButton);
    gameData->window.draw(gameOverText);
    gameData->window.draw(score);
    gameData->window.draw(highscore);
    gameData->window.display();
}
