//
// Created by stephan on 18-1-2022.
//

#include "StateMachine.hpp"

void StateMachine::AddGameState(GameStateReference newState, bool isReplacing) {
    adding = true;
    replacing = isReplacing;
    new_state = std::move(newState);
}

void StateMachine::RemoveGameState() {
    removing = true;
}

void StateMachine::ProcessGameStateChanges() {
    if (removing and !gamestates.empty()) {
        gamestates.pop();
        if (!gamestates.empty()) {
            gamestates.top()->Resume();
        }
        removing = false;
    }
    if (adding){
        if(!gamestates.empty()){
            if(replacing){
                gamestates.pop();
            }
            else{
                gamestates.top()->Pause();
            }
        }
        gamestates.push(std::move(new_state));
        gamestates.top()->Init();
        adding=false;
    }
}

GameStateReference &StateMachine::GetActiveGameState() {
    return gamestates.top();
}