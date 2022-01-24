#include "Character.hpp"
#include <utility>

Character::Character(GameDataReference data) : game_data(std::move(data)) {
    game_data->assets.loadTextureFromFile("character", CHARACTER_FRAME_1_FILEPATH);
    _characterSprite.setTexture(game_data->assets.GetTexture("character"));
    _characterSprite.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    _position = _characterSprite.getPosition();
    _characterState = character_states::Still;
}

sf::Vector2f Character::getPosition(){
    return _characterSprite.getPosition();
}

int Character::getHeight() const {
    return _height;
}

void Character::setHeight(const int & value) {
    _height = value;
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
    if(_characterSprite.getPosition().y < 0){
        _death = true;
    }

    if (character_states::Jumping == _characterState) {
        _velocity.y += GRAVITY;
        _position.y += _velocity.y;
        _position.x += _velocity.x;

        _height += (_velocity.y * -1);

    } else if (character_states::Stick == _characterState) {
        //do nothing
    }
}

void Character::Tap() {
    _movementClock.restart();
    _characterState = character_states::Jumping;
    _velocity.y = -12.0;
}

void Character::Collide(bool dangerous) {
    if (dangerous) {
        _death = true;
    } else{
        _velocity.x *= -1;
        while (!game_data->input.IsKeyPressed(sf::Keyboard::Space)) {
            _characterState = character_states::Stick;
        }
        _characterState = character_states::Jumping;
    }
}

sf::FloatRect Character::GetBound() {
    return _characterSprite.getGlobalBounds();
}
