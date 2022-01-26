#include "MainGameState.hpp"
#include <utility>
#include "PauseState.hpp"

MainGameState::MainGameState(GameDataReference data):
    game_data (std::move(data))
{}

void MainGameState::Init(){
    if( !_jumpSoundBuffer.loadFromFile(SOUND_JUMP_PATH)){
        std::cout << "ERROR loading jump sound" << std::endl;
    }
    if( !_deathSoundBuffer.loadFromFile(SOUND_DEATH_PATH)){
        std::cout << "ERROR loading death sound" << std::endl;
    }
    if( !_pauseSoundBuffer.loadFromFile(SOUND_PAUSE_PATH)){
        std::cout << "ERROR loading pause sound" << std::endl;
    }
    if( !_gameMusicSoundBuffer.loadFromFile(MUSIC_GAME_PATH)){
        std::cout << "ERROR loading music" << std::endl;
    }

    _jumpSound.setBuffer( _jumpSoundBuffer);
    _jumpSound.setVolume(game_data->json.Get_Soundvolume());
    _deathSound.setBuffer( _deathSoundBuffer );
    _deathSound.setVolume(game_data->json.Get_Soundvolume());
    _pauseSound.setBuffer( _pauseSoundBuffer );
    _pauseSound.setVolume(game_data->json.Get_Soundvolume());
    _gameMusicSound.setBuffer( _gameMusicSoundBuffer );
    _gameMusicSound.setVolume(game_data->json.Get_Musicvolume());

    _gameMusicSound.play();


    character = new Character(game_data);
    characterinfo = game_data->json.Get_PlayerSprite();
    game_data->assets.loadTextureFromFile(characterinfo.CharacterName, characterinfo.CharacterFileName);
    character->getSprite().setTexture( game_data->assets.GetTexture(characterinfo.CharacterName) );

    wall = new Wall(game_data);
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
            character->setJump(true);
            character->Tap();
        }
        if (!game_data->window.hasFocus()) {
            _gameMusicSound.pause();
            _pauseSound.play();
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

        wall -> move_Wall(sf::Vector2f(0, move_down_by));
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

    std::vector<Obstacle*> obstacles;
    obstacles = obstacles_container->getObstacle();
    for(auto obstacle : obstacles){
        if(obstacle->getBounds().intersects(character->GetBounds())){
            character->_death = true;
        }
    }

    if (character->_death){
        _gameMusicSound.stop();
        _deathSound.play();
        game_data->machine.AddGameState(GameStateReference(new GameOverState(game_data)), true);
    }
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

void MainGameState::Resume(){
    _jumpSound.setVolume(game_data->json.Get_Soundvolume());
    _deathSound.setVolume(game_data->json.Get_Soundvolume());
    _pauseSound.setVolume(game_data->json.Get_Soundvolume());
    _gameMusicSound.setVolume(game_data->json.Get_Musicvolume());
    _gameMusicSound.play();
}