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
    GameDataReference gameData;
    std::unique_ptr<Wall> wall;
    sf::Sprite background;
    sf::Sprite background2;
    std::unique_ptr<Obstacle_Container> obstaclesContainer;
    std::unique_ptr<Character> character;
    CustomCharacter characterInfo;
    std::unique_ptr<CoinContainer> coinsContainer;
    sf::Text score;
    sf::Text coinText;
    sf::Sound jumpSound;
    sf::Sound pauseSound;
    sf::Sound gameMusicSound;
    sf::Sound coinPickup;
    float backGroundOffsetY = 0;
    float backGroundOffsetY2;
    int acquiredCoins = 0;
    int counter = 0;
    bool jumpSoundPlayed = false;
    bool prevKeystateStart = true;


public:
    MainGameState(GameDataReference gameData);
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
    void resume() override;

};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP