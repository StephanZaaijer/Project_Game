#include "MainGameState.hpp"


MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}

void MainGameState::Init(){
    game_data->assets.loadTextureFromFile("character", CHARACTER_FRAME_1_FILEPATH);
    character = new Character(game_data);
}

void MainGameState::HandleInput(){
    sf::Event event;

    while(game_data -> window.pollEvent( event )){
        if(sf::Event::Closed == event.type){
            game_data -> window.close();
        }
        if(game_data->input.IsSpriteClicked(_background, sf::Mouse::Left, game_data->window)){
            character->Tap();
        }
    }
}

void MainGameState::Update( float delta ){
    character->Update(delta);
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();

    // draw something
    character->Draw();
    game_data -> window.display();
}