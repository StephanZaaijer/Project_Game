//
// Created by coenc on 20/01/2022.
//

#ifndef PROJECT_GAME_MAINMENUSTATE_HPP
#define PROJECT_GAME_MAINMENUSTATE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"
#include "MainMenuState.hpp"



class MainMenuState : public GameState {
private:
    GameDataReference game_data;
    sf::Clock _clock;
    sf::Sprite _background;
    sf::Sprite _title;
    sf::Sprite _banner;
    sf::Sprite _playButton;
    sf::Sprite _settingsButton;
    sf::Sprite _exitButton;

public:
    MainMenuState(GameDataReference data);

    void Init();
    void HandleInput();
    void Update(float delta);
    void Draw(float delta);
};

#endif //PROJECT_GAME_MAINMENUSTATE_HPP
