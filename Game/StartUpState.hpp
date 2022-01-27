#ifndef PROJECT_GAME_STARTUPSTATE_HPP
#define PROJECT_GAME_STARTUPSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "CustomCharacterState.hpp"

class StartUpState : public GameState {
private:
    GameDataReference game_data;
    sf::Clock _clock;
    sf::Sprite _background;
    sf::Sprite _logo;
    sf::Sprite _title;
    sf::Sprite _banner;

public:
    StartUpState(GameDataReference data);

    void Init() override;
    void HandleInput() override;
    void Update(float delta) override;
    void Draw(float delta) override;

    std::string ID() override{
        return "Startup";
    }
};

#endif //PROJECT_GAME_STARTUPSTATE_HPP