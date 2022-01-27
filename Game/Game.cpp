#include "Game.hpp"
#include "StartUpState.hpp"
#include "IconArray.hpp"

Game::Game(const int &screen_width, const int &screen_height, const std::string &game_title) {
    game_data->window.create(sf::VideoMode(screen_width, screen_height), game_title, sf::Style::Close | sf::Style::Titlebar);
    game_data->window.setIcon(100,100, iconArray2);

    game_data->machine.AddGameState(GameStateReference(new StartUpState(game_data)));
    start();
}

void Game::start() {
    float new_time, frameTime;
    float current_time = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0;
    while (game_data->window.isOpen()) {
        game_data->machine.ProcessGameStateChanges();
        new_time = clock.getElapsedTime().asSeconds();
        frameTime = new_time - current_time;
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        current_time = new_time;
        accumulator += frameTime;

        while (accumulator >= delta) {
            game_data->machine.GetActiveGameState()->HandleInput();
            game_data->machine.GetActiveGameState()->Update(delta);
            accumulator -= delta;
        }
        game_data->machine.GetActiveGameState()->Draw(accumulator / delta);
        sf::sleep(sf::milliseconds(20));
        std::cout << "Length gamestates = " << game_data->machine.GetLenGamestates() << '\n';

        std::cout << "Opbouw statemachine stack:\n";
        std::vector<std::string> states = game_data->machine.Get_Gamestatenames();
        int counter = 0;
        for(const auto& state: states){
            std::cout << counter << ":\t" << state << '\n';
            counter++;
        }
        std::cout << "Current state: " << game_data->machine.GetActiveGameState()->ID() << "\n\n\n\n\n";
        game_data->json.Update();
    }
    std::cout << "\t\t\twindow closed\n\n";
    std::cout << "Length gamestates = " << game_data->machine.GetLenGamestates() << '\n';

    std::cout << "Opbouw statemachine stack:\n";
    std::vector<std::string> states = game_data->machine.Get_Gamestatenames();
    int counter = 0;
    for(const auto& state: states){
        std::cout << counter << ":\t" << state << '\n';
        counter++;
    }
    std::cout << "Current state: " << game_data->machine.GetActiveGameState()->ID() << '\n';
    game_data->json.Direct_write();
}


