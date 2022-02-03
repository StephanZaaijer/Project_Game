#ifndef PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
#define PROJECT_GAME_SOUNDSETTINGSSTATE_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Definitions.hpp"
#include "Musicslider.hpp"
#include "Soundslider.hpp"
#include "MainMenuState.hpp"

/// @file SoundSettingsState.hpp
/// @brief
/// Project_Game: This is the SoundSettingsState which is called when the clicks the settingsbutton in the mainmenustate


/// @brief
/// This class is used to create the PauseState and all of its contents
class SoundSettingsState : public GameState {
private:
    GameDataReference gameData;
    sf::Sprite background;
    sf::RectangleShape darkFade;
    sf::Sprite musicButton;
    sf::Sprite soundButton;
    sf::Sprite backButton;
    sf::Text settingsText;
    std::vector<sf::Sprite *> clickableButtons = {&musicButton, &soundButton, &backButton};
    std::unique_ptr<SoundSlider> soundSlider;
    std::unique_ptr<MusicSlider> musicSlider;
    sf::Sound clickSound;
    bool prevMouseState = true;

public:
    ///\brief
    /// This constructor constructs an object of SoundSettingsState
    /// \param gameData
    SoundSettingsState(GameDataReference gameData);

    ///\brief
    /// This function initializes all of the textures and set their positions
    void init() override;

    /// @brief
    /// In this function all of the input from the user is checked and the corresponding actions are taken
    void handleInput() override;

    /// @brief
    /// update function that`s called regularly in the gameloop to update the position of the objects on the screen
    void update() override;

    /// @brief
    /// This function draws all of it's contents onto the screen
    void draw() override;


};


#endif // PROJECT_GAME_SOUNDSETTINGSSTATE_HPP
