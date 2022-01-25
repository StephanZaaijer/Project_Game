#include "MainGameState.hpp"
#include <iostream>
#include <utility>
#include "PauseState.hpp"

MainGameState::MainGameState(GameDataReference data):
    game_data (std::move(data))
{}
//bool MainGameState::CollisionDetection(sf::FloatRect &object1, sf::FloatRect &object2) {
//    if(object1.intersects(object2)){
//        return true;
//    }
//    return false;
//}

bool MainGameState::CollisionDetection(sf::FloatRect object1, sf::FloatRect object2) {
    if(object1.intersects(object2)){
        return true;
    }
    return false;
}


void MainGameState::Init(){
    character = new Character(game_data);
    game_data->assets.loadTextureFromFile("character", CHARACTER_FRAME_1_FILEPATH);
    character->getSpriteToChange().setTexture( game_data->assets.GetTexture("character") );
    obstacles_container = new Obstacle_Container(game_data);
    wall = new Wall(game_data);
    background.setTexture(this->game_data->assets.GetTexture("Background"));

    wall->spawn_Wall(WALL_HEIGHT);

    for(unsigned int i = 0; i < wall->getWalls().size(); i++){
        obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
        wall->setContainObstacleTrue(i);
    }
}

void MainGameState::HandleInput() {
    sf::Event event{};

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

    if (character->getHeight() > WALL_SPAWN_DISTANT + WALL_HEIGHT){ // spawn wall and obstacle
        wall ->spawn_Wall();
        for(unsigned int i = 0; i < wall->getWalls().size(); i++)
            if (!(wall->getWalls()[i].contains_obstacles)){
                obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
                wall->setContainObstacleTrue(i);
            }
        character->setHeight(0);
    }

    if(character->getPosition().y < SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT){
        int move_down_by = (SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT) - character->getPosition().y;

        wall -> move_Wall(sf::Vector2f(0, move_down_by));
        obstacles_container->move_Obstacle(sf::Vector2f(0, move_down_by));
        character->moveDownByOffset(move_down_by);
    }

  
    for ( auto &wallBound : wall->getWalls()) {
        if(CollisionDetection(character->GetBound(), wallBound.wall.getGlobalBounds())){
            character->Collide(false);

        }
    }

    if (character->_death){
        game_data->machine.AddGameState(GameStateReference(new GameOverState(game_data)), true);
    }

    character->Update(delta);
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();
    game_data-> window.draw(background);
    wall -> draw_Wall();
    obstacles_container -> draw_Obstacle();
    character->Draw();
    game_data -> window.display();
}

MainGameState::~MainGameState() {
    delete character;
    delete obstacles_container;
    delete wall;
    background.~Sprite();
}