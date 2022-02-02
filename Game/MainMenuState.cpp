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
    title.setTexture(gameData->assets.getTexture("Banner"));
    banner.setTexture(gameData->assets.getTexture("Groep6 Banner"));
    playButton.setTexture(gameData->assets.getTexture("Play Button"));
    settingsButton.setTexture(gameData->assets.getTexture("Settings Button"));
    customButton.setTexture(gameData->assets.getTexture("Customize Button"));
    tutorialButton.setTexture(gameData->assets.getTexture("Controls Button"));

    title.setOrigin(title.getGlobalBounds().width/2, title.getGlobalBounds().height/2);
    playButton.setOrigin(playButton.getGlobalBounds().width/2, playButton.getGlobalBounds().height/2);
    tutorialButton.setOrigin(tutorialButton.getGlobalBounds().width/2, tutorialButton.getGlobalBounds().height/2);
    settingsButton.setOrigin(settingsButton.getGlobalBounds().width/2, settingsButton.getGlobalBounds().height/2);
    customButton.setOrigin(customButton.getGlobalBounds().width/2, customButton.getGlobalBounds().height/2);
    banner.setOrigin(banner.getGlobalBounds().width/2, banner.getGlobalBounds().height/2);

    title.setPosition(SCREEN_WIDTH/2.0f, title.getGlobalBounds().height);
    playButton.setPosition((SCREEN_WIDTH/4.0f)*2, (SCREEN_HEIGHT/4.0f)*2);
    tutorialButton.setPosition((SCREEN_WIDTH/30.0f)*15, (SCREEN_HEIGHT/4.0f)*3);
    settingsButton.setPosition((SCREEN_WIDTH/30.0f)*7, (SCREEN_HEIGHT/4.0f)*3);
    customButton.setPosition((SCREEN_WIDTH/30.0f)*23, (SCREEN_HEIGHT/4.0f)*3);
    banner.setPosition((SCREEN_WIDTH/2.0f), SCREEN_HEIGHT-banner.getGlobalBounds().height);

    quoteVector = gameData->json.getQuotes();

    quote.setFont(gameData->assets.getFont("8-bit"));
    quote.setString(quoteVector[std::rand() % quoteVector.size()]);
    quote.setCharacterSize(MAIN_MENU_FONT_SIZE);
    quote.setRotation(-8);
    quote.setPosition(680,110);
    quote.setOrigin(quote.getGlobalBounds().width/2, quote.getLocalBounds().height/2);
    quote.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));

}

void MainMenuState::handleInput() {
    sf::Event event{};

    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
        if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if (gameData->input.isSpriteClicked(customButton, sf::Mouse::Left, gameData->window)) {
                if (!prevMouseState) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.addGameState(GameStateReference(new CustomCharacterState(gameData)), false);
                    prevMouseState = true;
                }
            } else if (gameData->input.isSpriteClicked(settingsButton, sf::Mouse::Left, gameData->window)) {
                if (!prevMouseState) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.addGameState(GameStateReference(new SoundSettingsState(gameData)), false);
                    prevMouseState = true;
                }
            } else if (gameData->input.isSpriteClicked(playButton, sf::Mouse::Left, gameData->window)) {
                if (!prevMouseState) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.addGameState(GameStateReference(new MainGameState(gameData)), true);
                    prevMouseState = true;
                }
            }else if (gameData->input.isSpriteClicked(tutorialButton, sf::Mouse::Left, gameData->window)) {
                    if (!prevMouseState) {
                        if (gameData->json.getSoundState()) {
                            clickSound.play();
                        }
                        gameData->machine.addGameState(GameStateReference(new TutorialState(gameData)), false);
                        prevMouseState = true;
                    }
            } else {
                prevMouseState = false;
            }
        }
    }
}

void MainMenuState::resume() {
    scaler = MAIN_MENU_FONT_SIZE_SCALER;
    clickSound.setVolume((float)gameData->json.getSoundVolume());
    quote.setString(quoteVector[std::rand() % quoteVector.size()]);
    quote.setPosition(680,110);
    quote.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

void MainMenuState::update() {
    if(fontSize == fontSizeOrigin + 5 * scaler){
        scaler *= -1;
    }
    quote.setCharacterSize(fontSize);
    quote.setOrigin(quote.getGlobalBounds().width/2, quote.getLocalBounds().height/2);
    fontSize += scaler;
}

void MainMenuState::draw() {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(title);
    gameData->window.draw(playButton);
    gameData->window.draw(tutorialButton);
    gameData->window.draw(settingsButton);
    gameData->window.draw(customButton);
    gameData->window.draw(banner);
    gameData->window.draw(quote);
    gameData->window.display();
}
