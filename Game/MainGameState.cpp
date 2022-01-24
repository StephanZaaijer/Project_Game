#include "MainGameState.hpp"
#include <iostream>
#include "PauseState.hpp"


MainGameState::MainGameState(GameDataReference data):
    game_data (data)
{}
bool MainGameState::CollisionDetection(sf::FloatRect &object1, sf::FloatRect &object2) {
    if(object1.intersects(object2)){
        return true;
    }
    return false;
}

bool MainGameState::CollisionDetection(sf::FloatRect object1, sf::FloatRect object2) {
    if(object1.intersects(object2)){
        return true;
    }
    return false;
}


void MainGameState::Init(){
    wall = new Wall(game_data);
    obstacles_container = new Obstacle_Container(game_data);
    game_data->assets.loadTextureFromFile("Game Background Image", "Assets/StartupBackground.png");
    background.setTexture(this->game_data->assets.GetTexture("Game Background Image"));
    wall->spawn_Wall(WALL_HEIGHT);
    for(unsigned int i = 0; i < wall->getWalls().size(); i++){
        obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i]);
        wall->setContainObstacleTrue(i);
    }
    game_data->assets.loadTextureFromFile("character", CHARACTER_FRAME_1_FILEPATH);
    character = new Character(game_data);
}

void MainGameState::HandleInput() {
    sf::Event event;

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
        if (game_data->input.IsKeyPressed(sf::Keyboard::Space)) {
            character->Tap();
        }
        if (!game_data->window.hasFocus()) {
            game_data->machine.AddGameState(GameStateReference(new PauseState(game_data)), false);
        }
    }
}

void MainGameState::Update( float delta ){
    if(character->getPosition().y < SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT){
        float move_down_by = (SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT) - character->getPosition().y;
        wall -> move_Wall(sf::Vector2f(0, move_down_by));
        obstacles_container->move_Obstacle(sf::Vector2f(0, move_down_by));
    }
  
    for ( auto &wallBound : wall->getWalls()) {
        if(CollisionDetection(character->GetBound(), wallBound.getGlobalBounds())){
            character->Collide(false);
        }
    //    if(CollisionDetection(character->GetBound(), spike->getGlobalBounds())){
//            character->Collide(True);
//        }
    }
  
//     if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//         character.move(0, -5);
//         char_height += 5;
//     }

    if (char_height > WALL_SPAWN_DISTANT + WALL_HEIGHT){ // spawn wall and obstacle
        wall ->spawn_Wall();
        for(unsigned int i = 0; i < wall->getContainsObstacles().size(); i++)
            if (wall->getContainsObstacles()[i] == false){
                obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i]);
                wall->setContainObstacleTrue(i);
            }
        char_height = 0;
    }
    character->Update(delta);
    wall -> move_Wall(sf::Vector2f(0, 3));
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();

    // draw something
    character->Draw();
    game_data-> window.setTitle("Main Game State");
    game_data-> window.draw(background);
    wall -> draw_Wall();
    obstacles_container -> draw_Obstacle();
    game_data -> window.display();
}