#include "CustomCharacterState.hpp"

void CustomCharacterState::Update(float delta) {}
void CustomCharacterState::Init() {
    game_data->assets.loadTextureFromFile("Arrow Right",ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Left",ARROW_LEFT_BUTTON);

    _ArrowRight.setTexture(game_data->assets.GetTexture("Arrow Right"));
    _ArrowLeft.setTexture(game_data->assets.GetTexture("Arrow Left"));
    _ArrowRight.setPosition(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 8.0f);
    _ArrowLeft.setPosition(SCREEN_WIDTH / 4.0f,SCREEN_HEIGHT / 8.0f);
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
    game_data->window.draw(_ArrowRight);
    game_data->window.draw(_ArrowLeft);
    game_data->window.display();
}
