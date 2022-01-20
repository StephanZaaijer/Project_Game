#ifndef PROJECT_GAME_MAINGAMESTATE_HPP
#define PROJECT_GAME_MAINGAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Game.hpp"

class MainGameState : public GameState{
private:
    GameDataReference game_data;

public:
    MainGameState(GameDataReference data);
    void init();

    void HandleInput();
    void Update( float delta );
    void Draw( float delta );
};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP