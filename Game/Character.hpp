#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"
#include "GameOverState.hpp"

class Character {
public:
    Character(GameDataReference data);

    void Draw();
    void Update(float dt);
    void Tap();
    void Collide(bool spike);
    void setHeight(const int &value);
    void moveDownByOffset(const float & y);

    int getHeight() const;

    bool _death = false;

    sf::Sprite & getSpriteToChange();

    sf::FloatRect GetBound();

    sf::Vector2f getPosition();

  
private:
    GameDataReference game_data;
    sf::Sprite _characterSprite;
    sf::Vector2f _velocity = {10,0};
    sf::Vector2f _position;
    sf::Clock _clock;
    sf::Clock _movementClock;
    character_states _characterState;
    int _height = 0;
};

#endif //CHARACTER_HPP