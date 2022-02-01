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

void Character::Tap() {
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

bool Character::CollideSpike(const std::unique_ptr<Obstacle> &spike) {
    sf::FloatRect own_hitbox = _characterSprite.getGlobalBounds();

    if(spike->getFace() == right){
        sf::Vector2f pos = spike->getPosition();
        sf::Vector2f upper_left = spike->get_point(0) + pos;
        sf::Vector2f mid_right  = spike->get_point(1) + pos;
        sf::Vector2f lower_left = spike->get_point(2) + pos;

        Line l1(upper_left, mid_right);
        Line l2(lower_left, mid_right);
        std::vector<sf::Vector2f> points_array_top = l1.get_points();
        std::vector<sf::Vector2f> points_array_bottom = l2.get_points();

        auto iterator = std::find_if(points_array_top.begin(), points_array_top.end(), [&own_hitbox](const sf::Vector2f & v) -> bool{
            return own_hitbox.contains(v);
        });

        if(iterator != points_array_top.end()){
            return true;
        }

        iterator = std::find_if(points_array_bottom.begin(), points_array_bottom.end(), [&own_hitbox](const sf::Vector2f & v) -> bool{
            return own_hitbox.contains(v);
        });

        if(iterator != points_array_bottom.end()){
            return true;
        }
    }

    if(spike->getFace() == left){
        sf::Vector2f pos = spike->getPosition();
        sf::Vector2f upper_right = spike->get_point(0) + pos;
        sf::Vector2f mid_left    = spike->get_point(1) + pos;
        sf::Vector2f lower_right = spike->get_point(2) + pos;

        Line l1(upper_right, mid_left);
        Line l2(lower_right, mid_left);
        std::vector<sf::Vector2f> points_array_top = l1.get_points();
        std::vector<sf::Vector2f> points_array_bottom = l2.get_points();


        auto iterator = std::find_if(points_array_top.begin(), points_array_top.end(), [this](const sf::Vector2f & v) -> bool{
            return _characterSprite.getGlobalBounds().contains(v);
        });

        if(iterator != points_array_top.end()){
            return true;
        }

        iterator = std::find_if(points_array_bottom.begin(), points_array_bottom.end(), [this](const sf::Vector2f & v) -> bool{
            return _characterSprite.getGlobalBounds().contains(v);
        });

        if(iterator != points_array_bottom.end()){
            return true;
        }
    }
    return false;
}





