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
    GameDataReference game_data;
    sf::Sprite _background;
    sf::Sprite _title;
    sf::Sprite _banner;
    sf::Sprite _playButton;
    sf::Sprite _settingsButton;
    sf::Sprite _customButton;
    sf::Sprite _tutorialButton;

    sf::Sound _clickSound;

    std::vector<sf::Sprite*> clickable_buttons = { &_playButton, &_settingsButton, &_customButton, &_tutorialButton };
    std::vector<std::string> quoteVector {QUOTE_1, QUOTE_2, QUOTE_3, QUOTE_4, QUOTE_5, QUOTE_6, QUOTE_7, QUOTE_8, QUOTE_9, QUOTE_10, QUOTE_11, QUOTE_12, QUOTE_13, QUOTE_14, QUOTE_15, QUOTE_16, QUOTE_17, QUOTE_18, QUOTE_19};

    float scaler = MAIN_MENU_FONT_SIZE_SCALER;
    float fontSize = MAIN_MENU_FONT_SIZE;
    float fontSizeOrigin = MAIN_MENU_FONT_SIZE;

    sf::Text _quote;

    bool prevMousestate = false;

public:
    MainMenuState(GameDataReference data);

    void Init() override;

    void HandleInput() override;

    void Update(float delta) override;

    void Draw(float delta) override;

    void Resume() override;

};

#endif //PROJECT_GAME_MAINMENUSTATE_HPP
