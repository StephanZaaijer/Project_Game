#include "MainGameState.hpp"
#include <utility>
#include "PauseState.hpp"
#include <iostream>

MainGameState::MainGameState(GameDataReference data):
    gameData (std::move(data))
{}

void MainGameState::Init(){
    _jumpSound.setBuffer(gameData->assets.getSoundBuffer("jumpSound"));
    _pauseSound.setBuffer(gameData->assets.getSoundBuffer("pauseSound"));
    _gameMusicSound.setBuffer(gameData->assets.getSoundBuffer("gameMusic"));
    _coinPickup.setBuffer(gameData->assets.getSoundBuffer("coinPickup"));


    _score.setFont(gameData->assets.getFont("Bauhaus"));
    _score.setCharacterSize(40);
    _score.setFillColor(TEXT_COLOR);

    coin_text.setFont(gameData->assets.getFont("Bauhaus"));
    coin_text.setCharacterSize(40);
    coin_text.setFillColor(TEXT_COLOR);

    _jumpSound.setVolume(gameData->json.Get_Soundvolume());
    _pauseSound.setVolume(gameData->json.Get_Soundvolume());
    _gameMusicSound.setVolume(gameData->json.Get_Musicvolume());
    _gameMusicSound.setLoop(true);

    if(gameData->json.Get_Musicstate()){
        _gameMusicSound.play();
    }

    character = std::unique_ptr<Character>(new Character(gameData));
    characterinfo = gameData->json.Get_PlayerSprite();
    gameData->assets.loadTextureFromFile(characterinfo.CharacterName, characterinfo.CharacterFileName);
    character->getSprite().setTexture( gameData->assets.getTexture(characterinfo.CharacterName) );

    obstacles_container =  std::unique_ptr<Obstacle_Container>(new Obstacle_Container(gameData));
    wall = std::unique_ptr<Wall>(new Wall(gameData));
    coins_container = std::unique_ptr<Coin_Container>(new Coin_Container(gameData));
    background.setTexture(gameData->assets.getTexture("BackgroundGround"));
    background2.setTexture(gameData->assets.getTexture("Background"));
    backGroundOffsetY2 = 0 - background.getGlobalBounds().height;
    background2.setPosition(0, backGroundOffsetY2);
    wall->spawn_Wall(WALL_HEIGHT);

    for(unsigned int i = 0; i < wall->getWalls().size(); i++){
        wall->setContainObstacleTrue(i);
    }
}

void MainGameState::handleInput() {
    sf::Event event{};

    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
            break;
        }
        if (gameData->input.IsKeyPressed(sf::Keyboard::Space) and !prevKeystate_start) {
            if(gameData->json.Get_Soundstate()){
                if(character->getJumpedTwice() && !jumpSoundPlayed) {
                    _jumpSound.play();
                    jumpSoundPlayed = true;
                }
            }
            character->Tap();
            character ->setJumpPressed(true);
        }
        else if (gameData->input.IsKeyPressed(sf::Keyboard::Escape)) {
            if (gameData->json.Get_Musicstate()) {
                _gameMusicSound.pause();
            }
            if (gameData->json.Get_Soundstate()) {
                _pauseSound.play();
            }
            gameData->machine.AddGameState(GameStateReference(new PauseState(gameData)), false);
        }
        else {
            character ->setJumpPressed(false);
            jumpSoundPlayed = false;
        }
        if (!gameData->window.hasFocus()) {
            if(gameData->json.Get_Musicstate()){
                _gameMusicSound.pause();
            }
            if(gameData->json.Get_Soundstate()){
                _pauseSound.play();
            }
            gameData->machine.AddGameState(GameStateReference(new PauseState(gameData)), false);
        }
    }
    if(prevKeystate_start){
        prevKeystate_start = gameData->input.IsKeyPressed(sf::Keyboard::Space);
    }
}

