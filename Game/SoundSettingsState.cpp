#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference data) : game_data(std::move(data)) {}

void SoundSettingsState::Init() {
  game_data->assets.loadTextureFromFile("Sound Settings Background", "Assets/SoundSettingsBackground.png");
  game_data->assets.loadTextureFromFile("Music Button Green", "Assets/MusicButtonGreen.png");
  game_data->assets.loadTextureFromFile("Music Button Red", "Assets/MusicButtonRed.png");
  game_data->assets.loadTextureFromFile("Sound Button Green", "Assets/SoundButtonGreen.png");
  game_data->assets.loadTextureFromFile("Sound Button Red", "Assets/SoundButtonRed.png");
  game_data->assets.loadTextureFromFile("Back Button", "Assets/BackButton.png");
  game_data->assets.loadTextureFromFile("Settings Banner", "Assets/SettingsBanner.png");

  _background.setTexture(this->game_data->assets.GetTexture("Sound Settings Background"));
  _backButton.setTexture(this->game_data->assets.GetTexture("Back Button"));
  _musicButton.setTexture(this->game_data->assets.GetTexture("Music Button Green"));
  _soundButton.setTexture(this->game_data->assets.GetTexture("Sound Button Green"));
  _settingsText.setTexture(this->game_data->assets.GetTexture("Settings Banner"));

  //set all of the positions
  _backButton.setPosition(SCREEN_WIDTH/2 - (_backButton.getGlobalBounds().width / 2) , SCREEN_HEIGHT - (_backButton.getGlobalBounds().height*1.1)); //TODO times ?? for good placement
  _musicButton.setPosition(SCREEN_WIDTH/2 - (_musicButton.getGlobalBounds().width / 2) , SCREEN_HEIGHT - (_musicButton.getGlobalBounds().height*2.1));
  _soundButton.setPosition(SCREEN_WIDTH/2 - (_soundButton.getGlobalBounds().width / 2) , SCREEN_HEIGHT - (_soundButton.getGlobalBounds().height*3.1));
  _settingsText.setPosition(SCREEN_WIDTH/2 - (_settingsText.getGlobalBounds().width / 2) , SCREEN_HEIGHT - (_settingsText.getGlobalBounds().height*4.2));
}

void SoundSettingsState::HandleInput() {
  sf::Event event;
  while (game_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      game_data->window.close();
    }
  }
}

void SoundSettingsState::Update(float delta) {}

void SoundSettingsState::Draw(float delta) {
  game_data->window.clear();
  game_data->window.draw(_background);
  game_data->window.draw(_musicButton);
  game_data->window.draw(_soundButton);
  game_data->window.draw(_backButton);
  game_data->window.draw(_settingsText);
  game_data->window.display();
}
