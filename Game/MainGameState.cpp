#include "MainGameState.hpp"
#include <iostream>

MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}
bool MainGameState::CollisionDetection(sf::Sprite &object1, sf::Sprite &object2) {
    if(object1.getGlobalBounds().intersects(object2.getGlobalBounds())){
        return true;
    }
    return false;
}

void MainGameState::Init(){
    wall = new Wall(game_data);
    game_data->assets.loadTextureFromFile("character", CHARACTER_FRAME_1_FILEPATH);
    character = new Character(game_data);
}

void MainGameState::HandleInput(){
    sf::Event event;

    while(game_data -> window.pollEvent( event )){
        if(sf::Event::Closed == event.type){
            game_data -> window.close();
        }
    }
    if(game_data->input.IsButtonPressed( sf::Mouse::Button::Left)){
            character->Tap();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        wall ->spawn_Wall();
    }
}

void MainGameState::Update( float delta ){
    for ( auto wallSprite : wall->GetWall()) {
        if(CollisionDetection(character->GetSprite(),wallSprite.getGlobalBounds())){

        }
    }
    character->Update(delta);
    wall -> move_Wall(sf::Vector2f(0, 3));
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();

    // draw something
    character->Draw();
    game_data-> window.setTitle("Main Game State");
    wall -> draw_Wall();
    game_data -> window.display();
}