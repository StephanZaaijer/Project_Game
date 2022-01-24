#ifndef PROJECT_GAME_DEFINITIONS_HPP
#define PROJECT_GAME_DEFINITIONS_HPP

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GAME_TITLE "JUUJUU"
#define FRAMERATE 60
#define CHARACTER_FRAME_1_FILEPATH "Assets/character.jpg"


// Change these implementations to enums
#define CHARACTER_STATE_STIL 1
#define CHARACTER_STATE_FALLING 2
#define CHARACTER_STATE_JUMPING 3
#define CHARACTER_START_HEIGHT 800

enum character_states {
	Still,
	Falling,
	Jumping,
	Stick
};


#define GRAVITY 0.5f
#define JUMPING_SPEED 200.0f
#define FLYING_SPEED 400.0f
#define JUMP_DURATION 0.75f

#define TEXT_COLOR { 59, 3, 31}
#define TEXT_TITLE_SIZE 200

#define START_UP_TIME 3
#define BACKGROUND_PATH "Assets/StartupBackground.png"
#define GAME_TITLE_PATH "Assets/JuuJuuBanner.png"
#define GAME_IMAGE_PATH "Assets/StartUpImage.png"
#define GROEP_6_BANNER_PATH "Assets/Groep6Banner.png"
#define MAIN_MENU_PLAY_BUTTON_PATH "Assets/PlayButton2.png"
#define MAIN_MENU_SETTINGS_BUTTON_PATH "Assets/SettingsButton.png"
#define MAIN_MENU_EXIT_BUTTON_PATH "Assets/ExitButton.png"

#define PAUSE_STATE_PLAY_BUTTON_PATH "Assets/PlayButton2.png"
#define PAUSE_STATE_BACKGROUND_PATH "Assets/SoundSettingsBackground.png"

#define SOUND_SETTINGS_BACKGROUND_PATH "Assets/SoundSettingsBackground.png"
#define SETTINGS_BANNER_PATH "Assets/SettingsBanner.png"
#define MUSIC_BUTTON_GREEN_PATH "Assets/MusicButtonGreen.png"
#define MUSIC_BUTTON_RED_PATH "Assets/MusicButtonRed.png"
#define SOUND_BUTTON_GREEN_PATH "Assets/SoundButtonGreen.png"
#define SOUND_BUTTON_RED_PATH "Assets/SoundButtonRed.png"
#define BACK_BUTTON_PATH "Assets/BackButton.png"

#define RESTART_BUTTON_PATH "Assets/RestartButton.png"
#define MAIN_MENU_BUTTON_PATH "Assets/MainMenuButton.png"

#define BAUHAUS_FONT_PATH "Assets/Bauhaus.ttf"

//#define GAMEOVER_BANNER_PATH "Assets/SettingsBanner.png"

#define GAME_FILE "Assets/Game.json"

#define WALL_HEIGHT 600
#define WALL_WIDTH 50
#define WALL_OBSTACLE_HEIGHT_1 WALL_HEIGHT / 6
#define WALL_OBSTACLE_HEIGHT_2 WALL_HEIGHT / 2
#define WALL_OBSTACLE_HEIGHT_3 WALL_HEIGHT / 6 * 5
#define WALL_SPAWN_DISTANT 300
#define CHARACTER_MAX_HEIGHT 500

#define SPIKE_SIZE 50
enum Obstacle_objects {Spike_Object};
enum Spike_facing {left, right};



//#define ENABLE_SOUND
#define ENABLE_FONT

#endif //PROJECT_GAME_DEFINITIONS_HPP