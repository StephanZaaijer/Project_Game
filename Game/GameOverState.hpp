#ifndef PROJECT_GAME_GAMEOVERSTATE_HPP
#define PROJECT_GAME_GAMEOVERSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"

class GameOverState : public GameState {
private:
    GameDataReference game_data;
    sf::Sprite _background;
    sf::Sprite _restartButton;
    sf::Sprite _mainMenuButton;

    sf::Text _gameOverText;
    sf::Text _score;
    sf::Text _highscore;

    sf::SoundBuffer _clickBuffer;
    sf::Sound _clickSound;

    std::vector<sf::Sprite*> clickable_buttons = { &_restartButton, &_mainMenuButton };

public:
    GameOverState(GameDataReference data);

    void Init();
    void HandleInput();
    void Update(float delta);
    void Draw(float delta);
};

#endif //PROJECT_GAME_GAMEOVERSTATE_HPP