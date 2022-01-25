#include "CustomCharacterState.hpp"

CustomCharacterState::CustomCharacterState(GameDataReference data):
        game_data (data)
{}
void CustomCharacterState::Update(float delta) {}
void CustomCharacterState::Init() {
    counter = 0;
    character = new Character(game_data);
    game_data->assets.loadTextureFromFile(character_lst[0], CHARACTER_FRAME_1_FILEPATH);
    game_data->assets.loadTextureFromFile(character_lst[1], CHARACTER_2);
    game_data->assets.loadTextureFromFile(character_lst[2], CHARACTER_3);
    game_data->assets.loadTextureFromFile("Random Button", RANDOMBUTTON);
    game_data->assets.loadTextureFromFile("Arrow Right",ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Left",ARROW_LEFT_BUTTON);
    game_data->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);

    character->getSprite().setTexture( game_data->assets.GetTexture(character_lst[counter]) );
    character->getSprite().setPosition({SCREEN_WIDTH / 4 * 2, SCREEN_HEIGHT / 2.0f});
    character->getSprite().setOrigin({character->getSprite().getGlobalBounds().width/2, character->getSprite().getGlobalBounds().height/2});
    character->getSprite().setOrigin({character->getSprite().getGlobalBounds().width/2, character->getSprite().getGlobalBounds().height/2});


    _backButton.setTexture(game_data->assets.GetTexture("Back Button"));
    _randomButton.setTexture(game_data->assets.GetTexture("Random Button"));
    _ArrowRight.setTexture(game_data->assets.GetTexture("Arrow Right"));
    _ArrowLeft.setTexture(game_data->assets.GetTexture("Arrow Left"));
    _background.setTexture(game_data->assets.GetTexture("Background"));

    _randomButton.setPosition(SCREEN_WIDTH / 5*3 ,SCREEN_HEIGHT /6*4);
    _ArrowRight.setPosition(SCREEN_WIDTH / 4*3 ,SCREEN_HEIGHT / 2.0f);
    _ArrowLeft.setPosition(SCREEN_WIDTH / 4*1,SCREEN_HEIGHT / 2.0f);
    _backButton.setPosition(SCREEN_WIDTH / 5*2 ,SCREEN_HEIGHT / 5 *4);

    _ArrowRight.setOrigin({_ArrowRight.getGlobalBounds().width/2, _ArrowRight.getGlobalBounds().height/2});
    _backButton.setOrigin({_backButton.getGlobalBounds().width/2, _backButton.getGlobalBounds().height/2});
    _ArrowLeft.setOrigin({_ArrowLeft.getGlobalBounds().width/2, _ArrowLeft.getGlobalBounds().height/2});
    _randomButton.setOrigin({_randomButton.getGlobalBounds().width/2, _randomButton.getGlobalBounds().height/2});

}
void CustomCharacterState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->window.close();
        }
        if (game_data->input.IsSpriteClicked(_ArrowRight, sf::Mouse::Left, game_data->window)) {
            if(counter == character_lst.size()-1){
                counter = 0;
            }else{ counter += 1; }
            character->getSprite().setTexture( game_data->assets.GetTexture(character_lst[counter]) );
        }
        if(game_data->input.IsSpriteClicked(_randomButton, sf::Mouse::Left, game_data->window)){
            counter = std::rand() % character_lst.size();
            character->getSprite().setTexture( game_data->assets.GetTexture(character_lst[counter]) );
        }
        if (game_data->input.IsSpriteClicked(_ArrowLeft, sf::Mouse::Left, game_data->window)) {
            if(counter == 0){
                counter = character_lst.size()-1;
            }else{ counter -= 1; }
            character->getSprite().setTexture( game_data->assets.GetTexture(character_lst[counter]) );
        }
        if (game_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, game_data->window)){
            game_data->machine.RemoveGameState();
        }
    }
    game_data->input.ChangeMouseWhenHoveringOverButton(CharacterSelect, game_data->window);
}
void CustomCharacterState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_randomButton);
    game_data->window.draw(_backButton);
    game_data->window.draw(_ArrowRight);
    game_data->window.draw(_ArrowLeft);
    character->Draw();
    game_data->window.display();
}
