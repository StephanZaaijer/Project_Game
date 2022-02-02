#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference gameData) : gameData(std::move(gameData)) {}

void SoundSettingsState::init() {
    darkFade.setSize(sf::Vector2f(gameData->window.getSize()));
    darkFade.setPosition(0, 0);
    darkFade.setFillColor(sf::Color(0, 0, 0, 120));

    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    clickSound.setVolume(gameData->json.getSoundVolume());
    background.setTexture(gameData->assets.getTexture("Background"));
    backButton.setTexture(gameData->assets.getTexture("Back Button"));
    musicButton.setTexture(gameData->assets.getTexture("Green music Button"));
    soundButton.setTexture(gameData->assets.getTexture("Green Sound Button"));
    settingsText.setFont(gameData->assets.getFont("Bauhaus"));
    settingsText.setString("SETTINGS");
    settingsText.setCharacterSize(TEXT_TITLE_SIZE);
    settingsText.setFillColor(TEXT_COLOR);

    auto tmpRect = settingsText.getLocalBounds();
    settingsText.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);

    gameData->json.getMusicState() ? musicButton.setTexture(gameData->assets.getTexture("Green music Button")) : musicButton.setTexture(
        gameData->assets.getTexture("Red music Button"));

    gameData->json.getSoundState() ? soundButton.setTexture(gameData->assets.getTexture("Green Sound Button")) : soundButton.setTexture(
        gameData->assets.getTexture("Red Sound Button"));

    settingsText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 8.0f);
    backButton.setPosition(SCREEN_WIDTH / 2.0f - (backButton.getGlobalBounds().width / 2),
        SCREEN_HEIGHT - (backButton.getGlobalBounds().height * 1.1));


    musicButton.setOrigin({ musicButton.getGlobalBounds().width / 2, musicButton.getGlobalBounds().height / 2 });
    soundButton.setOrigin({ soundButton.getGlobalBounds().width / 2, soundButton.getGlobalBounds().height / 2 });


    musicButton.setPosition(SCREEN_WIDTH / 3.0f * 2.0f, SCREEN_HEIGHT / 3.0f);
    soundButton.setPosition(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f);

    musicSlider = std::unique_ptr<MusicSlider>(new MusicSlider(gameData, { SCREEN_WIDTH / 3.0f * 2.0f, SCREEN_HEIGHT / 2.0f }, 300, false, sf::Color::Green, { 255, 0, 0, 100 }, { SCREEN_WIDTH / 3.0f *2 + 125, SCREEN_HEIGHT / 2.0f + 150 }, TEXT_TITLE_SIZE * 0.5));
    soundSlider = std::unique_ptr<SoundSlider>(new SoundSlider(gameData, { SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f }, 300, false, sf::Color::Green, { 255, 0, 0, 100 }, { SCREEN_WIDTH / 3.0f - 125, SCREEN_HEIGHT / 2.0f + 150 }, TEXT_TITLE_SIZE * 0.5));
}

void SoundSettingsState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
    }
    if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
        if(!prevMouseState) {
            if (gameData->input.isSpriteClicked(backButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.getSoundState()) {
                    clickSound.play();
                }
                gameData->machine.removeGameState();
            } else if (gameData->input.isSpriteClicked(musicButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.getSoundState()) {
                    clickSound.play();
                }
                gameData->json.setMusicState(!gameData->json.getMusicState());
            } else if (gameData->input.isSpriteClicked(soundButton, sf::Mouse::Left, gameData->window)) {
                if (!gameData->json.getSoundState()) {
                    clickSound.play();
                }
                gameData->json.setSoundState(!gameData->json.getSoundState());
            }
        }
    }
    prevMouseState = gameData->input.isButtonPressed(sf::Mouse::Left);
    soundSlider->handleInput();
    musicSlider->handleInput();
}


void SoundSettingsState::update() {
    clickSound.setVolume(gameData->json.getSoundVolume());
    soundSlider->update();
    musicSlider->update();
    if (gameData->json.getMusicState()) {
        musicButton.setTexture(gameData->assets.getTexture("Green music Button"));
    }
    else {
        musicButton.setTexture(gameData->assets.getTexture("Red music Button"));
    }
    if (gameData->json.getSoundState()) {
        soundButton.setTexture(gameData->assets.getTexture("Green Sound Button"));
    }
    else {
        soundButton.setTexture(
            gameData->assets.getTexture("Red Sound Button"));
    }
}

void SoundSettingsState::draw() {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(darkFade);
    soundSlider->draw();
    musicSlider->draw();
    gameData->window.draw(musicButton);
    gameData->window.draw(soundButton);
    gameData->window.draw(backButton);
    gameData->window.draw(settingsText);
    gameData->window.display();
}