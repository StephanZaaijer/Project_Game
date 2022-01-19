#include "MainGameState.hpp"


MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}

void MainGameState::Init(){
    game_data->assets.loadTextureFromFile("character ", CHARACTER_FRAME_1_FILEPATH);
    character = new stick_to_wall(game_data);
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
    character->Draw();
    game_data -> window.display();
}