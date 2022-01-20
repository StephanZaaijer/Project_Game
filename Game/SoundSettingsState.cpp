#include "SoundSettingsState.hpp"
#include <utility>

SoundSettingsState::SoundSettingsState(GameDataReference data) : game_data(std::move(data)) {}

void SoundSettingsState::Init() {
  game_data->assets.loadTextureFromFile("Sound Settings Background", "Assets/SoundSettingsBackground.png");
  //Some more assets
  game_data->assets.loadTextureFromFile("Music Button Green", "Assets/MusicButtonGreen.png");

  _background.setTexture(this->game_data->assets.GetTexture("Sound Settings Background"));
  //Set some more textures


  //set all of the positions
}


void SoundSettingsState::HandleInput() {}
void SoundSettingsState::Update(float delta) {}
void SoundSettingsState::Draw(float delta) {}
