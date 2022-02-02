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
    GameOverState(GameDataReference gameData);
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;


};

#endif //PROJECT_GAME_GAMEOVERSTATE_HPP