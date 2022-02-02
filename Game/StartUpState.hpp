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
    GameDataReference gameData;
    sf::Clock _clock;
    sf::Sprite background;
    sf::Sprite _logo;
    sf::Sprite _title;
    sf::Sprite _banner;

public:
    ///\brief StartUpState constructor
    /// \param gameData
    StartUpState(GameDataReference gameData);

    ///\brief init() function
    void init() override;

    ///\brief handleInput() function
    void handleInput() override;

    ///\brief update function
    /// \param delta
    void update(float delta) override;

    ///\brief draw() function
    /// \param delta
    void draw(float delta) override;

};

#endif //PROJECT_GAME_STARTUPSTATE_HPP