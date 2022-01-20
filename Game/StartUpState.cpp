#include "StartUpState.hpp"

StarUpState::StarUpState(GameDataReference data) : game_data(data) {}

void StarUpState::Init() {
    game_data->assets.loadTextureFromFile("StartUp State Background", BACKGROUND_PATH);
    game_data->assets.loadTextureFromFile("StartUp State Image", GAME_IMAGE_PATH);
    game_data->assets.loadTextureFromFile("StartUp State Banner", GAME_TITLE_PATH);
    game_data->assets.loadTextureFromFile("StartUp State groep6 Banner", GROEP_6_BANNER);

    _background.setTexture(this->game_data->assets.GetTexture("StartUp State Background"));
    _logo.setTexture(this->game_data->assets.GetTexture("StartUp State Image"));
    _title.setTexture(this->game_data->assets.GetTexture("StartUp State Banner"));
    _banner.setTexture(this->game_data->assets.GetTexture("StartUp State groep6 Banner"));

    _title.setPosition({(SCREEN_WIDTH/2 - (_title.getGlobalBounds().width/2)), _title.getGlobalBounds().height/2});
    _logo.setPosition({SCREEN_WIDTH/2, SCREEN_HEIGHT/2});
    _banner.setPosition((SCREEN_WIDTH/2 - (_banner.getGlobalBounds().width/2)), SCREEN_HEIGHT - _banner.getGlobalBounds().height*1.5);
}

void StarUpState::HandleInput() {
    sf::Event event;

    while (game_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            game_data->window.close();
        }
    }
}

void StarUpState::Update(float delta) {
    if (_clock.getElapsedTime().asSeconds() > START_UP_TIME) {
        std::cout << "Go to Main Menu" << std::endl;
        game_data->machine.AddGameState(GameStateReference(new MainMenuState(game_data)), true);
    }
}

void StarUpState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_title);
    game_data->window.draw(_logo);
    game_data->window.draw(_banner);
    game_data->window.display();
}