//
// Created by Franky on 19-1-2022.
//

#include "MainGameState.hpp"

MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}

void MainGameState::Init(){
    wall = new Wall(game_data);
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
    }
}

void MainGameState::Update( float delta ){
    wall -> move_Wall(sf::Vector2f(0, 3));
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();
    game_data-> window.setTitle("Main Game State");
    wall -> draw_Wall();
    game_data -> window.display();
}