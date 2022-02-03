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

/// @file MainMenuState.hpp
/// @brief
/// Project_Game: This is the MainMenuState which is the state you will see after the StartUpState


/// @brief
/// This class is used to create the MainMenuState and all of its contents
class MainMenuState : public GameState {
private:
    GameDataReference gameData;
    sf::Sprite background;
    sf::Sprite title;
    sf::Sprite banner;
    sf::Sprite playButton;
    sf::Sprite settingsButton;
    sf::Sprite customButton;
    sf::Sprite tutorialButton;

    sf::Sound clickSound;

    std::vector<sf::Sprite *> clickableButtons = {&playButton, &settingsButton, &customButton, &tutorialButton};
    std::vector<std::string> quoteVector;
    float scaler = MAIN_MENU_FONT_SIZE_SCALER;
    float fontSize = MAIN_MENU_FONT_SIZE;
    float fontSizeOrigin = MAIN_MENU_FONT_SIZE;

    sf::Text quote;


    bool prevMousestate = true;


public:
    ///\brief
    /// This constructor constructs an object of GameOverState
    /// \param gameData
    MainMenuState(GameDataReference gameData);

    ///\brief
    /// This function initializes all of the sounds, textures and set their positions
    void init() override;

    /// @brief
    /// In this function all of the input from the user is checked and the corresponding actions are taken
    void handleInput() override;

    /// @brief
    /// This function Checks if the time elapsed is greater then the START_UP_TIME macro and switches states
    void update() override;

    /// @brief
    /// This function draws all of it's contents onto the screen
    void draw() override;

    /// @brief
    /// This function makes necessary changes to variables when this state is recalled.
    void resume() override;

};

#endif //PROJECT_GAME_MAINMENUSTATE_HPP
