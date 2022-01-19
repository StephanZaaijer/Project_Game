//
// Created by stephan on 18-1-2022.
//

#ifndef PROJECT_GAME_GAMESTATE_HPP
#define PROJECT_GAME_GAMESTATE_HPP


class GameState{
public:
    virtual void Init() = 0;

    virtual void HandleInput() = 0;
    virtual void Update( float delta ) = 0;
    virtual void Draw( float delta ) = 0;

    virtual void Pause(){ }
    virtual void Resume(){ }
};


#endif //PROJECT_GAME_GAMESTATE_HPP