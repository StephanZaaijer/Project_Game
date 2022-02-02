#ifndef PROJECT_GAME_GAMESTATE_HPP
#define PROJECT_GAME_GAMESTATE_HPP

/// @file GameState.hpp
/// @brief
/// Project_Game: virtual state class that`s used as a template for all GameStates


class GameState{
public:
    /// @brief
    /// Init function that`s called first time when state is active in the statemachine
    virtual void init() = 0;

    /// @brief
    /// handleInput function that`s called regularly in the gameloop to handle userinput
    virtual void handleInput() = 0;
    /// @brief
    /// Update function that`s called regularly in the gameloop to update the position of the objects on the screen
    /// \param delta The elapsed time since the last call of the Update function
    virtual void update( float delta ) = 0;
    /// Draw function that`s called once every loop to draw the object on the screen
    /// \param delta The elapsed time since the last call of the Update function
    virtual void draw( float delta ) = 0;
    /// @brief
    /// Function that`s called when new state is appended to statemachine on top of the current gamestate
    virtual void pause(){ }
    /// @brief
    /// Function that`s called when the state is resumed after state that was on top of the gamestate is removed
    virtual void resume(){ }

};


#endif //PROJECT_GAME_GAMESTATE_HPP
