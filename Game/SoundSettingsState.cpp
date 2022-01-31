#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference data): game_data(std::move(data)) {}


void SoundSettingsState::Init() {
    _clickSound.setBuffer(game_data->assets.GetSoundBuffer("clickSound"));
    _clickSound.setVolume(game_data->json.Get_Soundvolume());
    _background.setTexture(game_data->assets.GetTexture("Background"));
    _backButton.setTexture(game_data->assets.GetTexture("Back Button"));
    _musicButton.setTexture(game_data->assets.GetTexture("Green Music Button"));
    _soundButton.setTexture(game_data->assets.GetTexture("Green Sound Button"));
    _settingsText.setFont(game_data->assets.GetFont("Bauhaus"));
    _settingsText.setString("SETTINGS");
    _settingsText.setCharacterSize(TEXT_TITLE_SIZE);
    _settingsText.setFillColor(TEXT_COLOR);

    auto tmpRect = _settingsText.getLocalBounds();
    _settingsText.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);

    game_data->json.Get_Musicstate() ? _musicButton.setTexture(game_data->assets.GetTexture("Green Music Button")) : _musicButton.setTexture(
        game_data->assets.GetTexture("Red Music Button"));

    game_data->json.Get_Soundstate() ? _soundButton.setTexture(game_data->assets.GetTexture("Green Sound Button")) : _soundButton.setTexture(
        game_data->assets.GetTexture("Red Sound Button"));

    _settingsText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 8.0f);
    _backButton.setPosition(SCREEN_WIDTH / 2.0f - (_backButton.getGlobalBounds().width / 2),
        SCREEN_HEIGHT - (_backButton.getGlobalBounds().height * 1.1));


    _musicButton.setOrigin({ _musicButton.getGlobalBounds().width / 2, _musicButton.getGlobalBounds().height / 2 });
    _soundButton.setOrigin({ _soundButton.getGlobalBounds().width / 2, _soundButton.getGlobalBounds().height / 2 });


    _musicButton.setPosition(SCREEN_WIDTH / 3.0f * 2.0f, SCREEN_HEIGHT / 3.0f);
    _soundButton.setPosition(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f);

    soundslider = std::unique_ptr<Soundslider>(new Soundslider(game_data, { SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f }, 300, false, sf::Color::Green, { 255, 0, 0, 100 }, { SCREEN_WIDTH / 3.0f - 125, SCREEN_HEIGHT / 2.0f + 150 }, TEXT_TITLE_SIZE * 0.5));
    musicslider = std::unique_ptr<Musicslider>(new Musicslider(game_data, { SCREEN_WIDTH / 3.0f * 2.0f, SCREEN_HEIGHT / 2.0f }, 300, false, sf::Color::Green, { 255, 0, 0, 100 }, { SCREEN_WIDTH / 3.0f *2 + 125, SCREEN_HEIGHT / 2.0f + 150 }, TEXT_TITLE_SIZE * 0.5));
}

void SoundSettingsState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
    }
    if (game_data->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, game_data->window)) {
        if(!prevMousestate) {
            if (game_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, game_data->window)) {
                if (game_data->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                game_data->machine.RemoveGameState();
            } else if (game_data->input.IsSpriteClicked(_musicButton, sf::Mouse::Left, game_data->window)) {
                if (game_data->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                game_data->json.Set_Musicstate(!game_data->json.Get_Musicstate());
            } else if (game_data->input.IsSpriteClicked(_soundButton, sf::Mouse::Left, game_data->window)) {
                if (!game_data->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                game_data->json.Set_Soundstate(!game_data->json.Get_Soundstate());
            }
        }
    }
    prevMousestate = game_data->input.IsButtonPressed(sf::Mouse::Left);
    soundslider->handleinput();
    musicslider->handleinput();
}
void SoundSettingsState::Update(float delta) {
    _clickSound.setVolume(game_data->json.Get_Soundvolume());
    soundslider->update();
    musicslider->update();
    if (game_data->json.Get_Musicstate()) {
        _musicButton.setTexture(game_data->assets.GetTexture("Green Music Button"));
    }
    else {
        _musicButton.setTexture(game_data->assets.GetTexture("Red Music Button"));
    }
    if (game_data->json.Get_Soundstate()) {
        _soundButton.setTexture(game_data->assets.GetTexture("Green Sound Button"));
    }
    else {
        _soundButton.setTexture(
            game_data->assets.GetTexture("Red Sound Button"));
    }
}

void SoundSettingsState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    soundslider->Draw();
    musicslider->Draw();
    game_data->window.draw(_musicButton);
    game_data->window.draw(_soundButton);
    game_data->window.draw(_backButton);
    game_data->window.draw(_settingsText);
    game_data->window.display();
}