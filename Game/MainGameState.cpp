#include "MainGameState.hpp"
#include <utility>
#include "PauseState.hpp"
#include <iostream>

MainGameState::MainGameState(GameDataReference data):
    game_data (std::move(data))
{}

void MainGameState::Init(){
    _jumpSound.setBuffer(game_data->assets.GetSoundBuffer("jumpSound"));
    _pauseSound.setBuffer(game_data->assets.GetSoundBuffer("pauseSound"));
    _gameMusicSound.setBuffer(game_data->assets.GetSoundBuffer("gameMusic"));

    _score.setFont(game_data->assets.GetFont("Bauhaus"));
    _score.setCharacterSize(60);
    _score.setFillColor(TEXT_COLOR);


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
    coins_container = std::unique_ptr<Coin_Container>(new Coin_Container(game_data));
    background.setTexture(this->game_data->assets.GetTexture("BackgroundGround"));
    background2.setTexture(this->game_data->assets.GetTexture("BackgroundGround"));
    backGroundOffsetY2 = 0 - background.getGlobalBounds().height;
    background2.setPosition(0, backGroundOffsetY2);
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
                if(character->getJumpedTwice() && !jumpSoundPlayed) {
                    _jumpSound.play();
                    jumpSoundPlayed = true;
                }
            }
            character->Tap();
            character ->setJumpPressed(true);
        }
        else if (game_data->input.IsKeyPressed(sf::Keyboard::Escape)) {
            if (game_data->json.Get_Musicstate()) {
                _gameMusicSound.pause();
            }
            if (game_data->json.Get_Soundstate()) {
                _pauseSound.play();
            }
            game_data->machine.AddGameState(GameStateReference(new PauseState(game_data)), false);
        }
        else {
            character ->setJumpPressed(false);
            jumpSoundPlayed = false;
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
        coins_container ->move(sf::Vector2f(0, move_down_by));
        backGroundOffsetY += move_down_by/BACKGROUND_SLIDE;
        backGroundOffsetY2 += move_down_by/BACKGROUND_SLIDE;
        background.setPosition(0, backGroundOffsetY);
        background2.setPosition(0, backGroundOffsetY2);
        if(backGroundOffsetY >= game_data->window.getSize().y){
            backGroundOffsetY = background2.getGlobalBounds().top - background2.getGlobalBounds().height;
            counter++;
        }
        if(backGroundOffsetY2 >= game_data->window.getSize().y){
            backGroundOffsetY2 = background.getGlobalBounds().top - background.getGlobalBounds().height;
            counter++;
        }
        obstacles_container->move_Obstacle(sf::Vector2f(0, move_down_by));
        character->moveDownByOffset(move_down_by);
    }


    switch (counter) {
        case 0:
            background2.setTexture(this->game_data->assets.GetTexture("Background"));
            break;

        case 1:
            background.setTexture(this->game_data->assets.GetTexture("Background"));
            break;

        case 3:
            background.setTexture(this->game_data->assets.GetTexture("BackgroundNoClouds"));
            break;

        case 4:
            background2.setTexture(this->game_data->assets.GetTexture("BackgroundNoClouds"));
            break;

        case 5:
            background.setTexture(this->game_data->assets.GetTexture("SkyToSpaceBackground"));
            break;

        case 6:
            background2.setTexture(this->game_data->assets.GetTexture("SpaceBackground"));
            break;

        case 7:
            background.setTexture(this->game_data->assets.GetTexture("SpaceBackground"));
            break;

        case 8:
            background2.setTexture(this->game_data->assets.GetTexture("SpaghettiMonsterBackground"));
            break;

        case 12:
            background2.setTexture(this->game_data->assets.GetTexture("SpaceBackground"));
            break;
    }


    // spawn walls and obstacles
    if (character->getHeight() > WALL_SPAWN_DISTANT + WALL_HEIGHT){
        wall ->spawn_Wall();
        coins_container ->spawn();
        for(unsigned int i = 0; i < wall->getWalls().size(); i++) {
            if (!(wall->getWalls()[i].contains_obstacles)) {
                obstacles_container->spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
                wall->setContainObstacleTrue(i);
            }
        }
        character->setHeight(0);
    }

    std::vector<std::unique_ptr<Coin>> & coins = coins_container -> getCoins();
    auto it = std::remove_if(coins.begin(),coins.end(),[this](std::unique_ptr<Coin> & coin){
        return (coin -> getBounds().intersects(character->GetBounds()));
    });
    std::for_each(it, coins.end(), [this](std::unique_ptr<Coin> & coin){
        this -> acquired_coins += 1;
    });
    coins.erase(it, coins.end());

    const std::vector<std::unique_ptr<Obstacle>> & obstacles = obstacles_container->getObstacle();
    for(const auto &obstacle : obstacles){
        if(obstacle->getBounds().intersects(character->GetBounds())){
            character->_death = true;
        }
    }

    _score.setString(std::to_string(character->getScore()));
    _score.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 20.0f);

    if (character->_death){
        game_data -> score = character -> getScore();
        game_data -> coins = acquired_coins;
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
    coins_container -> draw();
    game_data -> window.draw(_score);
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