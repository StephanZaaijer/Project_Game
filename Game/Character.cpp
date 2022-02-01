#include "Character.hpp"
#include <iostream>
#include <utility>

Character::Character(GameDataReference data) : game_data(std::move(data)) {
    _characterSprite.setPosition(SCREEN_WIDTH / 2.0f, CHARACTER_START_HEIGHT);
    _characterSprite.setScale(CHARACTER_SCALE, CHARACTER_SCALE);
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

int Character::getScore() const {
    return _score / 100;
}

void Character::addToScore(int add) {
    _score += add;
}

void Character::setHeight(const int &value) {
    _height = value;
}

void Character::resetJumps(){
    _jumped_once = false;
    _jumped_twice = false;
}

sf::Sprite & Character::getSprite() {
    return _characterSprite;
}

sf::FloatRect Character::GetBounds() {
    return _characterSprite.getGlobalBounds();
}

void Character::Draw() {
    game_data->window.draw(_characterSprite);
}

void Character::Update(float dt) {
    if ( _characterState == Jumping ) {
        _fallVelocity = 0;
        _position = _characterSprite.getPosition();
        _velocity.y += GRAVITY;
        _position += _velocity;
        _characterSprite.setPosition(_position);

        _height += (int(_velocity.y) * -1);
    }
    else if ( _characterState == Stick ) {
        float fallRate = _fallVelocity += GRAVITY / WALL_SLIDE_DELTA;
        moveDownByOffset(fallRate);
        _height -= int(fallRate);
    }

    if(_characterSprite.getPosition().y >SCREEN_HEIGHT){
        _death = true;
    }
}

void Character::Tap() { // with spacebar release implemented
    if ( !isJumpPressed && !_jumped_twice) {
        if (_jumped_once) {
            _jumped_twice = true;
        }
        else{
            _jumped_once = true;
        }
        _characterState = Jumping;
        _velocity.y = VELOCITY_Y;
    }
    else {}
}

void Character::CollideWalls(const std::vector<sf::RectangleShape> & Rects) {

    sf::Vector2f own_pos = _characterSprite.getPosition();
    sf::FloatRect own_hitbox = _characterSprite.getGlobalBounds();
    sf::Vector2f arr_own_points[] = {sf::Vector2f(own_pos.x, own_pos.y),
                                     sf::Vector2f(own_pos.x + own_hitbox.width, own_pos.y),
                                     sf::Vector2f(own_pos.x, own_pos.y + own_hitbox.height),
                                     sf::Vector2f(own_pos.x + own_hitbox.width, own_pos.y + own_hitbox.height)};
    bool hit_bottom = false;
    bool hit_top = false;
    for (const auto &rect: Rects) {

        if (rect.getGlobalBounds().intersects(own_hitbox)) {
            sf::Vector2f t_pos = rect.getPosition();
            sf::FloatRect t_hitbox = rect.getGlobalBounds();
            sf::Vector2f arr_target_points[] = {sf::Vector2f(t_pos.x, t_pos.y),
                                                sf::Vector2f(t_pos.x + t_hitbox.width, t_pos.y),
                                                sf::Vector2f(t_pos.x, t_pos.y + t_hitbox.height),
                                                sf::Vector2f(t_pos.x + t_hitbox.width, t_pos.y + t_hitbox.height)};

            if(_velocity.y > 0 && _velocity.x < 0){
                float dist_top = arr_own_points[2].y - arr_target_points[0].y;
                float dist_side = arr_target_points[1].x - arr_own_points[2].x;

                if(dist_top < dist_side){
                    hit_top = true;
                    _characterSprite.setPosition(own_pos.x , own_pos.y - dist_top);
                }
                else{
                    _characterSprite.setPosition(own_pos.x + dist_side, own_pos.y);
                }
            }
            else if(_velocity.y > 0 && _velocity.x > 0){
                float dist_top = arr_own_points[3].y - arr_target_points[0].y;
                float dist_side = arr_own_points[3].x - arr_target_points[0].x;

                if(dist_top < dist_side){
                    hit_top = true;
                    _characterSprite.setPosition(own_pos.x , own_pos.y - dist_top);
                }
                else{
                    _characterSprite.setPosition(own_pos.x - dist_side, own_pos.y);
                }
            }
            else if(_velocity.y < 0 && _velocity.x < 0){
                float dist_bottom = arr_target_points[3].y - arr_own_points[0].y;
                float dist_side = arr_target_points[3].x - arr_own_points[0].x;

                if(dist_bottom < dist_side){
                    hit_bottom = true;
                    _characterSprite.setPosition(own_pos.x , own_pos.y + dist_bottom);
                }
                else{
                    _characterSprite.setPosition(own_pos.x + dist_side, own_pos.y);
                }
            }
            else if(_velocity.y < 0 && _velocity.x > 0){
                float dist_bottom = arr_target_points[2].y - arr_own_points[1].y;
                float dist_side = arr_own_points[1].x - arr_target_points[2].x;

                if(dist_bottom < dist_side){
                    hit_bottom = true;
                    _characterSprite.setPosition(own_pos.x , own_pos.y + dist_bottom);
                }
                else{
                    _characterSprite.setPosition(own_pos.x - dist_side, own_pos.y);
                }
            }


            if(hit_bottom){
                _velocity.y = 0;
                _characterState = Jumping;
            }
            else if (hit_top){
                _characterState = Still;
                resetJumps();
            }
            else{
                _velocity.x *= -1;
                _characterState = Stick;
                resetJumps();
            }
        }
    }

}

void  Character::setJumpPressed(bool set) {
    isJumpPressed = set;
}

bool Character::getJumpedTwice() {
    if(_jumped_twice){
        return false;
    } else{
        return true;
    }

}




