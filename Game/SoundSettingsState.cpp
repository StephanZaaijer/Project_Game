#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference data): game_data(std::move(data)) {}

void SoundSettingsState::Init() {
    game_data->assets.loadTextureFromFile("Sound Settings Background",SOUND_SETTINGS_BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("Music Button Green",MUSIC_BUTTON_GREEN_PATH);
    game_data->assets.loadTextureFromFile("Music Button Red",MUSIC_BUTTON_RED_PATH);
    game_data->assets.loadTextureFromFile("Sound Button Green",SOUND_BUTTON_GREEN_PATH);
    game_data->assets.loadTextureFromFile("Sound Button Red",SOUND_BUTTON_RED_PATH);
    game_data->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);

    _background.setTexture(game_data->assets.GetTexture("Sound Settings Background"));
    _backButton.setTexture(game_data->assets.GetTexture("Back Button"));
    _musicButton.setTexture(game_data->assets.GetTexture("Music Button Green"));
    _soundButton.setTexture(game_data->assets.GetTexture("Sound Button Green"));

    _settingsText.setFont(game_data->assets.GetFont("Bauhaus font"));
    _settingsText.setString("SETTINGS");
    _settingsText.setCharacterSize(TEXT_TITLE_SIZE);
    _settingsText.setFillColor(TEXT_COLOR);
    auto tmpRect = _settingsText.getLocalBounds();
    _settingsText.setOrigin(tmpRect.left + tmpRect.width/2,
                            tmpRect.top  + tmpRect.height/2);

    game_data->json.Get_Musicstate() ? _musicButton.setTexture(game_data->assets.GetTexture("Music Button Green")) : _musicButton.setTexture(
            game_data->assets.GetTexture("Music Button Red"));

    game_data->json.Get_Soundstate() ? _soundButton.setTexture(game_data->assets.GetTexture("Sound Button Green")): _soundButton.setTexture(
            game_data->assets.GetTexture("Sound Button Red"));

    _settingsText.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 8.0f);
    _backButton.setPosition(SCREEN_WIDTH / 2.0f - (_backButton.getGlobalBounds().width / 2),
                            SCREEN_HEIGHT - (_backButton.getGlobalBounds().height * 1.1));

    _musicButton.setPosition(SCREEN_WIDTH / 2.0f - (_musicButton.getGlobalBounds().width / 2),
                            SCREEN_HEIGHT - (_musicButton.getGlobalBounds().height * 2.1));

    _soundButton.setPosition(SCREEN_WIDTH / 2.0f - (_soundButton.getGlobalBounds().width / 2),
                            SCREEN_HEIGHT - (_soundButton.getGlobalBounds().height * 3.1));

}

void SoundSettingsState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
        if (game_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, game_data->window)) {
            game_data->machine.RemoveGameState();
        }
        if (game_data->input.IsSpriteClicked(_musicButton, sf::Mouse::Left, game_data->window)) {
            // TODO actually turn off music
            if (game_data->json.Get_Musicstate()) {
                _musicButton.setTexture(game_data->assets.GetTexture("Music Button Red"));
                game_data->json.Set_Musicstate(false);
            }
            else {
                _musicButton.setTexture(game_data->assets.GetTexture("Music Button Green"));
                game_data->json.Set_Musicstate(true);
            }
        }
        if (game_data->input.IsSpriteClicked(_soundButton, sf::Mouse::Left, game_data->window)) {
            // TODO actually turn off sound
            if (game_data->json.Get_Soundstate()) {
                _soundButton.setTexture(game_data->assets.GetTexture("Sound Button Red"));
                game_data->json.Set_Soundstate(false);
            }
            else {
                _soundButton.setTexture(
                    game_data->assets.GetTexture("Sound Button Green"));
                game_data->json.Set_Soundstate(true);
            }
        }
    }
    game_data->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, game_data->window);
}

void SoundSettingsState::Update(float delta) {
}

void SoundSettingsState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_musicButton);
    game_data->window.draw(_soundButton);
    game_data->window.draw(_backButton);
    game_data->window.draw(_settingsText);
    game_data->window.display();
}
