#include "StateMachine.hpp"
#include <iostream>

void StateMachine::AddGameState(GameStateReference newState, bool isReplacing) {
    std::cout << "AddGameState newstate = " << newState->ID() << " isReplacing = " << isReplacing << '\n';
    adding = true;
    replacing = isReplacing;
    new_state = std::move(newState);
}

void StateMachine::RemoveGameState() {
    std::cout << "RemoveGameState" << '\n';

    removing = true;
}

void StateMachine::ProcessGameStateChanges() {
    if (removing and !gamestates.empty()) {
        gamestates.pop();
        gamestatestring.pop_back();
        if (!gamestates.empty()) {
            gamestates.top()->Resume();
        }
        removing = false;
    }
    if (adding){
        if(!gamestates.empty()){
            if(replacing){
                gamestates.pop();
                gamestatestring.pop_back();
            }
            else{
                gamestates.top()->Pause();
            }
        }
        gamestates.push(std::move(new_state));
        gamestatestring.push_back(gamestates.top()->ID());
        gamestates.top()->Init();
        adding=false;
    }
}

GameStateReference &StateMachine::GetActiveGameState() {
    return gamestates.top();
}

int StateMachine::GetLenGamestates(){
    return gamestates.size();
}

const std::vector<std::string>& StateMachine::Get_Gamestatenames(){
    return gamestatestring;
}