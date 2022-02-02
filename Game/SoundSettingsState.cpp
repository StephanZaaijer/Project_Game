#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference data): gameData(std::move(data)) {}


void SoundSettingsState::Init() {
    DarkFade.setSize(sf::Vector2f(gameData->window.getSize()));
    DarkFade.setPosition(0, 0);
    DarkFade.setFillColor(sf::Color(0, 0, 0, 120));

    _clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    _clickSound.setVolume(gameData->json.Get_Soundvolume());
    background.setTexture(gameData->assets.getTexture("Background"));
    backButton.setTexture(gameData->assets.getTexture("Back Button"));
    _musicButton.setTexture(gameData->assets.getTexture("Green Music Button"));
    _soundButton.setTexture(gameData->assets.getTexture("Green Sound Button"));
    _settingsText.setFont(gameData->assets.getFont("Bauhaus"));
    _settingsText.setString("SETTINGS");
    _settingsText.setCharacterSize(TEXT_TITLE_SIZE);
    _settingsText.setFillColor(TEXT_COLOR);

    auto tmpRect = _settingsText.getLocalBounds();
    _settingsText.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);

    gameData->json.Get_Musicstate() ? _musicButton.setTexture(gameData->assets.getTexture("Green Music Button")) : _musicButton.setTexture(
        gameData->assets.getTexture("Red Music Button"));

    gameData->json.Get_Soundstate() ? _soundButton.setTexture(gameData->assets.getTexture("Green Sound Button")) : _soundButton.setTexture(
        gameData->assets.getTexture("Red Sound Button"));

    _settingsText.setPosition(ScreenWidth / 2.0f, SCREEN_HEIGHT / 8.0f);
    backButton.setPosition(ScreenWidth / 2.0f - (backButton.getGlobalBounds().width / 2),
        SCREEN_HEIGHT - (backButton.getGlobalBounds().height * 1.1));


    _musicButton.setOrigin({ _musicButton.getGlobalBounds().width / 2, _musicButton.getGlobalBounds().height / 2 });
    _soundButton.setOrigin({ _soundButton.getGlobalBounds().width / 2, _soundButton.getGlobalBounds().height / 2 });


    _musicButton.setPosition(ScreenWidth / 3.0f * 2.0f, SCREEN_HEIGHT / 3.0f);
    _soundButton.setPosition(ScreenWidth / 3.0f, SCREEN_HEIGHT / 3.0f);

    soundslider = std::unique_ptr<Soundslider>(new Soundslider(gameData, { ScreenWidth / 3.0f, SCREEN_HEIGHT / 2.0f }, 300, false, sf::Color::Green, { 255, 0, 0, 100 }, { ScreenWidth / 3.0f - 125, SCREEN_HEIGHT / 2.0f + 150 }, TEXT_TITLE_SIZE * 0.5));
    musicslider = std::unique_ptr<Musicslider>(new Musicslider(gameData, { ScreenWidth / 3.0f * 2.0f, SCREEN_HEIGHT / 2.0f }, 300, false, sf::Color::Green, { 255, 0, 0, 100 }, { ScreenWidth / 3.0f *2 + 125, SCREEN_HEIGHT / 2.0f + 150 }, TEXT_TITLE_SIZE * 0.5));
}

void SoundSettingsState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
    }
    if (gameData->input.ChangeMouseWhenHoveringOverButton(clickable_buttons, gameData->window)) {
        if(!prevMousestate) {
            if (gameData->input.IsSpriteClicked(backButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                gameData->machine.RemoveGameState();
            } else if (gameData->input.IsSpriteClicked(_musicButton, sf::Mouse::Left, gameData->window)) {
                if (gameData->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                gameData->json.Set_Musicstate(!gameData->json.Get_Musicstate());
            } else if (gameData->input.IsSpriteClicked(_soundButton, sf::Mouse::Left, gameData->window)) {
                if (!gameData->json.Get_Soundstate()) {
                    _clickSound.play();
                }
                gameData->json.Set_Soundstate(!gameData->json.Get_Soundstate());
            }
        }
    }
    prevMousestate = gameData->input.IsButtonPressed(sf::Mouse::Left);
    soundslider->handleInput();
    musicslider->handleInput();
}
void SoundSettingsState::Update(float delta) {
    _clickSound.setVolume(gameData->json.Get_Soundvolume());
    soundslider->update();
    musicslider->update();
    if (gameData->json.Get_Musicstate()) {
        _musicButton.setTexture(gameData->assets.getTexture("Green Music Button"));
    }
    else {
        _musicButton.setTexture(gameData->assets.getTexture("Red Music Button"));
    }
    if (gameData->json.Get_Soundstate()) {
        _soundButton.setTexture(gameData->assets.getTexture("Green Sound Button"));
    }
    else {
        _soundButton.setTexture(
            gameData->assets.getTexture("Red Sound Button"));
    }
}

void SoundSettingsState::Draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(DarkFade);
    soundslider->Draw();
    musicslider->Draw();
    gameData->window.draw(_musicButton);
    gameData->window.draw(_soundButton);
    gameData->window.draw(backButton);
    gameData->window.draw(_settingsText);
    gameData->window.display();
}