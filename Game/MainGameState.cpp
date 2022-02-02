#include "MainGameState.hpp"
#include <utility>
#include "PauseState.hpp"
#include <iostream>

MainGameState::MainGameState(GameDataReference gameData):
    gameData (std::move(gameData))
{}

void MainGameState::init(){
    jumpSound.setBuffer(gameData->assets.getSoundBuffer("jumpSound"));
    pauseSound.setBuffer(gameData->assets.getSoundBuffer("pauseSound"));
    gameMusicSound.setBuffer(gameData->assets.getSoundBuffer("gameMusic"));
    coinPickup.setBuffer(gameData->assets.getSoundBuffer("coinPickup"));


    score.setFont(gameData->assets.getFont("Bauhaus"));
    score.setCharacterSize(40);
    score.setFillColor(TEXT_COLOR);

    coinText.setFont(gameData->assets.getFont("Bauhaus"));
    coinText.setCharacterSize(40);
    coinText.setFillColor(TEXT_COLOR);

    jumpSound.setVolume(gameData->json.getSoundVolume());
    pauseSound.setVolume(gameData->json.getSoundVolume());
    gameMusicSound.setVolume(gameData->json.getMusicVolume());
    gameMusicSound.setLoop(true);

    if(gameData->json.getMusicState()){
        gameMusicSound.play();
    }

    character = std::unique_ptr<Character>(new Character(gameData));
    characterInfo = gameData->json.getPlayerSprite();
    gameData->assets.loadTextureFromFile(characterInfo.CharacterName, characterInfo.CharacterFileName);
    character->getSprite().setTexture( gameData->assets.getTexture(characterInfo.CharacterName) );

    obstaclesContainer =  std::unique_ptr<Obstacle_Container>(new Obstacle_Container(gameData));
    wall = std::unique_ptr<Wall>(new Wall(gameData));
    coinsContainer = std::unique_ptr<Coin_Container>(new Coin_Container(gameData));
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
        if (gameData->input.isKeyPressed(sf::Keyboard::Space) and !prevKeystateStart) {
            if(gameData->json.getSoundState()){
                if(character->getJumpedTwice() && !jumpSoundPlayed) {
                    jumpSound.play();
                    jumpSoundPlayed = true;
                }
            }
            character->Tap();
            character ->setJumpPressed(true);
        }
        else if (gameData->input.isKeyPressed(sf::Keyboard::Escape)) {
            if (gameData->json.getMusicState()) {
                gameMusicSound.pause();
            }
            if (gameData->json.getSoundState()) {
                pauseSound.play();
            }
            gameData->machine.AddGameState(GameStateReference(new PauseState(gameData)), false);
        }
        else {
            character ->setJumpPressed(false);
            jumpSoundPlayed = false;
        }
        if (!gameData->window.hasFocus()) {
            if(gameData->json.getMusicState()){
                gameMusicSound.pause();
            }
            if(gameData->json.getSoundState()){
                pauseSound.play();
            }
            gameData->machine.AddGameState(GameStateReference(new PauseState(gameData)), false);
        }
    }
    if(prevKeystateStart){
        prevKeystateStart = gameData->input.isKeyPressed(sf::Keyboard::Space);
    }
}

void MainGameState::update( float delta ){
    // update character
    character->update(delta);

    // call collide funtion to check if character collides with something
    character->CollideWalls(wall->getAllRectangles());

    // move everything downwards if character is above limit and push character back
    if(character->getPosition().y < SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT){
        float move_down_by = (SCREEN_HEIGHT - CHARACTER_MAX_HEIGHT) - character->getPosition().y;
        character ->addToScore(move_down_by);
        wall -> move_Wall(sf::Vector2f(0, move_down_by));
        coinsContainer ->move(sf::Vector2f(0, move_down_by));
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

        obstaclesContainer->move_Obstacle(sf::Vector2f(0, move_down_by));
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
                obstaclesContainer->spawn_Obstacle_On_Wall(wall->getWalls()[i].wall);
                wall->setContainObstacleTrue(i);
            }
        }
        // Coin spawn
        coinsContainer -> spawn();

        // Obstacle Coin collision
        const std::vector<std::unique_ptr<Obstacle>> & obstacles = obstaclesContainer->getObstacle();
        std::vector<std::unique_ptr<Coin>> &coins = coinsContainer->getcoins();
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
    std::vector<std::unique_ptr<Coin>> &coins = coinsContainer->getcoins();
    auto it = std::remove_if(coins.begin(),coins.end(),[this](std::unique_ptr<Coin> & coin){
        return (coin -> getBounds().intersects(character->GetBounds()));
    });
    std::for_each(it, coins.end(), [this](std::unique_ptr<Coin> & coin){
        acquiredCoins += 1;
        coinPickup.play();
    });
    coins.erase(it, coins.end());

//     Character Obstacle collision
    const std::vector<std::unique_ptr<Obstacle>> & obstacles = obstaclesContainer->getObstacle();
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

    score.setString("Score: " + std::to_string(character->getScore()));
    score.setPosition(BORDER_WALL_WIDTH + (SCREEN_HEIGHT / 20.0f),SCREEN_HEIGHT / 20.0f);
    coinText.setString("coins: " + std::to_string(acquiredCoins));
    coinText.setPosition(BORDER_WALL_2_START - (SCREEN_HEIGHT / 20.0f) - coinText.getGlobalBounds().width,SCREEN_HEIGHT / 20.0f);

    if (character->_death){
        gameData -> score = character -> getScore();
        gameData -> coins = acquiredCoins;
        if(gameMusicSound.getStatus()){
            gameMusicSound.stop();
        }
        gameData->machine.AddGameState(GameStateReference(new GameOverState(gameData)), true);
    }
}

void MainGameState::draw( float delta ){
    gameData -> window.clear();
    gameData -> window.draw(background);
    gameData -> window.draw(background2);
    wall -> draw_Wall();
    obstaclesContainer -> draw_Obstacle();
    character->draw();
    coinsContainer -> draw();
    gameData -> window.draw(score);
    gameData -> window.draw(coinText);
    gameData -> window.display();
}

void MainGameState::resume(){
    jumpSound.setVolume(gameData->json.getSoundVolume());
    pauseSound.setVolume(gameData->json.getSoundVolume());
    coinPickup.setVolume(gameData->json.getSoundVolume());
    gameMusicSound.setVolume(gameData->json.getMusicVolume());
    if(gameData->json.getMusicState()){
        gameMusicSound.play();
    }
}