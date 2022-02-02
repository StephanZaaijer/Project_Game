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
    sf::Sprite _title;
    sf::Sprite _banner;
    sf::Sprite _playButton;
    sf::Sprite _settingsButton;
    sf::Sprite _customButton;
    sf::Sprite _tutorialButton;

    sf::Sound clickSound;

    std::vector<sf::Sprite*> clickableButtons = { &_playButton, &_settingsButton, &_customButton, &_tutorialButton };
    std::vector<std::string> quoteVector;
    float scaler = MAIN_MENU_FONT_SIZE_SCALER;
    float fontSize = MAIN_MENU_FONT_SIZE;
    float fontSizeOrigin = MAIN_MENU_FONT_SIZE;

    sf::Text _quote;

    bool prevMousestate = false;

public:
    MainMenuState(GameDataReference gameData);

    void init() override;

    void handleInput() override;

    void update(float delta) override;

    void draw(float delta) override;

    void resume() override;

};

#endif //PROJECT_GAME_MAINMENUSTATE_HPP
