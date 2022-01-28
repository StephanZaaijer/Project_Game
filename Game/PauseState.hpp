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
	GameDataReference game_data;
	sf::Sprite _background;
	sf::Sprite _playButton;
	sf::Sprite _soundsettingsButton;
	sf::Text _pauseText;
	std::vector<sf::Sprite*> clickable_buttons = { &_playButton, &_soundsettingsButton};
	sf::Sound _resumeSound;
	sf::Sound _clickSound;


public:
	PauseState(GameDataReference data);
	void Init() override;
	void HandleInput() override;
	void Update(float delta) override;
	void Draw(float delta) override;

};

#endif //PROJECT_GAME_PAUSESTATE_HPP
