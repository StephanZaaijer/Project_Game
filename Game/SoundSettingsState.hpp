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


public:
  SoundSettingsState(GameDataReference data);

  void Init();
  void HandleInput();
  void Update(float delta);
  void Draw(float delta);
};


#endif // PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
