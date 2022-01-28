#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference data): game_data(std::move(data)) {}

SoundSettingsState::~SoundSettingsState() {
}

void SoundSettingsState::Init() {

    game_data->assets.loadSoundBufferFromFile("_clickSound", SOUND_CLICK_PATH);
    _clickSound.setBuffer(game_data->assets.GetSoundBuffer("_clickSound"));
    _clickSound.setVolume(game_data->json.Get_Soundvolume());

    game_data->assets.loadTextureFromFile("Sound Settings Background", SOUND_SETTINGS_BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("Music Button Green", MUSIC_BUTTON_GREEN_PATH);
    game_data->assets.loadTextureFromFile("Music Button Red", MUSIC_BUTTON_RED_PATH);
    game_data->assets.loadTextureFromFile("Sound Button Green", SOUND_BUTTON_GREEN_PATH);
    game_data->assets.loadTextureFromFile("Sound Button Red", SOUND_BUTTON_RED_PATH);
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
    _settingsText.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);

    game_data->json.Get_Musicstate() ? _musicButton.setTexture(game_data->assets.GetTexture("Music Button Green")) : _musicButton.setTexture(
        game_data->assets.GetTexture("Music Button Red"));

    game_data->json.Get_Soundstate() ? _soundButton.setTexture(game_data->assets.GetTexture("Sound Button Green")) : _soundButton.setTexture(
        game_data->assets.GetTexture("Sound Button Red"));

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
        _musicButton.setTexture(game_data->assets.GetTexture("Music Button Green"));
    }
    else {
        _musicButton.setTexture(game_data->assets.GetTexture("Music Button Red"));
    }
    if (game_data->json.Get_Soundstate()) {
        _soundButton.setTexture(game_data->assets.GetTexture("Sound Button Green"));
    }
    else {
        _soundButton.setTexture(
            game_data->assets.GetTexture("Sound Button Red"));
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