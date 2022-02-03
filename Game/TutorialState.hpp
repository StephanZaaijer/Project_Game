#ifndef PROJECT_GAME_TUTORIALSTATE_HPP
#define PROJECT_GAME_TUTORIALSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"
#include "Character.hpp"

class TutorialState:public GameState {
private:
    GameDataReference gameData;
    sf::Sprite tutorial;
    sf::Sprite backButton;
    sf::Sprite background;
    sf::Sound clickSound;

    std::vector<sf::Sprite*> clickableButtons = { &backButton};
    bool prevMouseState;

public:
    TutorialState(GameDataReference gameData);
    void init() override;
    void handleInput() override;
    void draw() override;
};


#endif //PROJECT_GAME_TUTORIALSTATE_HPP
