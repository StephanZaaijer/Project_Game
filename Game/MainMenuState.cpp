#include "SoundSettingsState.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "CustomCharacterState.hpp"
#include "TutorialState.hpp"
#include <utility>

MainMenuState::MainMenuState(GameDataReference gameData) : gameData(std::move(gameData)) {}

void MainMenuState::init() {
    gameData->assets.loadTextureFromFile("Arrow Left", ARROW_LEFT_BUTTON);
    gameData->assets.loadTextureFromFile("Arrow Right", ARROW_RIGHT_BUTTON);
    gameData->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Background", BACKGROUND_PATH);
    gameData->assets.loadTextureFromFile("BackgroundGround", BACKGROUND_GROUND_PATH);
    gameData->assets.loadTextureFromFile("BackgroundNoClouds", BACKGROUND_NO_CLOUDS_PATH);
    gameData->assets.loadTextureFromFile("Banner", GAME_TITLE_PATH);
    gameData->assets.loadTextureFromFile("Buy Button", BUY_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Coin", COIN_PATH);
    gameData->assets.loadTextureFromFile("Customize Button", CUSTOMIZE_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Equip Button", EQUIP_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Green music Button", MUSIC_BUTTON_GREEN_PATH);
    gameData->assets.loadTextureFromFile("Green Sound Button", SOUND_BUTTON_GREEN_PATH);
    gameData->assets.loadTextureFromFile("Groep6 Banner", GROEP_6_BANNER_PATH);
    gameData->assets.loadTextureFromFile("MainMenu Button", MAIN_MENU_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Play Button", PLAY_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Random Button", RANDOM_BUTTON);
    gameData->assets.loadTextureFromFile("Red music Button", MUSIC_BUTTON_RED_PATH);
    gameData->assets.loadTextureFromFile("Red Sound Button", SOUND_BUTTON_RED_PATH);
    gameData->assets.loadTextureFromFile("Restart Button", RESTART_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("Settings Button", SETTINGS_BUTTON_PATH);
    gameData->assets.loadTextureFromFile("SkyToSpaceBackground", BACKGROUND_SKY_TO_SPACE_PATH);
    gameData->assets.loadTextureFromFile("SpaceBackground", SPACE_BACKGROUND_PATH);
    gameData->assets.loadTextureFromFile("SpaghettiMonsterBackground", SPACE_BACKGROUND_SPAGHETTI_MONSTER_PATH);
    gameData->assets.loadTextureFromFile("Controls Button", CONTROLS_BUTTON_PATH);


    gameData->assets.loadFontFromFile("Bauhaus", BAUHAUS_FONT_PATH);
    gameData->assets.loadFontFromFile("8-bit", BIT_FONT_PATH);

    gameData->assets.loadSoundBufferFromFile("clickSound", SOUND_CLICK_PATH);
    gameData->assets.loadSoundBufferFromFile("customClickSound", SOUND_CLICK_CUSTOM_PATH);
    gameData->assets.loadSoundBufferFromFile("coinPickup", SOUND_COIN_PICKUP_PATH);
    gameData->assets.loadSoundBufferFromFile("deathSound", SOUND_DEATH_PATH);
    gameData->assets.loadSoundBufferFromFile("gameMusic", MUSIC_GAME_PATH);
    gameData->assets.loadSoundBufferFromFile("jumpSound", SOUND_JUMP_PATH);
    gameData->assets.loadSoundBufferFromFile("pauseSound", SOUND_PAUSE_PATH);
    gameData->assets.loadSoundBufferFromFile("resumeSound", SOUND_RESUME_PATH);


    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    clickSound.setVolume(gameData->json.getSoundVolume());

    background.setTexture(gameData->assets.getTexture("Background"));
    _title.setTexture(gameData->assets.getTexture("Banner"));
    _banner.setTexture(gameData->assets.getTexture("Groep6 Banner"));
    _playButton.setTexture(gameData->assets.getTexture("Play Button"));
    _settingsButton.setTexture(gameData->assets.getTexture("Settings Button"));
    _customButton.setTexture(gameData->assets.getTexture("Customize Button"));
    _tutorialButton.setTexture(gameData->assets.getTexture("Controls Button"));

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

    quoteVector = gameData->json.getQuotes();

    _quote.setFont(gameData->assets.getFont("8-bit"));
    _quote.setString(quoteVector[std::rand() % quoteVector.size()]);
    _quote.setCharacterSize(MAIN_MENU_FONT_SIZE);
    _quote.setRotation(-8);
    _quote.setPosition(680,110);
    _quote.setOrigin(_quote.getGlobalBounds().width/2, _quote.getLocalBounds().height/2);
    _quote.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));

}

void MainMenuState::handleInput() {
    sf::Event event{};

    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
        if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if (gameData->input.isSpriteClicked(_customButton, sf::Mouse::Left, gameData->window)) {
                if (!prevMousestate) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.AddGameState(GameStateReference(new CustomCharacterState(gameData)), false);
                    prevMousestate = true;
                }
            } else if (gameData->input.isSpriteClicked(_settingsButton, sf::Mouse::Left, gameData->window)) {
                if (!prevMousestate) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.AddGameState(GameStateReference(new SoundSettingsState(gameData)), false);
                    prevMousestate = true;
                }
            } else if (gameData->input.isSpriteClicked(_playButton, sf::Mouse::Left, gameData->window)) {
                if (!prevMousestate) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.AddGameState(GameStateReference(new MainGameState(gameData)), true);
                    prevMousestate = true;
                }
            }else if (gameData->input.isSpriteClicked(_tutorialButton, sf::Mouse::Left, gameData->window)) {
                    if (!prevMousestate) {
                        if (gameData->json.getSoundState()) {
                            clickSound.play();
                        }
                        gameData->machine.AddGameState(GameStateReference(new TutorialState(gameData)), false);
                        prevMousestate = true;
                    }
            } else {
                prevMousestate = false;
            }
        }
    }
}

void MainMenuState::resume() {
    scaler = MAIN_MENU_FONT_SIZE_SCALER;
    clickSound.setVolume((float)gameData->json.getSoundVolume());
    _quote.setString(quoteVector[std::rand() % quoteVector.size()]);
    _quote.setPosition(680,110);
    _quote.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

void MainMenuState::update(float delta) {
    if(fontSize == fontSizeOrigin + 5 * scaler){
        scaler *= -1;
    }
    _quote.setCharacterSize(fontSize);
    _quote.setOrigin(_quote.getGlobalBounds().width/2, _quote.getLocalBounds().height/2);
    fontSize += scaler;
}

void MainMenuState::draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(_title);
    gameData->window.draw(_playButton);
    gameData->window.draw(_tutorialButton);
    gameData->window.draw(_settingsButton);
    gameData->window.draw(_customButton);
    gameData->window.draw(_banner);
    gameData->window.draw(_quote);
    gameData->window.display();
}
