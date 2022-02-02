#include "TutorialState.hpp"

TutorialState::TutorialState(GameDataReference data) :
        game_data(std::move(data)) {}

void TutorialState::Init(){
    game_data->assets.loadTextureFromFile("Tutorial", TUTORIAL);
    game_data->assets.loadSoundBufferFromFile("clickSound", SOUND_CLICK_PATH);

    tutorial.setTexture(game_data->assets.getTexture("Tutorial"));
    backButton.setTexture(game_data->assets.getTexture("Back Button"));
    background.setTexture(game_data->assets.getTexture("Background"));

    _clickSound.setBuffer(game_data->assets.getSoundBuffer("clickSound"));
    _clickSound.setVolume(game_data->json.Get_Soundvolume());

    backButton.setPosition(SCREEN_WIDTH / 6.0f * 6 - backButton.getGlobalBounds().width ,
                            SCREEN_HEIGHT - (backButton.getGlobalBounds().height * 1.1));
    tutorial.setPosition(400,100);
    tutorial.setScale(1,1);
}

void TutorialState::handleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
        if (game_data->input.ChangeMouseWhenHoveringOverButton(clickableButtons, game_data->window)) {
            if (!prevMousestate) {
                if (game_data->input.IsSpriteClicked(backButton, sf::Mouse::Left, game_data->window)) {
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
    game_data->window.draw(background);
    game_data->window.draw(tutorial);
    game_data->window.draw(backButton);
    game_data->window.display();
}