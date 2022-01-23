//
// Created by stephan on 18-1-2022.
//

#ifndef PROJECT_GAME_DEFINITIONS_HPP
#define PROJECT_GAME_DEFINITIONS_HPP

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GAME_TITLE "Platformer groep 6"
#define FRAMERATE 60

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
//#define ENABLE_FONT

#endif //PROJECT_GAME_DEFINITIONS_HPP