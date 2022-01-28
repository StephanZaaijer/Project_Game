#include "MainGameState.hpp"
#include <utility>
#include "PauseState.hpp"
#include <iostream>

MainGameState::MainGameState(GameDataReference data):
    game_data (std::move(data))
{}

void MainGameState::Init(){
    game_data->assets.loadSoundBufferFromFile("_jumpSound", SOUND_JUMP_PATH);
    game_data->assets.loadSoundBufferFromFile("_pauseSound", SOUND_PAUSE_PATH);
    game_data->assets.loadSoundBufferFromFile("_gameMusicSound", MUSIC_GAME_PATH);

    _jumpSound.setBuffer(game_data->assets.GetSoundBuffer("_jumpSound"));
    _pauseSound.setBuffer(game_data->assets.GetSoundBuffer("_pauseSound"));
    _gameMusicSound.setBuffer(game_data->assets.GetSoundBuffer("_gameMusicSound"));

    _jumpSound.setVolume(game_data->json.Get_Soundvolume());
    _pauseSound.setVolume(game_data->json.Get_Soundvolume());
    _gameMusicSound.setVolume(game_data->json.Get_Musicvolume());
    _gameMusicSound.setLoop(true);

    if(game_data->json.Get_Musicstate()){
        _gameMusicSound.play();
    }

    character = std::unique_ptr<Character>(new Character(game_data));
    characterinfo = game_data->json.Get_PlayerSprite();
    game_data->assets.loadTextureFromFile(characterinfo.CharacterName, characterinfo.CharacterFileName);
    character->getSprite().setTexture( game_data->assets.GetTexture(characterinfo.CharacterName) );

    obstacles_container =  std::unique_ptr<Obstacle_Container>(new Obstacle_Container(game_data));
    wall = std::unique_ptr<Wall>(new Wall(game_data));
    background.setTexture(this->game_data->assets.GetTexture("Background"));
    background2.setTexture(this->game_data->assets.GetTexture("Background"));
    backGroundOffsetY2 = 0 - background.getGlobalBounds().height;
    wall->spawn_Wall(WALL_HEIGHT);

    for(unsigned int i = 0; i < wall->getWalls().size(); i++){
//        obstacles_container -> spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
        wall->setContainObstacleTrue(i);
    }
}

void MainGameState::HandleInput() {
    sf::Event event{};

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
            break;
        }
        if (game_data->input.IsKeyPressed(sf::Keyboard::Space)) {
            if(game_data->json.Get_Soundstate()){
                if(character->getJumpedTwice()) {
                    _jumpSound.play();
                }
            }
            character->Tap();
            character ->setJumpPressed(true);
        }
        else {
            character ->setJumpPressed(false);
        }
        if (!game_data->window.hasFocus()) {
            if(game_data->json.Get_Musicstate()){
                _gameMusicSound.pause();
            }
            if(game_data->json.Get_Soundstate()){
                _pauseSound.play();
            }
            game_data->machine.AddGameState(GameStateReference(new PauseState(game_data)), false);
        }
    }
}

void MainGameState::Update( float delta ){
    // update character
    character->Update(delta);

    // call collide funtion to check if character collides with something
    character->CollideWalls(wall->getAllRectangles());

    // move walls downwards if character is above limit and push character back
    if(character->getPosition().y < SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT){
        float move_down_by = (SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT) - character->getPosition().y;
        character ->addToScore(move_down_by);
        wall -> move_Wall(sf::Vector2f(0, move_down_by));
        backGroundOffsetY += move_down_by/BACKGROUND_SLIDE;
        backGroundOffsetY2 += move_down_by/BACKGROUND_SLIDE;
        background.setPosition(0, backGroundOffsetY);
        background2.setPosition(0, backGroundOffsetY2);
        if(backGroundOffsetY >= game_data->window.getSize().y){
            backGroundOffsetY = background2.getGlobalBounds().top - background2.getGlobalBounds().height;
        }
        if(backGroundOffsetY2 >= game_data->window.getSize().y){
            backGroundOffsetY2 = background.getGlobalBounds().top - background.getGlobalBounds().height;
        }

        obstacles_container->move_Obstacle(sf::Vector2f(0, move_down_by));
        character->moveDownByOffset(move_down_by);
    }

    // spawn walls and obstacles
    if (character->getHeight() > WALL_SPAWN_DISTANT + WALL_HEIGHT){
        wall ->spawn_Wall();
        for(unsigned int i = 0; i < wall->getWalls().size(); i++) {
            if (!(wall->getWalls()[i].contains_obstacles)) {
                obstacles_container->spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
                wall->setContainObstacleTrue(i);
            }
        }
        character->setHeight(0);
    }

    const std::vector<std::unique_ptr<Obstacle>> & obstacles = obstacles_container->getObstacle();
    for(const auto &obstacle : obstacles){
        if(obstacle->getBounds().intersects(character->GetBounds())){
            character->_death = true;
        }
    }

    if (character->_death){
        game_data -> score = character -> getScore();
        if(_gameMusicSound.getStatus()){
            _gameMusicSound.stop();
        }
        game_data->machine.AddGameState(GameStateReference(new GameOverState(game_data)), true);
    }
}

void MainGameState::Draw( float delta ){
    game_data -> window.clear();
    game_data-> window.draw(background);
    game_data-> window.draw(background2);
    wall -> draw_Wall();
    obstacles_container -> draw_Obstacle();
    character->Draw();
    game_data -> window.display();
}


void MainGameState::Resume(){
    _jumpSound.setVolume(game_data->json.Get_Soundvolume());
    _pauseSound.setVolume(game_data->json.Get_Soundvolume());
    _gameMusicSound.setVolume(game_data->json.Get_Musicvolume());
    if(game_data->json.Get_Musicstate()){
        _gameMusicSound.play();
    }
}