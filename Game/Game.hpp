#ifndef PROJECT_GAME_GAME_HPP
#define PROJECT_GAME_GAME_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "JsonManager.hpp"

/// @file Game.hpp
/// @brief
/// Project_Game: Game class that constructs all the machines, the window and contains the gameloop


/// @brief
/// struct that contains all the Machines, the window and the score.
struct GameData {
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
    JsonManager json = JsonManager(GAME_FILE);
    int score = 0;
    int coins = 0;
    std::string test = "test";
};

/// @brief
/// Typedefinition to define std::shared_prt<GameData> as GameDataReference
typedef std::shared_ptr<GameData> GameDataReference;

class Game {
private:
    const float delta = 1.0/ FRAMERATE;
    sf::Clock clock;
    GameDataReference gameData = std::make_shared<GameData>();
    void start();
public:
    /// @brief
    /// constructor that creates the window, and loads the StartUpstate into the statemachine.
    /// \param screenWidth The width of the renderwindow
    /// \param screenHeight The height of the renderwindow
    /// \param gameTitle The title of the game shown in the menubar of the window
    Game(const int &screenWidth, const int &screenHeight, const std::string &gameTitle);
};


#endif //PROJECT_GAME_GAME_HPP
