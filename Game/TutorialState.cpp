#include "TutorialState.hpp"

TutorialState::TutorialState(GameDataReference data) :
        gameData(std::move(data)) {}

void TutorialState::Init(){
    gameData->assets.loadTextureFromFile("Tutorial", TUTORIAL);
    gameData->assets.loadSoundBufferFromFile("clickSound", SOUND_CLICK_PATH);

    tutorial.setTexture(gameData->assets.getTexture("Tutorial"));
    backButton.setTexture(gameData->assets.getTexture("Back Button"));
    background.setTexture(gameData->assets.getTexture("Background"));

    _clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    _clickSound.setVolume(gameData->json.Get_Soundvolume());

    backButton.setPosition(ScreenWidth / 6.0f * 6 - backButton.getGlobalBounds().width ,
                            SCREEN_HEIGHT - (backButton.getGlobalBounds().height * 1.1));
    tutorial.setPosition(400,100);
    tutorial.setScale(1,1);
}

void TutorialState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        if (gameData->input.ChangeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if (!prevMousestate) {
                if (gameData->input.IsSpriteClicked(backButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    gameData->machine.RemoveGameState();
                }
            }
        }
        prevMousestate = gameData->input.IsButtonPressed(sf::Mouse::Left);
    }
}
void TutorialState::Update(float delta){}
void TutorialState::Draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(tutorial);
    gameData->window.draw(backButton);
    gameData->window.display();
}