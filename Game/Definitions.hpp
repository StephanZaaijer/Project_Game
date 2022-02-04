#ifndef PROJECT_GAME_DEFINITIONS_HPP
#define PROJECT_GAME_DEFINITIONS_HPP

#include <string>
#include <SFML/Graphics.hpp>

/// @file Definitions.hpp
/// @brief
/// Project_Game: This file contains all macro's, and several enum's and structs used for sharing data through the program.

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GAME_TITLE "JUUJUU"
#define FRAMERATE 60
#define CHARACTER_START_HEIGHT 800
#define CHARACTER_SCALE 0.75
#define JUMP_ANIMATION_DOWNSIZE 0.02 // the amount of decrease in radius of the jumping effect.
#define PARTICLE_OPACITY 100 // 0-255 where 0 is invisible.

/// @brief
/// This enum list contains the character_states in which the character can be in.
enum character_states {
    Still,
    Jumping,
    Stick
};

#define GRAVITY 0.6f
#define VELOCITY_Y (-20.0)
#define VELOCITY_X 8.5

#define TEXT_COLOR { 59, 3, 31}

#define TEXT_TITLE_SIZE 200
#define GAME_OVER_SCORE_TEXT_SIZE 120

#define SKIN_PRICE 100
#define CHARACTER_FRAME_1_FILEPATH "Assets/character.jpg"
#define CHARACTER_2 "Assets/character_2.png"
#define CHARACTER_3 "Assets/character_3.png"
#define JASPER "Assets/jasper.png"
#define NICK "Assets/nick.png"
#define DANIEL "Assets/daniel.jpg"
#define COEN "Assets/coen.jpg"
#define FRANKY "Assets/franky.png"
#define STEPHAN "Assets/stephan.png"


#define TUTORIAL "Assets/Tutorial.png"
#define BACKGROUND_GROUND_PATH "Assets/BackgroundGround.png"
#define BACKGROUND_PATH "Assets/Background.png"
#define BACKGROUND_NO_CLOUDS_PATH "Assets/BackgroundNoClouds.png"
#define BACKGROUND_SKY_TO_SPACE_PATH "Assets/SkyToSpaceBackground.png"
#define SPACE_BACKGROUND_PATH "Assets/SpaceBackground.png"
#define SPACE_BACKGROUND_SPAGHETTI_MONSTER_PATH "Assets/SpaceBackgroundSpaghettiMonster.png"
#define GAME_TITLE_PATH "Assets/JuuJuuBanner.png"
#define GAME_IMAGE_PATH "Assets/StartUpImage.png"
#define GROEP_6_BANNER_PATH "Assets/Groep6Banner.png"
#define PLAY_BUTTON_PATH "Assets/PlayButton.png"
#define SETTINGS_BUTTON_PATH "Assets/SettingsButton.png"
#define CUSTOMIZE_BUTTON_PATH "Assets/CustomButton.png"
#define RANDOM_BUTTON "Assets/randomButton.png"
#define BUY_BUTTON_PATH "Assets/BuyButton.png"
#define EQUIP_BUTTON_PATH "Assets/EquipButton.png"

#define CONTROLS_BUTTON_PATH "Assets/ControlsButton.png"

#define MUSIC_BUTTON_GREEN_PATH "Assets/MusicButtonGreen.png"
#define MUSIC_BUTTON_RED_PATH "Assets/MusicButtonRed.png"
#define SOUND_BUTTON_GREEN_PATH "Assets/SoundButtonGreen.png"
#define SOUND_BUTTON_RED_PATH "Assets/SoundButtonRed.png"
#define BACK_BUTTON_PATH "Assets/BackButton.png"

#define ARROW_RIGHT_BUTTON "Assets/ArrowRight.png"
#define ARROW_LEFT_BUTTON "Assets/ArrowLeft.png"

#define COIN_PATH "Assets/Coin.png"
#define COIN_SCALE 0.25

#define RESTART_BUTTON_PATH "Assets/RestartButton.png"
#define MAIN_MENU_BUTTON_PATH "Assets/MainMenuButton.png"

