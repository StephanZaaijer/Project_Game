#ifndef PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
#define PROJECT_GAME_SOUNDSETTINGSSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"
#include "Musicslider.hpp"
#include "Soundslider.hpp"
#include "MainMenuState.hpp"

class SoundSettingsState : public GameState {
private:
  GameDataReference gameData;
  sf::Sprite background;
  sf::RectangleShape darkFade;
  sf::Sprite musicButton;
  sf::Sprite soundButton;
  sf::Sprite backButton;
  sf::Text settingsText;
  std::vector<sf::Sprite*> clickableButtons = { &musicButton, &soundButton, &backButton };
  std::unique_ptr<SoundSlider> soundSlider;
  std::unique_ptr<MusicSlider> musicSlider;
  sf::Sound clickSound;
  bool prevMouseState = true;

public:
  SoundSettingsState(GameDataReference gameData);
  void init() override;
  void handleInput() override;
  void update() override;
  void draw() override;

};


#endif // PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
