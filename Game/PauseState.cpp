#include "PauseState.hpp"
#include <utility>
#include "SoundSettingsState.hpp"

PauseState::PauseState(GameDataReference gameData):
    gameData(std::move(gameData))
{}

void PauseState::init() {
    DarkFade.setSize(sf::Vector2f(gameData->window.getSize()));
    DarkFade.setPosition(0, 0);
    DarkFade.setFillColor(sf::Color(0, 0, 0, 120));

    _resumeSound.setBuffer(gameData->assets.getSoundBuffer("resumeSound"));
    _resumeSound.setVolume(gameData->json.getSoundVolume());

    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    clickSound.setVolume(gameData->json.getSoundVolume());

    background.setTexture(gameData->assets.getTexture("Background"));
    _playButton.setTexture(gameData->assets.getTexture("Play Button"));
    _soundsettingsButton.setTexture(gameData->assets.getTexture("Settings Button"));

    _pauseText.setFont(gameData->assets.getFont("Bauhaus"));
    _pauseText.setString("PAUSED");
    _pauseText.setCharacterSize(TEXT_TITLE_SIZE);
    _pauseText.setFillColor(TEXT_COLOR);

    auto tmpRect = _pauseText.getLocalBounds();
    _pauseText.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);

    _playButton.setOrigin({ _playButton.getGlobalBounds().width / 2, _playButton.getGlobalBounds().height / 2 });
    _soundsettingsButton.setOrigin({ _soundsettingsButton.getGlobalBounds().width / 2, _soundsettingsButton.getGlobalBounds().height / 2 });

    _playButton.setPosition({ (SCREEN_WIDTH / 2.0f), (SCREEN_HEIGHT / 20.0f * 10.0f) });
    _soundsettingsButton.setPosition({ (SCREEN_WIDTH / 2.0f), (SCREEN_HEIGHT / 20.0f * 15.0f) });

    _pauseText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 8.0f);

}

void PauseState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if(!prevMousestate) {
                if (gameData->input.isSpriteClicked(_playButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        _resumeSound.play();
                        while (_resumeSound.getStatus() == _resumeSound.Playing) {}
                    }
                    gameData->machine.RemoveGameState();
                }
                if (gameData->input.isSpriteClicked(_soundsettingsButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.AddGameState(GameStateReference(new SoundSettingsState(gameData)), false);
                }
            }
        }
    }
    prevMousestate = gameData->input.isButtonPressed(sf::Mouse::Left);
}

void PauseState::update(float delta) {
}

void PauseState::draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(DarkFade);
    gameData->window.draw(_playButton);
    gameData->window.draw(_soundsettingsButton);
    gameData->window.draw(_pauseText);
    gameData->window.display();
}

