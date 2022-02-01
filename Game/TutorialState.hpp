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
    GameDataReference game_data;
    sf::Sprite tutorial;
    sf::Sprite _backButton;
    sf::Sprite _background;
    sf::Sound _clickSound;

    std::vector<sf::Sprite*> ClickableButtons = { &_backButton};
    bool prevMousestate;

public:
    TutorialState(GameDataReference data);
    void Init() override;
    void HandleInput() override;
    void Update( float delta ) override;
    void Draw( float delta ) override;
};


#endif //PROJECT_GAME_TUTORIALSTATE_HPP