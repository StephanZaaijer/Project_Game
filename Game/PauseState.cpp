#include "PauseState.hpp"
#include <utility>
#include "SoundSettingsState.hpp"

PauseState::PauseState(GameDataReference data):
    gameData(std::move(data))
{}

void PauseState::Init() {
    DarkFade.setSize(sf::Vector2f(gameData->window.getSize()));
    DarkFade.setPosition(0, 0);
    DarkFade.setFillColor(sf::Color(0, 0, 0, 120));

    _resumeSound.setBuffer(gameData->assets.getSoundBuffer("resumeSound"));
    _resumeSound.setVolume(gameData->json.Get_Soundvolume());

    _clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    _clickSound.setVolume(gameData->json.Get_Soundvolume());

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

    _playButton.setPosition({ (ScreenWidth / 2.0f), (SCREEN_HEIGHT / 20.0f * 10.0f) });
    _soundsettingsButton.setPosition({ (ScreenWidth / 2.0f), (SCREEN_HEIGHT / 20.0f * 15.0f) });

    _pauseText.setPosition(ScreenWidth / 2.0f, SCREEN_HEIGHT / 8.0f);

}

void PauseState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        if (gameData->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, gameData->window)) {
            if(!prevMousestate) {
                if (gameData->input.IsSpriteClicked(_playButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.Get_Soundstate()) {
                        _resumeSound.play();
                        while (_resumeSound.getStatus() == _resumeSound.Playing) {}
                    }
                    gameData->machine.RemoveGameState();
                }
                if (gameData->input.IsSpriteClicked(_soundsettingsButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    gameData->machine.AddGameState(GameStateReference(new SoundSettingsState(gameData)), false);
                }
            }
        }
    }
    prevMousestate = gameData->input.IsButtonPressed(sf::Mouse::Left);
}

void PauseState::Update(float delta) {
}

void PauseState::Draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(DarkFade);
    gameData->window.draw(_playButton);
    gameData->window.draw(_soundsettingsButton);
    gameData->window.draw(_pauseText);
    gameData->window.display();
}

