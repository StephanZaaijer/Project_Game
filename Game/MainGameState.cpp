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
    wall->spawn_Wall(WALL_HEIGHT);
    for(unsigned int i = 0; i < wall->getWalls().size(); i++){
        obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i]);
        wall->setContainObstacleTrue(i);
    }

    character.setRadius(60);
    character.setPosition(
            SCREEN_WIDTH / 2 - character.getRadius() / 2,
            SCREEN_HEIGHT - 100
            );
    character.setFillColor(sf::Color::Red);
}

void MainGameState::HandleInput(){
    sf::Event event;

    while(game_data -> window.pollEvent( event )){
        if(sf::Event::Closed == event.type){
            game_data -> window.close();
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        character.move(0, -5);
        char_height += 5;
    }

    if (char_height > WALL_SPAWN_DISTANT + WALL_HEIGHT){ // spawn wall and obstacle
        wall ->spawn_Wall();
        for(unsigned int i = 0; i < wall->getContainsObstacles().size(); i++)
            if (wall->getContainsObstacles()[i] == false){
                obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i]);
                wall->setContainObstacleTrue(i);
            }
        char_height = 0;
    }
}

void MainGameState::Update( float delta ){
    if(character.getPosition().y < SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT){
        float move_down_by = (SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT) - character.getPosition().y;
        wall -> move_Wall(sf::Vector2f(0, move_down_by));
        obstacles_container ->move_Obstacle(sf::Vector2f(0, move_down_by));
        character.move(0, move_down_by);
    }
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();
    game_data-> window.setTitle("Main Game State");
    game_data-> window.draw(background);
    wall -> draw_Wall();
    game_data -> window.draw(character);
    obstacles_container -> draw_Obstacle();
    game_data -> window.display();
}