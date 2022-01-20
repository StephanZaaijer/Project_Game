
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
        void Tap();
        sf::Sprite GetSprite();


private:
        GameDataReference game_data;
        sf::Sprite _characterSprite;

        sf::Clock _clock;
        sf::Clock _movementClock;

        int _characterState;
};

#endif //CHARACTER_HPP