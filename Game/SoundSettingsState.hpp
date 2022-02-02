#ifndef PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
#define PROJECT_GAME_SOUNDSETTINGSSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"
#include "Soundslider.hpp"
#include "Musicslider.hpp"
#include "MainMenuState.hpp"

class SoundSettingsState : public GameState {
private:
    GameDataReference game_data;
  sf::Sprite _background;
  sf::RectangleShape DarkFade;
  sf::Sprite _musicButton;
  sf::Sprite _soundButton;
  sf::Sprite _backButton;
  sf::Text _settingsText;
  std::vector<sf::Sprite*> clickable_buttons = { &_musicButton, &_soundButton, &_backButton };
  std::unique_ptr<Soundslider> soundslider;
  std::unique_ptr<Musicslider> musicslider;
  sf::Sound _clickSound;
  bool prevMousestate = true;

public:
  SoundSettingsState(GameDataReference data);
  void Init() override;
  void HandleInput() override;
  void Update(float delta) override;
  void Draw(float delta) override;

};


#endif // PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
