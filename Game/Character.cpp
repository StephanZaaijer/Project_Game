#include "Character.hpp"
#include <iostream>

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
    if(_characterSprite.getPosition().x < 1 || game_data->window.getSize().x <_characterSprite.getPosition().x + _characterSprite.getGlobalBounds().width ){
        Collide(false);
    }
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

        if (speed){
            _characterSprite.setPosition((_characterSprite.getPosition().x - 2),(_characterSprite.getPosition().y));
        }else{
            _characterSprite.setPosition((_characterSprite.getPosition().x + 2),(_characterSprite.getPosition().y));
        }
        speed = speed * -1;

        while(!game_data->input.IsButtonPressed(sf::Mouse::Left)){
            _characterState = CHARACTER_STATE_STICK;
        }
        _characterState = CHARACTER_STATE_FALLING;

    }
}
sf::FloatRect Character::GetBound() {
    return _characterSprite.getGlobalBounds();
}


