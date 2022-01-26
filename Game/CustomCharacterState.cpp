#include "CustomCharacterState.hpp"
#include <utility>

CustomCharacterState::CustomCharacterState(GameDataReference data) :
        game_data(std::move(data)) {}

void CustomCharacterState::Init() {
    counter = 0;
    character = new Character(game_data);
    CurrentCharacter = game_data->json.Get_PlayerSprite();
    for (const auto &characters : CustomCharacters) {
        game_data->assets.loadTextureFromFile(characters.CharacterName, characters.CharacterFileName);
    }

    game_data->assets.loadTextureFromFile("Random Button", RANDOMBUTTON);
    game_data->assets.loadTextureFromFile("Arrow Right", ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Left", ARROW_LEFT_BUTTON);
    game_data->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);

    for (const auto& characters : CustomCharacters) {
        if (CurrentCharacter == characters) {
            break;
        }
        counter++;
    }
    if (counter > CustomCharacters.size()) {
        counter = 0;
        CurrentCharacter = CustomCharacters[counter];
    }


    character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
    character->getSprite().setPosition({SCREEN_WIDTH / 4.0f * 2.0f, SCREEN_HEIGHT / 2.0f});
    character->getSprite().setOrigin({character->getSprite().getGlobalBounds().width / 2, character->getSprite().getGlobalBounds().height / 2});
    character->getSprite().setOrigin({character->getSprite().getGlobalBounds().width / 2, character->getSprite().getGlobalBounds().height / 2});


    _backButton.setTexture(game_data->assets.GetTexture("Back Button"));
    _randomButton.setTexture(game_data->assets.GetTexture("Random Button"));
    _arrowRight.setTexture(game_data->assets.GetTexture("Arrow Right"));
    _arrowLeft.setTexture(game_data->assets.GetTexture("Arrow Left"));
    _background.setTexture(game_data->assets.GetTexture("Background"));

    _randomButton.setPosition(SCREEN_WIDTH / 5.0f * 3.0f, SCREEN_HEIGHT / 6.0f * 4.0f);
    _arrowRight.setPosition(SCREEN_WIDTH / 4.0f * 3.0f, SCREEN_HEIGHT / 2.0f);
    _arrowLeft.setPosition(SCREEN_WIDTH / 4.0f * 1.0f, SCREEN_HEIGHT / 2.0f);
    _backButton.setPosition(SCREEN_WIDTH / 5.0f * 2.0f, SCREEN_HEIGHT / 5.0f * 4.0f);

    _arrowRight.setOrigin({_arrowRight.getGlobalBounds().width / 2, _arrowRight.getGlobalBounds().height / 2});
    _backButton.setOrigin({_backButton.getGlobalBounds().width / 2, _backButton.getGlobalBounds().height / 2});
    _arrowLeft.setOrigin({_arrowLeft.getGlobalBounds().width / 2, _arrowLeft.getGlobalBounds().height / 2});
    _randomButton.setOrigin({_randomButton.getGlobalBounds().width / 2, _randomButton.getGlobalBounds().height / 2});

}

void CustomCharacterState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->json.Set_PlayerSprite(CurrentCharacter);
            game_data->window.close();
            
        }
        if (game_data->input.IsSpriteClicked(_arrowRight, sf::Mouse::Left, game_data->window)) {
            if (counter == CustomCharacters.size() - 1) {
                counter = 0;
            } else { counter += 1; }
            CurrentCharacter = CustomCharacters[counter];
            character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
        }
        if (game_data->input.IsSpriteClicked(_randomButton, sf::Mouse::Left, game_data->window)) {
            counter = std::rand() % CustomCharacters.size();
            CurrentCharacter = CustomCharacters[counter];
            character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
        }
        if (game_data->input.IsSpriteClicked(_arrowLeft, sf::Mouse::Left, game_data->window)) {
            if (counter == 0) {
                counter = CustomCharacters.size() - 1;
            } else { counter -= 1; }
            CurrentCharacter = CustomCharacters[counter];
            character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
        }
        if (game_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, game_data->window)) {
            game_data->json.Set_PlayerSprite(CurrentCharacter);
            game_data->machine.RemoveGameState();
        }
        game_data->input.ChangeMouseWhenHoveringOverButton(CharacterSelect, game_data->window);
    }
}

void CustomCharacterState::Update(float delta) {}

void CustomCharacterState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_randomButton);
    game_data->window.draw(_backButton);
    game_data->window.draw(_arrowRight);
    game_data->window.draw(_arrowLeft);
    character->Draw();
    game_data->window.display();
}
