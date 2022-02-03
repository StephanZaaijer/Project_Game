#ifndef PROJECT_GAME_GAMEOVERSTATE_HPP
#define PROJECT_GAME_GAMEOVERSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Character.hpp"

/// @file
/// @brief
/// Project_Game: This is the GameOVerState in which you will end up if your character dies.

/// @brief
/// This class is used to create the GameOverState and all of its contents
class GameOverState : public GameState {
private:
    GameDataReference gameData;
    sf::Sprite background;
    sf::Sprite restartButton;
    sf::Sprite mainMenuButton;

    sf::Text gameOverText;
    sf::Text score;
    sf::Text highscore;

    sf::Sound deathSound;
    sf::Sound clickSound;

    std::vector<sf::Sprite*> clickableButtons = { &restartButton, &mainMenuButton };
    bool prevButtonState=true;
    bool prevKeyState=true;
public:

    /// @brief
    /// This constructor constructs an object of GameOverState
    /// \param data The game_data of a state, which contains the StateMachine, window, AssetManager, InputManager and JsonManager.
    GameOverState(GameDataReference gameData);

    /// @brief
    /// This function initializes all of the sounds, volumes, textures, fonts, texts, colors, and positions are set.
    void init() override;

    /// @brief
    /// In this function all of the input from the user is checked and the corresponding actions are taken.
    void handleInput() override;

    /// @brief
    /// This function draws all of it's contents onto the screen.
    void draw() override;


};

#endif //PROJECT_GAME_GAMEOVERSTATE_HPP