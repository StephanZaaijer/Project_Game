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

/// @file
/// @brief
/// Project_Game: This is the PauseState which is called when the user pauses the game


/// @brief
/// This class is used to create the PauseState and all of its contents
class PauseState : public GameState {
private:
	GameDataReference gameData;
    MainGameState* mainGameState;
    sf::RectangleShape darkFade;
	sf::Sprite playButton;
	sf::Sprite soundSettingsButton;
	sf::Text pauseText;
	std::vector<sf::Sprite*> clickableButtons = { &playButton, &soundSettingsButton};
	sf::Sound resumeSound;
	sf::Sound clickSound;
    bool prevMouseState = true;
public:
    ///\brief
    /// This constructor constructs an object of PauseState
    /// \param gameData
	PauseState(GameDataReference gameData, MainGameState* mainGameState);
	void init() override;
	void handleInput() override;
	void draw() override;

};

#endif //PROJECT_GAME_PAUSESTATE_HPP
