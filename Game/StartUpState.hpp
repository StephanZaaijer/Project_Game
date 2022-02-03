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

/// @brief
/// Project_Game: This is the StartUpState which is the first state you will see if the program has started


/// @brief
/// This class is used to create the StartUpState and all of its contents
class StartUpState : public GameState {
private:
    GameDataReference gameData;
    sf::Clock clock;
    sf::Sprite background;
    sf::Sprite logo;
    sf::Sprite title;
    sf::Sprite banner;

public:
    ///\brief
    /// This constructor constructs an object of GameOverState
    /// \param gameData
    StartUpState(GameDataReference gameData);

    ///\brief
    /// This function initializes all of the textures and set their positions
    void init() override;

    /// @brief
    /// In this function all of the input from the user is checked and the corresponding actions are taken
    void handleInput() override;

    /// @brief
    /// This function switches to the MainMenuState.
    void update() override;

    /// @brief
    /// This function draws all of it's contents onto the screen
    void draw() override;

};

#endif //PROJECT_GAME_STARTUPSTATE_HPP