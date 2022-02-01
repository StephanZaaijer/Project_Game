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
    sf::Sprite _arrowRightCharacter;
    sf::Sprite _arrowLeftCharacter;
    sf::Sprite _arrowRightTheme;
    sf::Sprite _arrowLeftTheme;
    sf::Sprite _background;
    sf::Sprite _randomButtonCharacter;
    sf::Sprite _randomButtonTheme;
    sf::Sprite _theme;
    sf::Sprite _buyEquipButton;
    sf::Sprite _equipButtonTheme;
    sf::Sprite _characterImg;

    std::unique_ptr<Character> character;
    std::vector<sf::Sprite*> ClickableButtons = { &_arrowRightCharacter, &_arrowLeftCharacter ,&_backButton,&_randomButtonCharacter, &_randomButtonTheme, &_arrowLeftTheme, &_arrowRightTheme, &_buyEquipButton, &_equipButtonTheme};
    std::vector<CustomCharacter> CustomCharacters = { {"character", CHARACTER_FRAME_1_FILEPATH}, {"character_2", CHARACTER_2}, {"character_3", CHARACTER_3 },{"jasper",JASPER},{"nick",NICK},{"daniel",DANIEL},{"franky",FRANKY},{"stephan",STEPHAN},{"coen",COEN} };
    std::vector<CustomTheme> CustomThemes = {{sf::Color::Black, sf::Color::Red, "black_red_theme" ,BLACK_RED_THEME_PATH}, {sf::Color::Green, sf::Color::Blue, "green_blue_theme", GREEN_BLUE_THEME_PATH}, {sf::Color::Yellow,sf::Color::Black, "yellow_black_theme", YELLOW_BLACK_THEME_PATH },{sf::Color::Cyan,sf::Color::Blue, "cyan_blue_theme", CYAN_BLUE_THEME_PATH }};
    CustomCharacter CurrentCharacter;
    CustomTheme CurrentTheme;
    sf::Sound _clickSound;
    sf::Sound _customClickSound;
    sf::Text _coins_text;

    std::vector<bool> skin_bought;

    int coins;
    int counter_Characters;
    int counter_Theme;
    bool prevMousestate;

public:
    CustomCharacterState(GameDataReference data);
    void Init() override;
    void HandleInput() override;
    void Update(float delta) override;
    void Draw(float delta) override;
};


#endif //PROJECT_GAME_CUSTOMCHARACTERSTATE_H
