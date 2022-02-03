#ifndef PROJECT_GAME_PAUSESTATE_HPP
#define PROJECT_GAME_PAUSESTATE_HPP

#include "GameState.hpp"
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "MainGameState.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"

/// @file PauseState.hpp
/// @brief
/// Project_Game: This is the PauseState which is called when the user pauses the game


/// @brief
/// This class is used to create the PauseState and all of its contents
class PauseState : public GameState {
private:
    GameDataReference gameData;
    MainGameState *mainGameState;
    sf::RectangleShape darkFade;
    sf::Sprite playButton;
    sf::Sprite soundSettingsButton;
    sf::Text pauseText;
    std::vector<sf::Sprite *> clickableButtons = {&playButton, &soundSettingsButton};
    sf::Sound resumeSound;
    sf::Sound clickSound;
    bool prevMouseState = true;
public:
    /// @brief
    /// This constructor constructs an object of PauseState
    /// \param gameData GameDataReference to communicate with the assetmanager etc.
    /// \param mainGameState pointer to the MainGameState so that it's draw function can be called
    PauseState(GameDataReference gameData, MainGameState *mainGameState);

    /// @brief
    /// init function that`s called first time when state is active in the statemachine
    void init() override;

    /// @brief
    /// handleInput function that`s called regularly in the gameloop to handle userinput
    void handleInput() override;

    /// @brief
    /// draw function that`s called once every loop to draw the object on the screen
    void draw() override;

};

#endif //PROJECT_GAME_PAUSESTATE_HPP
