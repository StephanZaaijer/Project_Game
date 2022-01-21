#include "Character.hpp"






Character::Character(GameDataReference data): game_data(data){
    _characterSprite.setTexture(game_data->assets.GetTexture("character"));
    _characterSprite.setPosition(
            (game_data->window.getSize().x/2)-(_characterSprite.getGlobalBounds().width/2),
            (game_data->window.getSize().y/4)-(_characterSprite.getGlobalBounds().height/2));
    _characterState = CHARACTER_STATE_STIL;
}
void Character::Draw() {
    game_data->window.draw(_characterSprite);
    game_data->window.display();
}
void Character::Update(float dt) {
    if (CHARACTER_STATE_FALLING == _characterState){
        _characterSprite.move(0, GRAVITY * dt);
    }
    else if( CHARACTER_STATE_JUMPING == _characterState){
        _characterSprite.move(0, -JUMPING_SPEED * dt );
    }

    if(_movementClock.getElapsedTime().asSeconds() > JUMP_DURATION){
        _movementClock.restart();
        _characterState = CHARACTER_STATE_FALLING;
    }
}
void Character::Tap() {
        _movementClock.restart();
        _characterState = CHARACTER_STATE_JUMPING;
}
sf::Sprite Character::GetSprite() {
    return _characterSprite;
}

