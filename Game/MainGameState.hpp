
#ifndef PROJECT_GAME_MAINGAMESTATE_HPP
#define PROJECT_GAME_MAINGAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"
#include "GameState.hpp"
#include "Game.hpp"
#include "Wall.hpp"
#include "ObstaclesContainer.hpp"
#include "Character.hpp"
#include "GameOverState.hpp"

class MainGameState : public GameState{
private:
    int char_height = 0;
    GameDataReference game_data;
    Wall *wall;
    sf::Sprite background;
    Obstacle_Container *obstacles_container;
    Character *character;
    sf::SoundBuffer _jumpSoundBuffer;
    sf::Sound _jumpSound;
    sf::SoundBuffer _deathSoundBuffer;
    sf::Sound _deathSound;
    sf::SoundBuffer _pauseSoundBuffer;
    sf::Sound _pauseSound;
    sf::SoundBuffer _gameMusicSoundBuffer;
    sf::Sound _gameMusicSound;
public:
    MainGameState(GameDataReference data);
    void Init() override;
    bool CollisionDetection(sf::FloatRect &object1, sf::FloatRect &object2);
    bool CollisionDetection(sf::FloatRect object1, sf::FloatRect object2);

    void HandleInput() override;
    void Update( float delta ) override;
    void Draw( float delta ) override;
    void Resume();
};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP