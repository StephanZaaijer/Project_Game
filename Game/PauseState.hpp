#ifndef PROJECT_GAME_PAUSESTATE_HPP
#define PROJECT_GAME_PAUSESTATE_HPP

#include "GameState.hpp"
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"

class PauseState : public GameState {
private:
	GameDataReference gameData;
	sf::Sprite background;
    sf::RectangleShape darkFade;
	sf::Sprite playButton;
	sf::Sprite soundSettingsButton;
	sf::Text pauseText;
	std::vector<sf::Sprite*> clickableButtons = { &playButton, &soundSettingsButton};
	sf::Sound resumeSound;
	sf::Sound clickSound;
    bool prevMouseState = true;
public:
	PauseState(GameDataReference gameData);
	void init() override;
	void handleInput() override;
	void update() override;
	void draw() override;

};

#endif //PROJECT_GAME_PAUSESTATE_HPP
