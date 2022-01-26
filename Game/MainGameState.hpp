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
    GameDataReference game_data;
    Wall *wall;
    sf::Sprite background;
    sf::Sprite background2;
    Obstacle_Container *obstacles_container;
    Character *character;
    CustomCharacter characterinfo;

    sf::Sound _jumpSound;
    sf::Sound _pauseSound;
    sf::Sound _gameMusicSound;
    float backGroundOffsetY = 0;
    float backGroundOffsetY2;

public:
    MainGameState(GameDataReference data);
    ~MainGameState() override;
    void Init() override;

    void HandleInput() override;
    void Update( float delta ) override;
    void Draw( float delta ) override;
    void Resume() override;
};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP