#ifndef PROJECT_GAME_MAINGAMESTATE_HPP
#define PROJECT_GAME_MAINGAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"
#include "GameState.hpp"
#include "Game.hpp"
#include "Wall.hpp"
#include "ObstaclesContainer.hpp"
#include "Character.hpp"
#include "GameOverState.hpp"
#include "Line.hpp"
#include "CoinContainer.hpp"

/// @file
/// @brief
/// Project_Game: MainGameState is the state you're in when you're playing the game.

/// @brief
/// This class is used to create and display the main game and handle all game related events.
class MainGameState : public GameState{
private:
    GameDataReference gameData;
    std::unique_ptr<Wall> wall;
    sf::Sprite background;
    sf::Sprite background2;
    std::unique_ptr<ObstacleContainer> obstaclesContainer;
    std::unique_ptr<Character> character;
    CustomCharacter characterInfo;
    std::unique_ptr<CoinContainer> coinsContainer;
    sf::Text score;
    sf::Text coinText;
    sf::Sound jumpSound;
    sf::Sound pauseSound;
    sf::Sound gameMusicSound;
    sf::Sound coinPickup;
    float backGroundOffsetY = 0;
    float backGroundOffsetY2;
    int acquiredCoins = 0;
    int counter = 0;
    bool jumpSoundPlayed = false;
    bool prevKeystateStart = true;
    bool death = false;

public:

    /// @brief
    /// This constructor constructs an object of the MainGameState class.
    /// \param gameData The game_data of a state, which contains the StateMachine, window, AssetManager, InputManager and JsonManager.
    MainGameState(GameDataReference gameData);

    /// @brief
    /// this function initializes all the sounds, colors, textures and positions of all elements in this state.
    void init() override;

    /// @brief
    /// This function handles all user input for this state.
    void handleInput() override;

    /// @brief
    /// This function updates all game events in this state.
    /// @details
    /// This function calls the character update function.
    /// It calls the collideWalls function on the character to check if the character is colliding with a wall.
    /// When the player is above a certain height, score is added to the player's score, the background is moved down, and a new background may be rendered.
    /// It also checks if the character has died, it spawns new obstacles if needed and checks if a coin is collected.
    void update() override;

    /// @brief
    /// This function draws all elements of this state onto the screen.
    void draw() override;

    /// @brief
    /// This function sets the volume of the sounds and checks if it has to play the game sound.
    void resume() override;

};

#endif // PROJECT_GAME_MAINGAMESTATE_HPP