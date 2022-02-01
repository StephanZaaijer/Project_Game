#ifndef PROJECT_GAME_GAME_HPP
#define PROJECT_GAME_GAME_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "JsonManager.hpp"

struct GameData {
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
    JsonManager json = JsonManager(GAME_FILE);
    int score = 0;
    int coins = 0;
};

typedef std::shared_ptr<GameData> GameDataReference;

class Game {
private:
    const float delta = 1.0/ FRAMERATE;
    sf::Clock clock;

    GameDataReference game_data = std::make_shared<GameData>();
    void start();
public:
    Game(const int &screen_width, const int &screen_height, const std::string &game_title);
};


#endif //PROJECT_GAME_GAME_HPP
