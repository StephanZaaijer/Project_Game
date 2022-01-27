#ifndef PROJECT_GAME_DEFINITIONS_HPP
#define PROJECT_GAME_DEFINITIONS_HPP

#include <string>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GAME_TITLE "JUUJUU"
#define FRAMERATE 60
#define CHARACTER_START_HEIGHT 800

enum character_states {
	Still,
	Jumping,
	Stick
};
#define GRAVITY 0.6f
#define VELOCITY_Y (-20.0)
#define VELOCITY_X 8


#define JUMPING_SPEED 200.0f
#define FLYING_SPEED 400.0f
#define JUMP_DURATION 0.75f
#define TEXT_COLOR { 59, 3, 31}

#define TEXT_TITLE_SIZE 200
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

#define RANDOMBUTTON "Assets/randomButton.png"

#define BACKGROUND_PATH "Assets/StartupBackground.png"
#define GAME_TITLE_PATH "Assets/JuuJuuBanner.png"
#define GAME_IMAGE_PATH "Assets/StartUpImage.png"
#define GROEP_6_BANNER_PATH "Assets/Groep6Banner.png"
#define MAIN_MENU_PLAY_BUTTON_PATH "Assets/PlayButton2.png"
#define MAIN_MENU_SETTINGS_BUTTON_PATH "Assets/SettingsButton.png"
#define MAIN_MENU_EXIT_BUTTON_PATH "Assets/ExitButton.png"
#define MAIN_MENU_CUSTOM_BUTTON_PATH "Assets/CustomButton.png"

#define PAUSE_STATE_PLAY_BUTTON_PATH "Assets/PlayButton2.png"
#define PAUSE_STATE_BACKGROUND_PATH "Assets/SoundSettingsBackground.png"
#define PAUSE_STATE_SETTINGS_BUTTON_PATH "Assets/SettingsButton.png"


#define SOUND_SETTINGS_BACKGROUND_PATH "Assets/SoundSettingsBackground.png"
#define SETTINGS_BANNER_PATH "Assets/SettingsBanner.png"
#define MUSIC_BUTTON_GREEN_PATH "Assets/MusicButtonGreen.png"
#define MUSIC_BUTTON_RED_PATH "Assets/MusicButtonRed.png"
#define SOUND_BUTTON_GREEN_PATH "Assets/SoundButtonGreen.png"
#define SOUND_BUTTON_RED_PATH "Assets/SoundButtonRed.png"
#define BACK_BUTTON_PATH "Assets/BackButton.png"

#define ARROW_RIGHT_BUTTON "Assets/ArrowRight.png"
#define ARROW_LEFT_BUTTON "Assets/ArrowLeft.png"

#define RESTART_BUTTON_PATH "Assets/RestartButton.png"
#define MAIN_MENU_BUTTON_PATH "Assets/MainMenuButton.png"

#define BAUHAUS_FONT_PATH "Assets/Bauhaus.ttf"

//#define GAMEOVER_BANNER_PATH "Assets/SettingsBanner.png"

#define GAME_FILE "Assets/Game.json"

#define WALL_COLOR sf::Color::Green
#define WALL_HEIGHT 810
#define WALL_WIDTH 50
#define WALL_OBSTACLE_HEIGHT_1 (WALL_HEIGHT / 6.0f)
#define WALL_OBSTACLE_HEIGHT_2 (WALL_HEIGHT / 2.0f)
#define WALL_OBSTACLE_HEIGHT_3 (WALL_HEIGHT / 6.0f * 5.0f)
#define WALL_SPAWN_DISTANT 200
#define CHARACTER_MAX_HEIGHT 700
#define WALL_SLIDE_DELTA 4 //Higher is slower
#define BACKGROUND_SLIDE 4 //Higher is slower

#define SPIKE_SIZE 75
enum Obstacle_objects {Spike_Object};
enum Spike_facing {left, right};


struct CustomCharacter {
    std::string CharacterName = "";
    std::string CharacterFileName = "";
	bool operator==(const CustomCharacter &rhs) const{
		return (CharacterName == rhs.CharacterName) and (CharacterFileName == rhs.CharacterFileName);
	}
};

#define MUSIC_MAIN_MENU_PATH "Assets/gameMusicMenu.wav"
#define MUSIC_GAME_PATH "Assets/gameMusic.wav"
#define SOUND_CLICK_PATH "Assets/click.wav"
#define SOUND_DEATH_PATH "Assets/death.wav"
#define SOUND_JUMP_PATH "Assets/jump.wav"
#define SOUND_PAUSE_PATH "Assets/pause.wav"
#define SOUND_RESUME_PATH "Assets/resume.wav"


#endif //PROJECT_GAME_DEFINITIONS_HPP