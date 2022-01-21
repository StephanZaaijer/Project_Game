//
// Created by Franky on 19-1-2022.
//

#include "MainGameState.hpp"
#include <iostream>

MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}

void MainGameState::Init(){
    wall = new Wall(game_data);
    obstacles_container = new Obstacle_Container(game_data);
    game_data->assets.loadTextureFromFile("Game Background Image", "Assets/StartupBackground.png");
    background.setTexture(this->game_data->assets.GetTexture("Game Background Image"));
}

void MainGameState::HandleInput(){
    sf::Event event;

    while(game_data -> window.pollEvent( event )){
        if(sf::Event::Closed == event.type){
            game_data -> window.close();
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        wall ->spawn_Wall();
        obstacles_container ->spawn_Obstacle(Spike_Object);
        std::cout << "spawn succes" << std::endl;;
    }
}

void MainGameState::Update( float delta ){
    wall -> move_Wall(sf::Vector2f(0, 3));
    obstacles_container ->move_Obstacle(sf::Vector2f(0, 3));
    std::cout << "Move succes" << std::endl;;
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();
    game_data-> window.setTitle("Main Game State");
    game_data-> window.draw(background);
    obstacles_container -> draw_Obstacle();
    wall -> draw_Wall();
    game_data -> window.display();
}