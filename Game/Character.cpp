#include "Character.hpp"
#include "iostream"
#include <utility>

Character::Character(GameDataReference data) : game_data(std::move(data)) {
    _characterSprite.setTexture(game_data->assets.GetTexture("character"));
//    _characterSprite.setPosition(
//            (game_data->window.getSize().x / 4) - (_characterSprite.getGlobalBounds().width / 2),
//            (game_data->window.getSize().y / 2) - (_characterSprite.getGlobalBounds().height / 2));
    _characterSprite.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _position = _characterSprite.getPosition();
    _characterState = CHARACTER_STATE_STIL;
}

void Character::Draw() {
    _characterSprite.setPosition(_position);
    game_data->window.draw(_characterSprite);
}

void Character::Update(float dt) {
    if ((_characterSprite.getPosition().x < 1) ||
        (_position.x + _characterSprite.getGlobalBounds().width) >= game_data->window.getSize().x) {
        Collide(false);
    }

    if (CHARACTER_STATE_JUMPING == _characterState) {
        _velocity.y += GRAVITY;
        _position.y += _velocity.y;
        _position.x += _velocity.x;
//        _characterSprite.move(speed * dt, -JUMPING_SPEED * dt);

    } else if (CHARACTER_STATE_STICK == _characterState) {
        _characterSprite.setPosition(_characterSprite.getPosition());
    }

//    if (_movementClock.getElapsedTime().asSeconds() > JUMP_DURATION) {
//        _movementClock.restart();
//        _characterState = CHARACTER_STATE_FALLING;
//    }
}

void Character::Tap() {
    _movementClock.restart();
    _characterState = CHARACTER_STATE_JUMPING;
    _velocity.y = -12.0;
}


//void Character::Collide(bool spike) {
//    if (spike) {
//        //go to game over state
//    } else {
//        if (_velocity.x < 0) {
//            _characterSprite.setPosition((_position.x + 3), (_position.y));
//        } else {
//            _characterSprite.setPosition((_position.x - 3), (_position.y));
//        }
//        _velocity.x *= -1;
////        _velocity.y *= -1;
//
//        while (!game_data->input.IsKeyPressed(sf::Keyboard::Space)) {
//            _characterState = CHARACTER_STATE_STICK;
//        }
////        _characterState = CHARACTER_STATE_FALLING;
//    }
//}

void Character::Collide(bool dangerous) {
    if (dangerous) {
        //ga dood aub
    } else{
        _velocity.x *= -1;
        while (!game_data->input.IsKeyPressed(sf::Keyboard::Space)) {
            _characterState = CHARACTER_STATE_STICK;
        }
        _characterState = CHARACTER_STATE_JUMPING;
//        _position = _characterSprite.getPosition();
    }
}

sf::FloatRect Character::GetBound() {
    return _characterSprite.getGlobalBounds();
}


