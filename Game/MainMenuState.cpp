//
// Created by coenc on 20/01/2022.
//

#include "MainMenuState.hpp"
#include "SoundSettingsState.hpp"

MainMenuState::MainMenuState(GameDataReference data) : game_data(data) {}

void MainMenuState::Init() {
    game_data->assets.loadTextureFromFile("MainMenu State Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("MainMenu State Banner", GAME_TITLE_PATH);
    game_data->assets.loadTextureFromFile("MainMenu State groep6 Banner", GROEP_6_BANNER);
    game_data->assets.loadTextureFromFile("MainMenu Play Button", MAIN_MENU_PLAY_BUTTON);
    game_data->assets.loadTextureFromFile("MainMenu Settings Button", MAIN_MENU_SETTINGS_BUTTON);
    game_data->assets.loadTextureFromFile("MainMenu Exit Button", MAIN_MENU_EXIT_BUTTON);

    _background.setTexture(this->game_data->assets.GetTexture("MainMenu State Background"));
    _title.setTexture(this->game_data->assets.GetTexture("MainMenu State Banner"));
    _banner.setTexture(this->game_data->assets.GetTexture("MainMenu State groep6 Banner"));
    _playButton.setTexture(this->game_data->assets.GetTexture("MainMenu Play Button"));
    _settingsButton.setTexture(this->game_data->assets.GetTexture("MainMenu Settings Button"));
    _exitButton.setTexture(this->game_data->assets.GetTexture("MainMenu Exit Button"));

    _title.setPosition({(SCREEN_WIDTH/2 - (_title.getGlobalBounds().width/2)), _title.getGlobalBounds().height/2});
    _playButton.setPosition({(SCREEN_WIDTH/2 - (_playButton.getGlobalBounds().width/2)), _title.getGlobalBounds().height*2});
    _settingsButton.setPosition({_playButton.getGlobalBounds().left - _playButton.getGlobalBounds().width, _title.getGlobalBounds().height*2});
    _exitButton.setPosition({_playButton.getGlobalBounds().left + _playButton.getGlobalBounds().width , _title.getGlobalBounds().height*2});

    _banner.setPosition((SCREEN_WIDTH/2 - (_banner.getGlobalBounds().width/2)), SCREEN_HEIGHT - _banner.getGlobalBounds().height*1.5);

}

void MainMenuState::HandleInput() {
    sf::Event event;

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }

        if(game_data->input.IsSpriteClicked( _exitButton, sf::Mouse::Left, game_data->window )){
            game_data->window.close();
        }

        if(game_data->input.IsSpriteClicked( _settingsButton, sf::Mouse::Left, game_data->window )){
            game_data->machine.AddGameState(GameStateReference(new SoundSettingsState(game_data)), false);
        }

        if(game_data->input.IsSpriteClicked( _playButton, sf::Mouse::Left, game_data->window )){
            //game_data->machine.AddGameState(GameStateReference(new (game_data)), false);

        }
    }
}

void MainMenuState::Update(float delta) {

}

void MainMenuState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_title);
    game_data->window.draw(_playButton);
    game_data->window.draw(_settingsButton);
    game_data->window.draw(_exitButton);
    game_data->window.draw(_banner);

    game_data->window.display();
}