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
};

/// Typedefinition to define std::shared_prt<GameData> as GameDataReference
typedef std::shared_ptr<GameData> GameDataReference;

class Game {
private:
    const float delta = 1.0/ FRAMERATE;
    sf::Clock clock;
    GameDataReference game_data = std::make_shared<GameData>();
    void start();
public:
    /// @brief
    /// constructor that creates the window, and loads the StartUpstate into the statemachine.
    /// \param screen_width The width of the renderwindow
    /// \param screen_height The height of the renderwindow
    /// \param game_title The title of the game shown in the menubar of the window
    Game(const int &screen_width, const int &screen_height, const std::string &game_title);
};


#endif //PROJECT_GAME_GAME_HPP
