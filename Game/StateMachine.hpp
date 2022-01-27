#ifndef PROJECT_GAME_STATEMACHINE_HPP
#define PROJECT_GAME_STATEMACHINE_HPP

#include <memory>
#include <stack>
#include "GameState.hpp"
#include <vector>

typedef std::unique_ptr<GameState> GameStateReference;

class StateMachine {
private:
    std::stack<GameStateReference> gamestates;
    std::vector<std::string> gamestatestring = {};
    GameStateReference new_state;
    bool removing;
    bool adding;
    bool replacing;

public:
    void AddGameState( GameStateReference newState, bool isReplacing=true);
    void RemoveGameState();

    void ProcessGameStateChanges();

    GameStateReference &GetActiveGameState();

    int GetLenGamestates();

    const std::vector<std::string>& Get_Gamestatenames();
};


#endif //PROJECT_GAME_STATEMACHINE_HPP
