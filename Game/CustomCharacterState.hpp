#ifndef PROJECT_GAME_CUSTOMCHARACTERSTATE_H
#define PROJECT_GAME_CUSTOMCHARACTERSTATE_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"
#include "Character.hpp"

class CustomCharacterState: public GameState {
private:
    GameDataReference game_data;
    sf::Sprite _ArrowRight;
    sf::Sprite _ArrowLeft;
    sf::Sprite _background;
    Character *character;
    std::vector<sf::Sprite*> CharacterSelect = { &_ArrowRight, &_ArrowLeft };

public:
    CustomCharacterState(GameDataReference data);

    void Init() override;
    void HandleInput() override;
    void Update(float delta) override;
    void Draw(float delta) override;
};


#endif //PROJECT_GAME_CUSTOMCHARACTERSTATE_H
