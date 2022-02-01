#ifndef PROJECT_GAME_MAINMENUSTATE_HPP
#define PROJECT_GAME_MAINMENUSTATE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"
#include <vector>

class MainMenuState : public GameState {
private:
    GameDataReference game_data;
    sf::Sprite _background;
    sf::Sprite _title;
    sf::Sprite _banner;
    sf::Sprite _playButton;
    sf::Sprite _settingsButton;
    sf::Sprite _customButton;
    sf::Sprite _tutorialButton;

    sf::Sound _clickSound;

    std::vector<sf::Sprite*> clickable_buttons = { &_playButton, &_settingsButton, &_customButton, &_tutorialButton };
    bool prevMousestate = false;

public:
    MainMenuState(GameDataReference data);

    void Init() override;

    void HandleInput() override;

    void Update(float delta) override;

    void Draw(float delta) override;

    void Resume() override;

};

#endif //PROJECT_GAME_MAINMENUSTATE_HPP
