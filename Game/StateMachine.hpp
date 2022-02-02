#ifndef PROJECT_GAME_STATEMACHINE_HPP
#define PROJECT_GAME_STATEMACHINE_HPP

#include <memory>
#include "GameState.hpp"
#include <stack>

typedef std::unique_ptr<GameState> GameStateReference;

class StateMachine {
private:
    std::stack<GameStateReference> gameStates;
    GameStateReference newState;
    bool removing;
    bool adding;
    bool replacing;

public:
    void addGameState( GameStateReference newState, bool isReplacing = true);
    void removeGameState();

    void processGameStateChanges();

    GameStateReference &getActiveGameState();
};


#endif //PROJECT_GAME_STATEMACHINE_HPP
