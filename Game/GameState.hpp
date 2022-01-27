#ifndef PROJECT_GAME_GAMESTATE_HPP
#define PROJECT_GAME_GAMESTATE_HPP

#include <string>

class GameState{
public:
    virtual void Init() = 0;

    virtual void HandleInput() = 0;
    virtual void Update( float delta ) = 0;
    virtual void Draw( float delta ) = 0;

    virtual void Pause(){ }
    virtual void Resume(){ }
    
    virtual ~GameState(){};

    virtual std::string ID(){
        return "Unimplemented for this state";
    }
};


#endif //PROJECT_GAME_GAMESTATE_HPP
