#include "TutorialState.hpp"

TutorialState::TutorialState(GameDataReference data) :
        game_data(std::move(data)) {}

void TutorialState::Init(){
    game_data->assets.loadTextureFromFile("Tutorial", TUTORIAL);
    tutorial.setTexture(game_data->assets.GetTexture("Tutorial"));

    _backButton.setTexture(game_data->assets.GetTexture("Back Button"));


    _background.setTexture(game_data->assets.GetTexture("Background"));
    _backButton.setPosition(SCREEN_WIDTH / 2.0f - (_backButton.getGlobalBounds().width / 2),
                            SCREEN_HEIGHT - (_backButton.getGlobalBounds().height * 1.1));
    tutorial.setPosition(200,0);
    tutorial.setScale(1.5,1);
}

void TutorialState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
        if (game_data->input.ChangeMouseWhenHoveringOverButton(ClickableButtons, game_data->window)) {
            if (!prevMousestate) {
                if (game_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    game_data->machine.RemoveGameState();
                }
            }
        }
        prevMousestate = game_data->input.IsButtonPressed(sf::Mouse::Left);
    }
}
void TutorialState::Update(float delta){}
void TutorialState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(tutorial);
    game_data->window.draw(_backButton);
    game_data->window.display();
}