void MainGameState::Update( float delta ){
    // update character
    character->Update(delta);

    // call collide funtion to check if character collides with something
    character->CollideWalls(wall->getAllRectangles());

    // move everything downwards if character is above limit and push character back
    if(character->getPosition().y < SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT){
        float move_down_by = (SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT) - character->getPosition().y;
        character ->addToScore(move_down_by);
        wall -> move_Wall(sf::Vector2f(0, move_down_by));
        coins_container ->move(sf::Vector2f(0, move_down_by));
        backGroundOffsetY += move_down_by/BACKGROUND_SLIDE;
        backGroundOffsetY2 += move_down_by/BACKGROUND_SLIDE;
        background.setPosition(0, backGroundOffsetY);
        background2.setPosition(0, backGroundOffsetY2);
        if(backGroundOffsetY >= gameData->window.getSize().y){
            backGroundOffsetY = background2.getGlobalBounds().top - background2.getGlobalBounds().height;
            counter++;
        }

        if(backGroundOffsetY2 >= gameData->window.getSize().y){
            backGroundOffsetY2 = background.getGlobalBounds().top - background.getGlobalBounds().height;
            counter++;
        }

        obstacles_container->move_Obstacle(sf::Vector2f(0, move_down_by));
        character->moveDownByOffset(move_down_by);
    }


    switch (counter) {
        case 0:
            background2.setTexture(gameData->assets.getTexture("Background"));
            break;

        case 1:
            background.setTexture(gameData->assets.getTexture("Background"));
            break;

        case 3:
            background.setTexture(gameData->assets.getTexture("BackgroundNoClouds"));
            break;

        case 4:
            background2.setTexture(gameData->assets.getTexture("BackgroundNoClouds"));
            break;

        case 5:
            background.setTexture(gameData->assets.getTexture("SkyToSpaceBackground"));
            break;

        case 6:
            background2.setTexture(gameData->assets.getTexture("SpaceBackground"));
            break;

        case 7:
            background.setTexture(gameData->assets.getTexture("SpaceBackground"));
            break;

        case 12:
            background2.setTexture(gameData->assets.getTexture("SpaghettiMonsterBackground"));
            break;

        case 14:
            background2.setTexture(gameData->assets.getTexture("SpaceBackground"));
            break;
    }


    // spawn walls, obstacles and coins
    if (character->getHeight() > WALL_SPAWN_DISTANT + WALL_HEIGHT){
        // Wall spawn
        wall ->spawn_Wall();

        // Obstacle spawn
        for(unsigned int i = 0; i < wall->getWalls().size(); i++) {
            if (!(wall->getWalls()[i].contains_obstacles)) {
                obstacles_container->spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
                wall->setContainObstacleTrue(i);
            }
        }
        // Coin spawn
        coins_container -> spawn();

        // Obstacle Coin collision
        const std::vector<std::unique_ptr<Obstacle>> & obstacles = obstacles_container->getObstacle();
        std::vector<std::unique_ptr<Coin>> &coins = coins_container->getCoins();
            for (const auto &obstacle: obstacles) {
                auto it = std::remove_if(coins.begin(), coins.end(),
                                         [&obstacle](std::unique_ptr<Coin> &coin)
                {
                    return (obstacle->getBounds().intersects(coin->getBounds()));
                });
                coins.erase(it, coins.end());
            }
        character->setHeight(0);
    }

    // Character Coin collision
    std::vector<std::unique_ptr<Coin>> &coins = coins_container->getCoins();
    auto it = std::remove_if(coins.begin(),coins.end(),[this](std::unique_ptr<Coin> & coin){
        return (coin -> getBounds().intersects(character->GetBounds()));
    });
    std::for_each(it, coins.end(), [this](std::unique_ptr<Coin> & coin){
        acquired_coins += 1;
        _coinPickup.play();
    });
    coins.erase(it, coins.end());

//     Character Obstacle collision
    const std::vector<std::unique_ptr<Obstacle>> & obstacles = obstacles_container->getObstacle();
    for(const auto &obstacle : obstacles){
        if(obstacle->getID() == deathwall){
            if(obstacle->getBounds().intersects(character->GetBounds())){
                character->_death = true;
            }
        }
        else if(obstacle->getID() == spike){
            if(obstacle->getBounds().intersects(character->GetBounds())){
                if(character->CollideSpike(obstacle)){
                    character->_death = true;
                }
            }
        }
    }

    _score.setString("Score: " + std::to_string(character->getScore()));
    _score.setPosition(BORDER_WALL_WIDTH + (SCREEN_HEIGHT / 20.0f),SCREEN_HEIGHT / 20.0f);
    coin_text.setString("Coins: " + std::to_string(acquired_coins));
    coin_text.setPosition(BORDER_WALL_2_START - (SCREEN_HEIGHT / 20.0f) - coin_text.getGlobalBounds().width,SCREEN_HEIGHT / 20.0f);

    if (character->_death){
        gameData -> score = character -> getScore();
        gameData -> coins = acquired_coins;
        if(_gameMusicSound.getStatus()){
            _gameMusicSound.stop();
        }
        gameData->machine.AddGameState(GameStateReference(new GameOverState(gameData)), true);
    }
}

void MainGameState::Draw( float delta ){
    gameData -> window.clear();
    gameData -> window.draw(background);
    gameData -> window.draw(background2);
    wall -> draw_Wall();
    obstacles_container -> draw_Obstacle();
    character->Draw();
    coins_container -> draw();
    gameData -> window.draw(_score);
    gameData -> window.draw(coin_text);
    gameData -> window.display();
}

void MainGameState::Resume(){
    _jumpSound.setVolume(gameData->json.Get_Soundvolume());
    _pauseSound.setVolume(gameData->json.Get_Soundvolume());
    _coinPickup.setVolume(gameData->json.Get_Soundvolume());
    _gameMusicSound.setVolume(gameData->json.Get_Musicvolume());
    if(gameData->json.Get_Musicstate()){
        _gameMusicSound.play();
    }
}