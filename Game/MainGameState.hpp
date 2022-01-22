#ifndef PROJECT_GAME_MAINGAMESTATE_HPP
#define PROJECT_GAME_MAINGAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Game.hpp"
#include "Wall.hpp"
#include "Character.hpp"
#include "GameOverState.hpp"

class MainGameState : public GameState{
private:
    GameDataReference game_data;
    Wall *wall;
    Character *character;
public:
    MainGameState(GameDataReference data);
    void Init() override;

    void HandleInput() override;
    void Update( float delta ) override;
    void Draw( float delta ) override;
};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP