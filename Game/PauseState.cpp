#include "PauseState.hpp"
#include <utility>
#include "SoundSettingsState.hpp"

PauseState::PauseState(GameDataReference data):
    game_data(std::move(data))
{}

void PauseState::Init() {
    _resumeSound.setBuffer(game_data->assets.GetSoundBuffer("resumeSound"));
    _resumeSound.setVolume(game_data->json.Get_Soundvolume());

    _clickSound.setBuffer(game_data->assets.GetSoundBuffer("clickSound"));
    _clickSound.setVolume(game_data->json.Get_Soundvolume());

    _background.setTexture(game_data->assets.GetTexture("Background"));
    _playButton.setTexture(game_data->assets.GetTexture("Play Button"));
    _soundsettingsButton.setTexture(game_data->assets.GetTexture("Settings Button"));

    _pauseText.setFont(game_data->assets.GetFont("Bauhaus"));
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

void PauseState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
        if (game_data->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, game_data->window)) {
            if(!prevMousestate) {
                if (game_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _resumeSound.play();
                        while (_resumeSound.getStatus() == _resumeSound.Playing) {}
                    }
                    game_data->machine.RemoveGameState();
                }
                if (game_data->input.IsSpriteClicked(_soundsettingsButton, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    game_data->machine.AddGameState(GameStateReference(new SoundSettingsState(game_data)), false);
                }
            }
        }
    }
    prevMousestate = game_data->input.IsButtonPressed(sf::Mouse::Left);
}

void PauseState::Update(float delta) {
}

void PauseState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_playButton);
    game_data->window.draw(_soundsettingsButton);
    game_data->window.draw(_pauseText);
    game_data->window.display();
}

