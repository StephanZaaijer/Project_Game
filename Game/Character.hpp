#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"

class Character{
public:
        Character(GameDataReference data);
        void Draw();
        void Update(float dt);
        void Collide(bool spike);
        void Tap();
        sf::FloatRect GetBound();
        sf::Vector2f getPosition();

        int getHeight();
        void setHeight(const int & value);

private:
        GameDataReference game_data;
        sf::Sprite _characterSprite;
        sf::Vector2f _velocity = {5,0};
        sf::Vector2f _position;
        sf::Clock _clock;
        sf::Clock _movementClock;
        character_states _characterState;
        int height;
};

#endif //CHARACTER_HPP