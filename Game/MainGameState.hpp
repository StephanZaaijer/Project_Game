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
#include "Line.hpp"
#include "CoinContainer.hpp"

class MainGameState : public GameState{
private:
    GameDataReference game_data;
    std::unique_ptr<Wall> wall;
    sf::Sprite background;
    sf::Sprite background2;
    std::unique_ptr<Obstacle_Container> obstacles_container;
    std::unique_ptr<Character> character;
    CustomCharacter characterinfo;
    std::unique_ptr<CoinContainer> coins_container;
    sf::Text _score;
    sf::Text coin_text;
    sf::Sound _jumpSound;
    sf::Sound _pauseSound;
    sf::Sound _gameMusicSound;
    sf::Sound _coinPickup;
    float backGroundOffsetY = 0;
    float backGroundOffsetY2;
    int acquired_coins = 0;
    int counter = 0;
    bool jumpSoundPlayed = false;
    bool prevKeystate_start=true;


public:
    MainGameState(GameDataReference data);
    void Init() override;
    void handleInput() override;
    void Update( float delta ) override;
    void Draw( float delta ) override;
    void Resume() override;

};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP