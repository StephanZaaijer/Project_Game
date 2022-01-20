#include "MainGameState.hpp"

MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}

void MainGameState::init(){

}

void MainGameState::HandleInput(){
    sf::Event event;

    while(game_data -> window.pollEvent( event )){
        if(sf::Event::Closed == event.type){
            game_data -> window.close();
        }
    }
}

void MainGameState::Update( float delta ){

}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();

    // draw something

    game_data -> window.display();
}