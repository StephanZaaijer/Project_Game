#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include <utility>

GameOverState::GameOverState(GameDataReference data) : gameData(std::move(data)){}

void GameOverState::Init() {
    _clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    _deathSound.setBuffer(gameData->assets.getSoundBuffer("deathSound"));

    _clickSound.setVolume(gameData->json.Get_Soundvolume());
    _deathSound.setVolume(gameData->json.Get_Soundvolume());

    if(gameData->json.Get_Soundstate()){
        _deathSound.play();
    }

    background.setTexture(gameData->assets.getTexture("Background"));
    _restartButton.setTexture(gameData->assets.getTexture("Restart Button"));
    _mainMenuButton.setTexture(gameData->assets.getTexture("MainMenu Button"));

    _gameOverText.setFont(gameData->assets.getFont("Bauhaus"));
    _score.setFont(gameData->assets.getFont("Bauhaus"));
    _highscore.setFont( gameData->assets.getFont("Bauhaus"));

    _restartButton.setPosition(ScreenWidth - (_restartButton.getGlobalBounds().width * 2.9),
                               SCREEN_HEIGHT - (_restartButton.getGlobalBounds().height * 1.1));
    _mainMenuButton.setPosition(ScreenWidth - (_mainMenuButton.getGlobalBounds().width * 1.9),
                               SCREEN_HEIGHT - (_mainMenuButton.getGlobalBounds().height * 1.1));

    _gameOverText.setString("GAMEOVER!");
    _score.setString("Score: " + std::to_string(gameData -> score));
    gameData->json.Set_Highscore(gameData -> score);
    _highscore.setString("Highscore: " + std::to_string(gameData->json.Get_Highscore()));
    gameData->json.Set_Coins(gameData -> json.Get_Coins() + gameData -> coins);

    _gameOverText.setCharacterSize(TEXT_TITLE_SIZE);
    _score.setCharacterSize(GAME_OVER_SCORE_TEXT_SIZE);
    _highscore.setCharacterSize(GAME_OVER_SCORE_TEXT_SIZE);

    _gameOverText.setFillColor(TEXT_COLOR);
    _score.setFillColor(TEXT_COLOR);
    _highscore.setFillColor(TEXT_COLOR);


    auto tmpRect = _gameOverText.getLocalBounds();
    _gameOverText.setOrigin(tmpRect.left + tmpRect.width/2,tmpRect.top  + tmpRect.height/2);

    tmpRect = _score.getLocalBounds();
    _score.setOrigin(tmpRect.left + tmpRect.width/2,tmpRect.top  + tmpRect.height/2);

    tmpRect = _highscore.getLocalBounds();
    _highscore.setOrigin(tmpRect.left + tmpRect.width/2,tmpRect.top  + tmpRect.height/2);

    _gameOverText.setPosition(ScreenWidth / 2.0f,SCREEN_HEIGHT / 8.0f);
    _score.setPosition(ScreenWidth / 2.0f,SCREEN_HEIGHT / 3.0f);
    _highscore.setPosition(ScreenWidth / 2.0f,SCREEN_HEIGHT / 2.0f);
}

void GameOverState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
    }
    if(gameData->input.IsKeyPressed(sf::Keyboard::Space) and !prevKeystate) {
        if (gameData->json.Get_Soundstate()) {
            _deathSound.stop();
            _clickSound.play();
        }
        gameData->machine.AddGameState(GameStateReference(new MainGameState(gameData)), true);
    }
    else if (gameData->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, gameData->window)) {
        if (!prevButtonState) {
            if (gameData->input.IsSpriteClicked(_restartButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.Get_Soundstate()) {
                    _deathSound.stop();
                    _clickSound.play();
                }
                gameData->machine.AddGameState(GameStateReference(new MainGameState(gameData)), true);
            }
            else if (gameData->input.IsSpriteClicked(_mainMenuButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                gameData->machine.AddGameState(GameStateReference(new MainMenuState(gameData)), true);
            }
        }
    }
    prevKeystate=gameData->input.IsKeyPressed(sf::Keyboard::Space);
    prevButtonState=gameData->input.IsButtonPressed(sf::Mouse::Left);
}

void GameOverState::Update(float delta) {
}

void GameOverState::Draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(_gameOverText);
    gameData->window.draw(_restartButton);
    gameData->window.draw(_mainMenuButton);
    gameData->window.draw(_gameOverText);
    gameData->window.draw(_score);
    gameData->window.draw(_highscore);
    gameData->window.display();
}
