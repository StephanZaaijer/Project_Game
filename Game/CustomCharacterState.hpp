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
    sf::Sprite _backButton;
    sf::Sprite _arrowRight;
    sf::Sprite _arrowLeft;
    sf::Sprite _background;
    sf::Sprite _randomButton;
    Character *character;
    std::vector<sf::Sprite*> CharacterSelect = { &_arrowRight, &_arrowLeft ,&_backButton,&_randomButton};
    std::vector<CustomCharacter> CustomCharacters = { {"character", CHARACTER_FRAME_1_FILEPATH}, {"character_2", CHARACTER_2}, {"character_3", CHARACTER_3 },{"jasper",JASPER},{"nick",NICK},{"daniel",DANIEL},{"franky",FRANKY},{"stephan",STEPHAN},{"coen",COEN} };
    CustomCharacter CurrentCharacter;
    unsigned int counter;
public:
    CustomCharacterState(GameDataReference data);
    ~CustomCharacterState() override;
    void Init() override;
    void HandleInput() override;
    void Update(float delta) override;
    void Draw(float delta) override;

    std::string ID() override{
        return "Costum character";
    }

};


#endif //PROJECT_GAME_CUSTOMCHARACTERSTATE_H