#define BAUHAUS_FONT_PATH "Assets/Bauhaus.ttf"
#define BIT_FONT_PATH "Assets/8-bit.ttf"

#define GAME_FILE "Assets/Game.json"

#define WALL_HEIGHT 750
#define WALL_HEIGHT 750
#define WALL_WIDTH 50
#define BORDER_WALL_2_START (SCREEN_WIDTH / 6.0f * 5.0f)
#define BORDER_WALL_WIDTH (SCREEN_WIDTH / 6.0f)

#define WALL_OBSTACLE_HEIGHT_1 (WALL_HEIGHT / 6.0f)
#define WALL_OBSTACLE_HEIGHT_2 (WALL_HEIGHT / 2.0f)
#define WALL_OBSTACLE_HEIGHT_3 (WALL_HEIGHT / 6.0f * 5.0f)
#define WALL_SPAWN_DISTANT 250
#define CHARACTER_MAX_HEIGHT 700
#define WALL_SLIDE_DELTA 4 //Higher is slower
#define BACKGROUND_SLIDE 2 //Higher is slower

#define SPIKE_SIZE 125

#define MAIN_MENU_FONT_SIZE 60
#define MAIN_MENU_FONT_SIZE_SCALER 1

/// @brief
/// This enum spikeFacing list is used to define which way an obstacle is facing
enum spikeFacing {
    left, right, neither
};

/// @brief
/// This enum identifier list is used to identify an obstacle as a spike or deathwall.
enum identifier {
    spike, deathwall
};

/// @brief
/// This CustomCharacter struct is used to store character-sprite information.
/// @details
/// This struct contains the character name and filename.
struct CustomCharacter {
    std::string characterName;
    std::string characterFileName;

    /// @brief
    /// This operator== is used to check if the a CustomCharacter is equal to another CustomCharacter.
    /// This is done by checking their name and filename is.
    bool operator==(const CustomCharacter &rhs) const {
        return (characterName == rhs.characterName) and (characterFileName == rhs.characterFileName);
    }
};

/// @brief
/// This CustomTheme struct is used to store information for the game theme.
/// @details
/// This struct contains the wallColor, objectColor, themeName and themeFileName.
/// This is used to initialize the colors of all game elements.
struct CustomTheme {
    sf::Color wallColor;
    sf::Color objectColor;
    std::string themeName;
    std::string themeFileName;

    /// @brief
    /// This operator== is used to determine if the a given theme is equal to another theme.
    /// This is done by comparing their names and filenames
    bool operator==(const CustomTheme &rhs) const {
        return (themeName == rhs.themeName) and (themeFileName == rhs.themeFileName);
    }
};

#define BLACK_RED_THEME_PATH "Assets/black_red.png"
#define GREEN_BLUE_THEME_PATH "Assets/green_blue.png"
#define CYAN_BLUE_THEME_PATH "Assets/cyan_blue.png"
#define YELLOW_BLACK_THEME_PATH "Assets/yellow_black.png"

#define SOUND_CLICK_PATH "Assets/click.wav"
#define SOUND_CLICK_CUSTOM_PATH "Assets/clickCustom.wav"
#define SOUND_COIN_PICKUP_PATH "Assets/coin.wav"
#define SOUND_DEATH_PATH "Assets/Death.wav"
#define SOUND_JUMP_PATH "Assets/jump.wav"
#define SOUND_PAUSE_PATH "Assets/pause.wav"
#define SOUND_RESUME_PATH "Assets/resume.wav"
#define MUSIC_GAME_STATE1_PATH "Assets/gameMusicState1.wav"
#define MUSIC_GAME_STATE2_PATH "Assets/gameMusicState2.wav"
#define MUSIC_GAME_STATE3_PATH "Assets/gameMusicState3.wav"
#define MUSIC_GAME_STATE4_PATH "Assets/gameMusicState4.wav"
#define MUSIC_GAME_STATE5_PATH "Assets/gameMusicState5.wav"


#endif //PROJECT_GAME_DEFINITIONS_HPP