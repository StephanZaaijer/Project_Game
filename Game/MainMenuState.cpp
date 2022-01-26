#include "SoundSettingsState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "CustomCharacterState.hpp"
#include <utility>

MainMenuState::MainMenuState(GameDataReference data) : game_data(std::move(data)) {}

void MainMenuState::Init() {
    if( !_clickBuffer.loadFromFile(SOUND_CLICK_PATH)){
        std::cout << "ERROR loading click sound" << std::endl;
    }

    _clickSound.setBuffer( _clickBuffer );
    _clickSound.setVolume(game_data->json.Get_Soundvolume());

    game_data->assets.loadTextureFromFile("MainMenu State Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("MainMenu State Banner", GAME_TITLE_PATH);
    game_data->assets.loadTextureFromFile("MainMenu State groep6 Banner", GROEP_6_BANNER_PATH);
    game_data->assets.loadTextureFromFile("MainMenu Play Button", MAIN_MENU_PLAY_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("MainMenu Settings Button", MAIN_MENU_SETTINGS_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("MainMenu Custom Button", MAIN_MENU_CUSTOM_BUTTON_PATH);

    _background.setTexture(game_data->assets.GetTexture("MainMenu State Background"));
    _title.setTexture(game_data->assets.GetTexture("MainMenu State Banner"));
    _banner.setTexture(game_data->assets.GetTexture("MainMenu State groep6 Banner"));
    _playButton.setTexture(game_data->assets.GetTexture("MainMenu Play Button"));
    _settingsButton.setTexture(game_data->assets.GetTexture("MainMenu Settings Button"));
    _customButton.setTexture(game_data->assets.GetTexture("MainMenu Custom Button"));

    _title.setPosition((SCREEN_WIDTH/2.0f - (_title.getGlobalBounds().width/2)), _title.getGlobalBounds().height/2);
    _playButton.setPosition((SCREEN_WIDTH/2.0f - (_playButton.getGlobalBounds().width/2)), _title.getGlobalBounds().height*2);
    _settingsButton.setPosition(_playButton.getGlobalBounds().left - _playButton.getGlobalBounds().width, _title.getGlobalBounds().height*2);
    _customButton.setPosition(_playButton.getGlobalBounds().left + _playButton.getGlobalBounds().width , _title.getGlobalBounds().height*2);
    _banner.setPosition((SCREEN_WIDTH/2.0f - (_banner.getGlobalBounds().width/2)), SCREEN_HEIGHT - _banner.getGlobalBounds().height*1.5);
}

void MainMenuState::HandleInput() {
    sf::Event event{};


    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }

    if(game_data->input.IsSpriteClicked( _customButton, sf::Mouse::Left, game_data->window )){
        if(game_data->json.Get_Soundstate()){
            _clickSound.play();
        }
        game_data->machine.AddGameState(GameStateReference(new CustomCharacterState(game_data)), false);
    }

    if(game_data->input.IsSpriteClicked( _settingsButton, sf::Mouse::Left, game_data->window )){
        if(game_data->json.Get_Soundstate()){
            _clickSound.play();
        }
        game_data->machine.AddGameState(GameStateReference(new SoundSettingsState(game_data)), false);
    }

    if(game_data->input.IsSpriteClicked( _playButton, sf::Mouse::Left, game_data->window )){
        if(game_data->json.Get_Soundstate()){
            _clickSound.play();
        }
      game_data->machine.AddGameState(GameStateReference(new MainGameState(game_data)), true);
    }

        game_data->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, game_data->window);
    }
}

void MainMenuState::Update(float delta) {
    _clickSound.setVolume(game_data->json.Get_Soundvolume());
}

void MainMenuState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_title);
    game_data->window.draw(_playButton);
    game_data->window.draw(_settingsButton);
    game_data->window.draw(_customButton);
    game_data->window.draw(_banner);
    game_data->window.display();
}