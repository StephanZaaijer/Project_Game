#ifndef PROJECT_GAME_STATEMACHINE_HPP
#define PROJECT_GAME_STATEMACHINE_HPP

#include <memory>
#include <stack>
#include "GameState.hpp"

typedef std::unique_ptr<GameState> GameStateReference;

class StateMachine {
private:
    std::stack<GameStateReference> gamestates;
    GameStateReference new_state;
    bool removing;
    bool adding;
    bool replacing;

public:
    void AddGameState( GameStateReference newState, bool isReplacing=true);
    void RemoveGameState();

    void ProcessGameStateChanges();

    GameStateReference &GetActiveGameState();




};


#endif //PROJECT_GAME_STATEMACHINE_HPP
