#include "SoundSettingsState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "CustomCharacterState.hpp"
#include "TutorialState.hpp"
#include <utility>

MainMenuState::MainMenuState(GameDataReference data) : game_data(std::move(data)) {}

void MainMenuState::Init() {
    game_data->assets.loadTextureFromFile("Arrow Left", ARROW_LEFT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Right", ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("BackgroundGround", BACKGROUND_GROUND_PATH);
    game_data->assets.loadTextureFromFile("BackgroundNoClouds", BACKGROUND_NO_CLOUDS_PATH);
    game_data->assets.loadTextureFromFile("Banner", GAME_TITLE_PATH);
    game_data->assets.loadTextureFromFile("Buy Button", BUY_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Coin", COIN_PATH);
    game_data->assets.loadTextureFromFile("Customize Button", CUSTOMIZE_BUTTON_PATH);
    game_data->assets.loadTextureFromFile("Equip Button", EQUIP_BUTTON_PATH);
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
    game_data->assets.loadTextureFromFile("SkyToSpaceBackground", BACKGROUND_SKY_TO_SPACE_PATH);
    game_data->assets.loadTextureFromFile("SpaceBackground", SPACE_BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("SpaghettiMonsterBackground", SPACE_BACKGROUND_SPAGHETTI_MONSTER_PATH);
    game_data->assets.loadTextureFromFile("Controls Button", CONTROLS_BUTTON_PATH);


    game_data->assets.loadFontFromFile("Bauhaus", BAUHAUS_FONT_PATH);
    game_data->assets.loadFontFromFile("8-bit", BIT_FONT_PATH);

    game_data->assets.loadSoundBufferFromFile("clickSound", SOUND_CLICK_PATH);
    game_data->assets.loadSoundBufferFromFile("customClickSound", SOUND_CLICK_CUSTOM_PATH);
    game_data->assets.loadSoundBufferFromFile("coinPickup", SOUND_COIN_PICKUP_PATH);
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
    _tutorialButton.setTexture(game_data->assets.GetTexture("Controls Button"));

    _title.setOrigin(_title.getGlobalBounds().width/2, _title.getGlobalBounds().height/2);
    _playButton.setOrigin(_playButton.getGlobalBounds().width/2, _playButton.getGlobalBounds().height/2);
    _tutorialButton.setOrigin(_tutorialButton.getGlobalBounds().width/2, _tutorialButton.getGlobalBounds().height/2);
    _settingsButton.setOrigin(_settingsButton.getGlobalBounds().width/2, _settingsButton.getGlobalBounds().height/2);
    _customButton.setOrigin(_customButton.getGlobalBounds().width/2, _customButton.getGlobalBounds().height/2);
    _banner.setOrigin(_banner.getGlobalBounds().width/2, _banner.getGlobalBounds().height/2);



    _title.setPosition(SCREEN_WIDTH/2.0f, _title.getGlobalBounds().height);
    _playButton.setPosition((SCREEN_WIDTH/4.0f)*2, (SCREEN_HEIGHT/4.0f)*2);
    _tutorialButton.setPosition((SCREEN_WIDTH/30.0f)*15, (SCREEN_HEIGHT/4.0f)*3);
    _settingsButton.setPosition((SCREEN_WIDTH/30.0f)*7, (SCREEN_HEIGHT/4.0f)*3);
    _customButton.setPosition((SCREEN_WIDTH/30.0f)*23, (SCREEN_HEIGHT/4.0f)*3);
    _banner.setPosition((SCREEN_WIDTH/2.0f), SCREEN_HEIGHT-_banner.getGlobalBounds().height);

    _quote.setFont(game_data->assets.GetFont("8-bit"));
    _quote.setString(quoteVector[std::rand() % quoteVector.size()]);
    _quote.setCharacterSize(MAIN_MENU_FONT_SIZE);
    _quote.setRotation(-8);
    _quote.setPosition(680,110);
    _quote.setOrigin(_quote.getGlobalBounds().width/2, _quote.getLocalBounds().height/2);
    _quote.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));

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
            }else if (game_data->input.IsSpriteClicked(_tutorialButton, sf::Mouse::Left, game_data->window)) {
                    if (!prevMousestate) {
                        if (game_data->json.Get_Soundstate()) {
                            _clickSound.play();
                        }
                        game_data->machine.AddGameState(GameStateReference(new TutorialState(game_data)), false);
                        prevMousestate = true;
                    }
            } else {
                prevMousestate = false;
            }
        }
    }
}

void MainMenuState::Resume() {
    scaler = MAIN_MENU_FONT_SIZE_SCALER;
    _clickSound.setVolume((float)game_data->json.Get_Soundvolume());
    _quote.setString(quoteVector[std::rand() % quoteVector.size()]);
    _quote.setPosition(680,110);
    _quote.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

void MainMenuState::Update(float delta) {
    if(fontSize == fontSizeOrigin + 5 * scaler){
        scaler *= -1;
    }
    _quote.setCharacterSize(fontSize);
    _quote.setOrigin(_quote.getGlobalBounds().width/2, _quote.getLocalBounds().height/2);
    fontSize += scaler;
}

void MainMenuState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_title);
    game_data->window.draw(_playButton);
    game_data->window.draw(_tutorialButton);
    game_data->window.draw(_settingsButton);
    game_data->window.draw(_customButton);
    game_data->window.draw(_banner);
    game_data->window.draw(_quote);
    game_data->window.display();
}
