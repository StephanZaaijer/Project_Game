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
    GameDataReference gameData;
    sf::Sprite backButton;
    sf::Sprite arrowRightCharacter;
    sf::Sprite arrowLeftCharacter;
    sf::Sprite arrowRightTheme;
    sf::Sprite arrowLeftTheme;
    sf::Sprite background;
    sf::Sprite randomButtonCharacter;
    sf::Sprite randomButtonTheme;
    sf::Sprite theme;
    sf::Sprite buyEquipButton;
    sf::Sprite equipButtonTheme;

    sf::Text equippedCharacter;
    sf::Text equippedTheme;

    std::unique_ptr<Character> character;
    CustomCharacter currentCharacter;
    CustomTheme currentTheme;
    sf::Sound clickSound;
    sf::Sound customClickSound;
    sf::Text coinsText;
    std::vector<bool> skinBought;

    int coins;
    int counterCharacters;
    int counterTheme;
    bool prevMouseState;

    std::vector<CustomTheme> customThemes = {{sf::Color::Black, sf::Color::Red, "black_red_theme" ,BLACK_RED_THEME_PATH},
                                             {sf::Color::Green, sf::Color::Blue, "green_blue_theme", GREEN_BLUE_THEME_PATH},
                                             {sf::Color::Yellow,sf::Color::Black, "yellow_black_theme", YELLOW_BLACK_THEME_PATH },
                                             {sf::Color::Cyan,sf::Color::Blue, "cyan_blue_theme", CYAN_BLUE_THEME_PATH }};

    std::vector<sf::Sprite*> clickableButtons = { &arrowRightCharacter, &arrowLeftCharacter,
                                                  &backButton,&randomButtonCharacter,
                                                  &randomButtonTheme, &arrowLeftTheme,
                                                  &arrowRightTheme, &buyEquipButton,
                                                  &equipButtonTheme};

    std::vector<CustomCharacter> customCharacters = { {"character", CHARACTER_FRAME_1_FILEPATH},
                                                      {"character_2", CHARACTER_2},
                                                      {"character_3", CHARACTER_3 },
                                                      {"jasper",JASPER},
                                                      {"nick",NICK},
                                                      {"daniel",DANIEL},
                                                      {"franky",FRANKY},
                                                      {"stephan",STEPHAN},
                                                      {"coen",COEN} };
public:
    CustomCharacterState(GameDataReference gameData);
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
};


#endif //PROJECT_GAME_CUSTOMCHARACTERSTATE_H
