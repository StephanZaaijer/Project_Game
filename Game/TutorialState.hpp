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
    sf::Sound _clickSound;

    std::vector<sf::Sprite*> clickableButtons = { &backButton};
    bool prevMousestate;

public:
    TutorialState(GameDataReference data);
    void Init() override;
    void handleInput() override;
    void Update( float delta ) override;
    void Draw( float delta ) override;
};


#endif //PROJECT_GAME_TUTORIALSTATE_HPP
