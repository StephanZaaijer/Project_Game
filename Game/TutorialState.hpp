#ifndef PROJECT_GAME_TUTORIALSTATE_HPP
#define PROJECT_GAME_TUTORIALSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"
#include "Character.hpp"

/// @file TutorialState.hpp
/// @brief
/// Project_Game: TutorialState to explain game controls

/// @brief
/// This class is used to create the TutorialState and all of its contents
class TutorialState : public GameState {
private:
    GameDataReference gameData;
    sf::Sprite tutorial;
    sf::Sprite backButton;
    sf::Sprite background;
    sf::Sound clickSound;

    std::vector<sf::Sprite *> clickableButtons = {&backButton};
    bool prevMouseState;

public:
    ///\brief
    /// This constructor constructs an object of TutorialState
    /// \param gameData GameDataReference to communicate with the assetmanager etc.
    TutorialState(GameDataReference gameData);

    /// @brief
    /// init function that`s called first time when state is active in the statemachine
    void init() override;

    /// @brief
    /// handleInput function that`s called regularly in the gameloop to handle userinput
    void handleInput() override;

    ///@brief
    /// draw function that`s called once every loop to draw the object on the screen
    void draw() override;
};


#endif //PROJECT_GAME_TUTORIALSTATE_HPP
