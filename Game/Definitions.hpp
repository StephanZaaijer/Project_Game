#ifndef PROJECT_GAME_DEFINITIONS_HPP
#define PROJECT_GAME_DEFINITIONS_HPP

#include <string>
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GAME_TITLE "JUUJUU"
#define FRAMERATE 60
#define CHARACTER_START_HEIGHT 800
#define CHARACTER_SCALE 0.75
#define JSON_WRITEOUT_TIME 5.0
enum character_states {
	Still,
	Jumping,
	Stick
};
#define GRAVITY 0.6f
#define VELOCITY_Y (-20.0)
#define VELOCITY_X 8

#define TEXT_COLOR { 59, 3, 31}

#define TEXT_TITLE_SIZE 200
#define GAME_OVER_SCORE_TEXT_SIZE 120
#define START_UP_TIME 0.4

#define CHARACTER_FRAME_1_FILEPATH "Assets/character.jpg"
#define CHARACTER_2 "Assets/character_2.png"
#define CHARACTER_3 "Assets/character_3.png"
#define JASPER "Assets/jasper.png"
#define NICK "Assets/nick.png"
#define DANIEL "Assets/daniel.jpg"
#define COEN "Assets/coen.jpg"
#define FRANKY "Assets/franky.png"
#define STEPHAN "Assets/stephan.png"

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

#define GAME_FILE "Assets/Game.json"

#define WALL_HEIGHT 750
#define WALL_HEIGHT 750
#define WALL_WIDTH 50
#define WALL_OBSTACLE_HEIGHT_1 (WALL_HEIGHT / 6.0f)
#define WALL_OBSTACLE_HEIGHT_2 (WALL_HEIGHT / 2.0f)
#define WALL_OBSTACLE_HEIGHT_3 (WALL_HEIGHT / 6.0f * 5.0f)
#define WALL_SPAWN_DISTANT 200
#define CHARACTER_MAX_HEIGHT 700
#define WALL_SLIDE_DELTA 4 //Higher is slower
#define BACKGROUND_SLIDE 2 //Higher is slower

#define SPIKE_SIZE 75
enum Obstacle_objects {Spike_Object};
enum Spike_facing {left, right};


struct CustomCharacter {
    std::string CharacterName;
    std::string CharacterFileName;
	bool operator==(const CustomCharacter &rhs) const{
		return (CharacterName == rhs.CharacterName) and (CharacterFileName == rhs.CharacterFileName);
	}
};

struct CustomTheme{
    sf::Color wall_color;
    sf::Color object_color;
    std::string themeName;
    std::string themeFileName;
    bool operator==(const CustomTheme &rhs) const{
        return (themeName == rhs.themeName) and (themeFileName == rhs.themeFileName);
    }
};

#define BLACK_RED_THEME_PATH "Assets/black_red.png"
#define GREEN_BLUE_THEME_PATH "Assets/green_blue.png"
#define CYAN_BLUE_THEME_PATH "Assets/cyan_blue.png"
#define YELLOW_BLACK_THEME_PATH "Assets/yellow_black.png"

#define MUSIC_GAME_PATH "Assets/gameMusic.wav"
#define SOUND_CLICK_PATH "Assets/click.wav"
#define SOUND_CLICK_CUSTOM_PATH "Assets/clickCustom.wav"
#define SOUND_DEATH_PATH "Assets/death.wav"
#define SOUND_JUMP_PATH "Assets/jump.wav"
#define SOUND_PAUSE_PATH "Assets/pause.wav"
#define SOUND_RESUME_PATH "Assets/resume.wav"


#endif //PROJECT_GAME_DEFINITIONS_HPP