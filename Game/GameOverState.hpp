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

class GameOverState : public GameState {
private:
    GameDataReference game_data;
    sf::Sprite _background;
    sf::Sprite _restartButton;
    sf::Sprite _mainMenuButton;

    sf::Text _gameOverText;
    sf::Text _score;
    sf::Text _highscore;

    sf::Sound _deathSound;
    sf::Sound _clickSound;

    std::vector<sf::Sprite*> clickable_buttons = { &_restartButton, &_mainMenuButton };

public:
    GameOverState(GameDataReference data);
    ~GameOverState() override = default;
    void Init() override;
    void HandleInput() override;
    void Update(float delta) override;
    void Draw(float delta) override;


};

#endif //PROJECT_GAME_GAMEOVERSTATE_HPP