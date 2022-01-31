#include "SoundSettingsState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "CustomCharacterState.hpp"
#include <utility>

MainMenuState::MainMenuState(GameDataReference data) : game_data(std::move(data)) {}

void MainMenuState::Init() {
    game_data->assets.loadTextureFromFile("Arrow Left", ARROW_LEFT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Right", ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("BackgroundGround", BACKGROUND_GROUND_PATH);
    game_data->assets.loadTextureFromFile("BackgroundNoClouds", BACKGROUND_NO_CLOUDS_PATH);
    game_data->assets.loadTextureFromFile("SkyToSpaceBackground", BACKGROUND_SKY_TO_SPACE_PATH);
    game_data->assets.loadTextureFromFile("SpaceBackground", SPACE_BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("Banner", GAME_TITLE_PATH);
    game_data->assets.loadTextureFromFile("Customize Button", CUSTOMIZE_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Green Music Button", MUSIC_BUTTON_GREEN_PATH);
    game_data->assets.loadTextureFromFile("Green Sound Button", SOUND_BUTTON_GREEN_PATH);
    game_data->assets.loadTextureFromFile("Groep6 Banner", GROEP_6_BANNER_PATH);
    game_data->assets.loadTextureFromFile("MainMenu Button", MAIN_MENU_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Play Button", PLAY_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Random Button", RANDOM_BUTTON);
    game_data->assets.loadTextureFromFile("Red Music Button", MUSIC_BUTTON_RED_PATH);
    game_data->assets.loadTextureFromFile("Red Sound Button", SOUND_BUTTON_RED_PATH);
    game_data->assets.loadTextureFromFile("Restart Button", RESTART_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Settings Button", SETTINGS_BUTTON_PATH);

    game_data->assets.loadFontFromFile("Bauhaus", BAUHAUS_FONT_PATH);

    game_data->assets.loadSoundBufferFromFile("clickSound", SOUND_CLICK_PATH);
    game_data->assets.loadSoundBufferFromFile("customClickSound", SOUND_CLICK_CUSTOM_PATH);
    game_data->assets.loadSoundBufferFromFile("deathSound", SOUND_DEATH_PATH);
    game_data->assets.loadSoundBufferFromFile("gameMusic", MUSIC_GAME_PATH);
    game_data->assets.loadSoundBufferFromFile("jumpSound", SOUND_JUMP_PATH);
    game_data->assets.loadSoundBufferFromFile("pauseSound", SOUND_PAUSE_PATH);
    game_data->assets.loadSoundBufferFromFile("resumeSound", SOUND_RESUME_PATH);

    _clickSound.setBuffer(game_data->assets.GetSoundBuffer("clickSound"));
    _clickSound.setVolume(game_data->json.Get_Soundvolume());

    _background.setTexture(game_data->assets.GetTexture("Background"));
    _title.setTexture(game_data->assets.GetTexture("Banner"));
    _banner.setTexture(game_data->assets.GetTexture("Groep6 Banner"));
    _playButton.setTexture(game_data->assets.GetTexture("Play Button"));
    _settingsButton.setTexture(game_data->assets.GetTexture("Settings Button"));
    _customButton.setTexture(game_data->assets.GetTexture("Customize Button"));

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
        if (game_data->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, game_data->window)) {
            if (game_data->input.IsSpriteClicked(_customButton, sf::Mouse::Left, game_data->window)) {
                if (!prevMousestate) {
                    if (game_data->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    game_data->machine.AddGameState(GameStateReference(new CustomCharacterState(game_data)), false);
                    prevMousestate = true;
                }
            } else if (game_data->input.IsSpriteClicked(_settingsButton, sf::Mouse::Left, game_data->window)) {
                if (!prevMousestate) {
                    if (game_data->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    game_data->machine.AddGameState(GameStateReference(new SoundSettingsState(game_data)), false);
                    prevMousestate = true;
                }
            } else if (game_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, game_data->window)) {
                if (!prevMousestate) {
                    if (game_data->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    game_data->machine.AddGameState(GameStateReference(new MainGameState(game_data)), true);
                    prevMousestate = true;
                }
            } else {
                prevMousestate = false;
            }
        }
    }
}
void MainMenuState::Resume() {
    _clickSound.setVolume((float)game_data->json.Get_Soundvolume());
}

void MainMenuState::Update(float delta) {
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
