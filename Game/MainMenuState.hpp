#ifndef PROJECT_GAME_MAINMENUSTATE_HPP
#define PROJECT_GAME_MAINMENUSTATE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"
#include <vector>

class MainMenuState : public GameState {
private:
    GameDataReference gameData;
    sf::Sprite background;
    sf::Sprite title;
    sf::Sprite banner;
    sf::Sprite playButton;
    sf::Sprite settingsButton;
    sf::Sprite customButton;
    sf::Sprite tutorialButton;

    sf::Sound clickSound;

    std::vector<sf::Sprite*> clickableButtons = { &playButton, &settingsButton, &customButton, &tutorialButton };
    std::vector<std::string> quoteVector;
    float scaler = MAIN_MENU_FONT_SIZE_SCALER;
    float fontSize = MAIN_MENU_FONT_SIZE;
    float fontSizeOrigin = MAIN_MENU_FONT_SIZE;

    sf::Text quote;

    bool prevMouseState = false;

public:
    MainMenuState(GameDataReference gameData);

    void init() override;

    void handleInput() override;

    void update() override;

    void draw() override;

    void resume() override;

};

#endif //PROJECT_GAME_MAINMENUSTATE_HPP
