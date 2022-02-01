#ifndef PROJECT_GAME_STARTUPSTATE_HPP
#define PROJECT_GAME_STARTUPSTATE_HPP

///@file

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

///\class StartUpState ///\public GameState
class StartUpState : public GameState {
private:
    GameDataReference game_data;
    sf::Clock _clock;
    sf::Sprite _background;
    sf::Sprite _logo;
    sf::Sprite _title;
    sf::Sprite _banner;

public:
    ///\brief StartUpState constructor
    /// \param data
    StartUpState(GameDataReference data);

    ///\brief Init() function
    void Init() override;

    ///\brief HandleInput() function
    void HandleInput() override;

    ///\brief Update function
    /// \param delta
    void Update(float delta) override;

    ///\brief Draw() function
    /// \param delta
    void Draw(float delta) override;

};

#endif //PROJECT_GAME_STARTUPSTATE_HPP