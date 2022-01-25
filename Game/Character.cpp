#include "Character.hpp"
#include <iostream>
#include <utility>

Character::Character(GameDataReference data) : game_data(std::move(data)) {
    _characterSprite.setPosition(SCREEN_WIDTH / 2.0f, CHARACTER_START_HEIGHT);
    _position = _characterSprite.getPosition();
    _characterState = Still;
}

sf::Vector2f Character::getPosition(){
    return _characterSprite.getPosition();
}


void Character::moveDownByOffset(const float & y){
    _position.y += y;
}

int Character::getHeight() const {
    return _height;
}

void Character::setHeight(const int &value) {
    _height = value;
}

void Character::setJump(const bool & set){
    jump = set;
}

sf::Sprite & Character::getSpriteToChange() {
    return _characterSprite;
}


void Character::Draw() {
    game_data->window.draw(_characterSprite);
}

void Character::Update(float dt) {
    if ( _characterState == Jumping ) {

        // TELEPORT JUMP WITH CHARACTER SPRITE POSITION CHANGE
//        sf::Vector2f pos = _characterSprite.getPosition();
//        _velocity.y += GRAVITY;
//        pos.y += _velocity.y;
//        pos.x += _velocity.x;
//        _characterSprite.setPosition(pos);

        // BLOB JUMP
//        _velocity.y += GRAVITY;
//
////        std::cout << _characterSprite.getPosition().y << "\t" << _position.y << "\n";
//        _position.y = _characterSprite.getPosition().y;
//        _position.x = _characterSprite.getPosition().x;
//        _position.y += _velocity.y ;
//        _position.x += _velocity.x ;

        // TELEPORT JUMP
//        std::cout << "update values" << "\n";
        _velocity.y += GRAVITY;
        _position.y += _velocity.y;
        _position.x += _velocity.x;
        _characterSprite.setPosition(_position);



        _height += (_velocity.y * -1);

    }
    else if ( _characterState == Stick ) {
    }
}

void Character::Tap() {
//    std::cout << "tap()" << "\n";
    _movementClock.restart();
    _characterState = Jumping;
    _velocity.y = VELOCITY_Y;
//    _position = _characterSprite.getPosition();
}

void Character::Collide(bool dangerous) {
    _velocity.x *= -1;
    _characterState = Stick;
}

sf::FloatRect Character::GetBound() {
    return _characterSprite.getGlobalBounds();
}
