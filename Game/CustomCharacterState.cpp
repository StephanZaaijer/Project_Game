#include "CustomCharacterState.hpp"

CustomCharacterState::CustomCharacterState(GameDataReference data):
        game_data (data)
{}
void CustomCharacterState::Update(float delta) {}
void CustomCharacterState::Init() {
    character = new Character(game_data);
    game_data->assets.loadTextureFromFile("character", CHARACTER_FRAME_1_FILEPATH);
    game_data->assets.loadTextureFromFile("Arrow Right",ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Left",ARROW_LEFT_BUTTON);

    character->getSpriteToChange().setTexture( game_data->assets.GetTexture("character") );
    character->setPosition({SCREEN_WIDTH / 4 * 2, SCREEN_HEIGHT / 2.0f});
    character->getSpriteToChange().setOrigin({character->getSpriteToChange().getGlobalBounds().width/2, character->getSpriteToChange().getGlobalBounds().height/2});
    character->getSpriteToChange().setOrigin({character->getSpriteToChange().getGlobalBounds().width/2, character->getSpriteToChange().getGlobalBounds().height/2});

    _ArrowRight.setTexture(game_data->assets.GetTexture("Arrow Right"));
    _ArrowLeft.setTexture(game_data->assets.GetTexture("Arrow Left"));
    _background.setTexture(game_data->assets.GetTexture("Background"));
    _ArrowRight.setPosition(SCREEN_WIDTH / 4*3 ,SCREEN_HEIGHT / 2.0f);
    _ArrowRight.setOrigin({_ArrowRight.getGlobalBounds().width/2, _ArrowRight.getGlobalBounds().height/2});
    _ArrowLeft.setOrigin({_ArrowLeft.getGlobalBounds().width/2, _ArrowLeft.getGlobalBounds().height/2});
    _ArrowLeft.setPosition(SCREEN_WIDTH / 4*1,SCREEN_HEIGHT / 2.0f);
}
void CustomCharacterState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
        if (game_data->input.IsSpriteClicked(_ArrowRight, sf::Mouse::Left, game_data->window)) {}
        if (game_data->input.IsSpriteClicked(_ArrowLeft, sf::Mouse::Left, game_data->window)) {}
    }
    game_data->input.ChangeMouseWhenHoveringOverButton(CharacterSelect, game_data->window);
}
void CustomCharacterState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_ArrowRight);
    game_data->window.draw(_ArrowLeft);
    character->Draw();
    game_data->window.display();
}
