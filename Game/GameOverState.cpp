#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include <utility>

GameOverState::GameOverState(GameDataReference data) : game_data(std::move(data)){}

void GameOverState::Init() {
    game_data->assets.loadTextureFromFile("State Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("Restart Button", RESTART_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Main Menu Button", MAIN_MENU_BUTTON_PATH);

    game_data->assets.loadFontFromFile("Bauhaus font", BAUHAUS_FONT_PATH);

    _background.setTexture(this->game_data->assets.GetTexture("State Background"));
    _restartButton.setTexture(this->game_data->assets.GetTexture("Restart Button"));
    _mainMenuButton.setTexture(this->game_data->assets.GetTexture("Main Menu Button"));

    _gameOverText.setFont(this->game_data->assets.GetFont("Bauhaus font"));
    _score.setFont(this->game_data->assets.GetFont("Bauhaus font"));
    _highscore.setFont(this->game_data->assets.GetFont("Bauhaus font"));


    _restartButton.setPosition(SCREEN_WIDTH - (_restartButton.getGlobalBounds().width * 2.9),
                               SCREEN_HEIGHT - (_restartButton.getGlobalBounds().height * 1.1));
    _mainMenuButton.setPosition(SCREEN_WIDTH - (_mainMenuButton.getGlobalBounds().width * 1.9),
                               SCREEN_HEIGHT - (_mainMenuButton.getGlobalBounds().height * 1.1));

    _gameOverText.setString("GAMEOVER!");
    _score.setString("Score: 200");
    _highscore.setString("Highscore: 342");

    _gameOverText.setCharacterSize(TEXT_TITLE_SIZE);
    _score.setCharacterSize(120);
    _highscore.setCharacterSize(120);

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

void GameOverState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
        if(game_data->input.IsSpriteClicked( _restartButton, sf::Mouse::Left, game_data->window )){
            std::cout << "restart \n";
        }
        if(game_data->input.IsSpriteClicked( _mainMenuButton, sf::Mouse::Left, game_data->window )){
            game_data->machine.AddGameState(GameStateReference(new MainMenuState(game_data)), true);
        }
    }
}

void GameOverState::Update(float delta) {
}

void GameOverState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_gameOverText);
    game_data->window.draw(_restartButton);
    game_data->window.draw(_mainMenuButton);
    game_data->window.draw(_gameOverText);
    game_data->window.draw(_score);
    game_data->window.draw(_highscore);
    game_data->window.display();
}