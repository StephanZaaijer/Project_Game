//
// Created by Franky on 19-1-2022.
//

#ifndef PROJECT_GAME_MAINGAMESTATE_HPP
#define PROJECT_GAME_MAINGAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "GameState.hpp"
#include "Game.hpp"
#include "Wall.hpp"
#include "ObstaclesContainer.hpp"

class MainGameState : public GameState{
private:
    GameDataReference game_data;
    Wall *wall;
    sf::Sprite background;
    Obstacle_Container *obstacles_container;

public:
    MainGameState(GameDataReference data);
    void Init();

    void HandleInput();
    void Update( float delta );
    void Draw( float delta );
};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP