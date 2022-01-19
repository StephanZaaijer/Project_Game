//
// Created by coenc on 18/01/2022.
//

#ifndef PROJECT_GAME_STARTUPSTATE_HPP
#define PROJECT_GAME_STARTUPSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"



class StartUpState : public GameState {
private:
    GameDataReference game_data;
    sf::Clock _clock;
    sf::Texture _backgroundTexture;
    sf::Sprite _background;

public:
    StartUpState(GameDataReference data);

    void Init();
    void HandleInput();
    void Update(float delta);
    void Draw(float delta);
};

#endif //PROJECT_GAME_STARTUPSTATE_HPP