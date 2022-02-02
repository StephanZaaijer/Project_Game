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
    sf::RectangleShape DarkFade;
	sf::Sprite _playButton;
	sf::Sprite _soundsettingsButton;
	sf::Text _pauseText;
	std::vector<sf::Sprite*> clickableButtons = { &_playButton, &_soundsettingsButton};
	sf::Sound _resumeSound;
	sf::Sound clickSound;
    bool prevMousestate=true;
public:
	PauseState(GameDataReference data);
	void init() override;
	void handleInput() override;
	void update(float delta) override;
	void draw(float delta) override;

};

#endif //PROJECT_GAME_PAUSESTATE_HPP
