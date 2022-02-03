#include "PauseState.hpp"
#include <utility>
#include "SoundSettingsState.hpp"

PauseState::PauseState(GameDataReference gameData, MainGameState* mainGameState):
    gameData(std::move(gameData)),
    mainGameState(mainGameState)
{}

void PauseState::init() {
    darkFade.setSize(sf::Vector2f(gameData->window.getSize()));
    darkFade.setPosition(0, 0);
    darkFade.setFillColor(sf::Color(0, 0, 0, 120));

    resumeSound.setBuffer(gameData->assets.getSoundBuffer("resumeSound"));
    resumeSound.setVolume(gameData->json.getSoundVolume());

    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    clickSound.setVolume(gameData->json.getSoundVolume());

    playButton.setTexture(gameData->assets.getTexture("Play Button"));
    soundSettingsButton.setTexture(gameData->assets.getTexture("Settings Button"));

    pauseText.setFont(gameData->assets.getFont("Bauhaus"));
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(TEXT_TITLE_SIZE);
    pauseText.setFillColor(TEXT_COLOR);

    auto tmpRect = pauseText.getLocalBounds();
    pauseText.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);

    playButton.setOrigin({ playButton.getGlobalBounds().width / 2, playButton.getGlobalBounds().height / 2 });
    soundSettingsButton.setOrigin({ soundSettingsButton.getGlobalBounds().width / 2, soundSettingsButton.getGlobalBounds().height / 2 });

    playButton.setPosition({ (SCREEN_WIDTH / 2.0f), (SCREEN_HEIGHT / 20.0f * 10.0f) });
    soundSettingsButton.setPosition({ (SCREEN_WIDTH / 2.0f), (SCREEN_HEIGHT / 20.0f * 15.0f) });

    pauseText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 8.0f);

}

void PauseState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if(!prevMouseState) {
                if (gameData->input.isSpriteClicked(playButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        resumeSound.play();
                        while (resumeSound.getStatus() == resumeSound.Playing) {}
                    }
                    gameData->machine.removeGameState();
                }
                if (gameData->input.isSpriteClicked(soundSettingsButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.addGameState(GameStateReference(new SoundSettingsState(gameData)), false);
                }
            }
        }
    }
    prevMouseState = gameData->input.isButtonPressed(sf::Mouse::Left);
}

void PauseState::draw() {
    mainGameState->drawNoDisplay();
    gameData->window.draw(darkFade);
    gameData->window.draw(playButton);
    gameData->window.draw(soundSettingsButton);
    gameData->window.draw(pauseText);
    gameData->window.display();
}

