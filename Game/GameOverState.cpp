#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include <utility>

GameOverState::GameOverState(GameDataReference data) : game_data(std::move(data)){}

void GameOverState::Init() {
    _clickSound.setBuffer(game_data->assets.getSoundBuffer("clickSound"));
    _deathSound.setBuffer(game_data->assets.getSoundBuffer("deathSound"));

    _clickSound.setVolume(game_data->json.Get_Soundvolume());
    _deathSound.setVolume(game_data->json.Get_Soundvolume());

    if(game_data->json.Get_Soundstate()){
        _deathSound.play();
    }

    background.setTexture(game_data->assets.getTexture("Background"));
    _restartButton.setTexture(game_data->assets.getTexture("Restart Button"));
    _mainMenuButton.setTexture(game_data->assets.getTexture("MainMenu Button"));

    _gameOverText.setFont(game_data->assets.getFont("Bauhaus"));
    _score.setFont(game_data->assets.getFont("Bauhaus"));
    _highscore.setFont( game_data->assets.getFont("Bauhaus"));

    _restartButton.setPosition(SCREEN_WIDTH - (_restartButton.getGlobalBounds().width * 2.9),
                               SCREEN_HEIGHT - (_restartButton.getGlobalBounds().height * 1.1));
    _mainMenuButton.setPosition(SCREEN_WIDTH - (_mainMenuButton.getGlobalBounds().width * 1.9),
                               SCREEN_HEIGHT - (_mainMenuButton.getGlobalBounds().height * 1.1));

    _gameOverText.setString("GAMEOVER!");
    _score.setString("Score: " + std::to_string(game_data -> score));
    game_data->json.Set_Highscore(game_data -> score);
    _highscore.setString("Highscore: " + std::to_string(game_data->json.Get_Highscore()));
    game_data->json.Set_Coins(game_data -> json.Get_Coins() + game_data -> coins);

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

    _gameOverText.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 8.0f);
    _score.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 3.0f);
    _highscore.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f);
}

void GameOverState::handleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
    }
    if(game_data->input.IsKeyPressed(sf::Keyboard::Space) and !prevKeystate) {
        if (game_data->json.Get_Soundstate()) {
            _deathSound.stop();
            _clickSound.play();
        }
        game_data->machine.AddGameState(GameStateReference(new MainGameState(game_data)), true);
    }
    else if (game_data->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, game_data->window)) {
        if (!prevButtonState) {
            if (game_data->input.IsSpriteClicked(_restartButton, sf::Mouse::Left, game_data->window)) {
                if (game_data->json.Get_Soundstate()) {
                    _deathSound.stop();
                    _clickSound.play();
                }
                game_data->machine.AddGameState(GameStateReference(new MainGameState(game_data)), true);
            }
            else if (game_data->input.IsSpriteClicked(_mainMenuButton, sf::Mouse::Left, game_data->window)) {
                if (game_data->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                game_data->machine.AddGameState(GameStateReference(new MainMenuState(game_data)), true);
            }
        }
    }
    prevKeystate=game_data->input.IsKeyPressed(sf::Keyboard::Space);
    prevButtonState=game_data->input.IsButtonPressed(sf::Mouse::Left);
}

void GameOverState::Update(float delta) {
}

void GameOverState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(background);
    game_data->window.draw(_gameOverText);
    game_data->window.draw(_restartButton);
    game_data->window.draw(_mainMenuButton);
    game_data->window.draw(_gameOverText);
    game_data->window.draw(_score);
    game_data->window.draw(_highscore);
    game_data->window.display();
}
