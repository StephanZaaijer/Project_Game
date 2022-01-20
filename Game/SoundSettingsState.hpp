#ifndef PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
#define PROJECT_GAME_SOUNDSETTINGSSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"

class SoundSettingsState : public GameState {
private:
  GameDataReference game_data;
  sf::Sprite _background;
  sf::Sprite _musicButton;
  sf::Sprite _soundButton;
  sf::Sprite _backButton;
  sf::Sprite _settingsText;
  bool music = true; //TODO Change this to music/ sound class, and settings file?
  bool sound = true; //TODO keep changes when pressed on back


public:
  SoundSettingsState(GameDataReference data);

  void Init() override;
  void HandleInput() override;
  void Update(float delta) override;
  void Draw(float delta) override;
};


#endif // PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
