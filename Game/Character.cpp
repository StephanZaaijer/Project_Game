#include "Character.hpp"


Character::Character(GameDataReference data) : game_data(data) {
    _characterSprite.setTexture(game_data->assets.GetTexture("character"));
    _characterSprite.setPosition(
            (game_data->window.getSize().x / 4) - (_characterSprite.getGlobalBounds().width / 2),
            (game_data->window.getSize().y / 2) - (_characterSprite.getGlobalBounds().height / 2));
    _characterState = CHARACTER_STATE_STIL;
}

void Character::Draw() {
    game_data->window.draw(_characterSprite);
}

void Character::Update(float dt) {

    if (CHARACTER_STATE_FALLING == _characterState) {
        _characterSprite.move(speed * dt, GRAVITY * dt);
    } else if (CHARACTER_STATE_JUMPING == _characterState) {
        _characterSprite.move(speed * dt, -JUMPING_SPEED * dt);
    }else if(CHARACTER_STATE_STICK == _characterState){
        _characterSprite.setPosition(_characterSprite.getPosition());
    }

    if (_movementClock.getElapsedTime().asSeconds() > JUMP_DURATION) {
        _movementClock.restart();
        _characterState = CHARACTER_STATE_FALLING;
    }
}

void Character::Tap() {
    _movementClock.restart();
    _characterState = CHARACTER_STATE_JUMPING;
}
void Character::Collide(bool spike){
    if(spike){
        //go to game over state
    }else{
        while(!game_data->input.IsButtonPressed(sf::Mouse::Left)){
            _characterState = CHARACTER_STATE_STICK;
        }

        _characterState = CHARACTER_STATE_JUMPING;
        if (speed){
            _characterSprite.setPosition((_characterSprite.getPosition().x - 5),(_characterSprite.getPosition().y - 5));
        }else{
            _characterSprite.setPosition((_characterSprite.getPosition().x + 5),(_characterSprite.getPosition().y + 5));
        }
        speed = speed * -1;
    }
}
sf::FloatRect Character::GetBound() {
    return _characterSprite.getGlobalBounds();
}


