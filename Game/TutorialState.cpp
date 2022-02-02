#include "TutorialState.hpp"

TutorialState::TutorialState(GameDataReference gameData) :
        gameData(std::move(gameData)) {}

void TutorialState::init(){
    gameData->assets.loadTextureFromFile("Tutorial", TUTORIAL);
    gameData->assets.loadSoundBufferFromFile("clickSound", SOUND_CLICK_PATH);

    tutorial.setTexture(gameData->assets.getTexture("Tutorial"));
    backButton.setTexture(gameData->assets.getTexture("Back Button"));
    background.setTexture(gameData->assets.getTexture("Background"));

    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    clickSound.setVolume(gameData->json.getSoundVolume());

    backButton.setPosition(SCREEN_WIDTH / 6.0f * 6 - backButton.getGlobalBounds().width ,
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
        if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if (!prevMouseState) {
                if (gameData->input.isSpriteClicked(backButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.RemoveGameState();
                }
            }
        }
        prevMouseState = gameData->input.isButtonPressed(sf::Mouse::Left);
    }
}
void TutorialState::update(float delta){}
void TutorialState::draw(float delta) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(tutorial);
    gameData->window.draw(backButton);
    gameData->window.display();
}