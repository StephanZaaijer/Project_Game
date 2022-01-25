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
    _position = _characterSprite.getPosition();
    _position.y += y;
    _characterSprite.setPosition(_position);
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

sf::Sprite & Character::getSprite() {
    return _characterSprite;
}

sf::FloatRect Character::GetBound() {
    return _characterSprite.getGlobalBounds();
}


void Character::Draw() {
    game_data->window.draw(_characterSprite);
}

void Character::Update(float dt) {
    if ( _characterState == Jumping ) {

        _position = _characterSprite.getPosition();
        _velocity.y += GRAVITY;
        _position += _velocity;
        _characterSprite.setPosition(_position);

        _height += (_velocity.y * -1);

    }
    else if ( _characterState == Stick ) {
    }
}

void Character::Tap() {
    _characterState = Jumping;
    _velocity.y = VELOCITY_Y;
}

void Character::Collide(const std::vector<sf::RectangleShape> & Rects) {

    sf::Vector2f own_pos = _characterSprite.getPosition();
    sf::FloatRect own_hitbox = _characterSprite.getGlobalBounds();
    sf::Vector2f arr_own_points[] = {sf::Vector2f(own_pos.x, own_pos.y),
                                     sf::Vector2f(own_pos.x + own_hitbox.width, own_pos.y),
                                     sf::Vector2f(own_pos.x, own_pos.y + own_hitbox.height),
                                     sf::Vector2f(own_pos.x + own_hitbox.width, own_pos.y + own_hitbox.height)};

    for (const auto &rect: Rects) {

        if (rect.getGlobalBounds().intersects(own_hitbox)) {
            sf::Vector2f t_pos = rect.getPosition();
            sf::FloatRect t_hitbox = rect.getGlobalBounds();
            sf::Vector2f arr_target_points[] = {sf::Vector2f(t_pos.x, t_pos.y),
                                                sf::Vector2f(t_pos.x + t_hitbox.width, t_pos.y),
                                                sf::Vector2f(t_pos.x, t_pos.y + t_hitbox.height),
                                                sf::Vector2f(t_pos.x + t_hitbox.width, t_pos.y + t_hitbox.height)};

            if (_velocity.x < 0) {
                float dist = (arr_target_points[1].x - arr_own_points[0].x);
                _characterSprite.setPosition(own_pos.x + dist, own_pos.y);

            } else {
                float dist = (arr_own_points[1].x - arr_target_points[0].x);
                _characterSprite.setPosition(own_pos.x - dist, own_pos.y);
            }

            _velocity.x *= -1;
            _characterState = Stick;
        }
    }

}

