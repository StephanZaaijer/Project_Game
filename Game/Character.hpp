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
    void Collide(const std::vector<sf::RectangleShape> & Rects );
    void setHeight(const int &value);
    void moveDownByOffset(const float & y);

    void setJump(const bool & set);

    int getHeight() const;

    sf::Sprite & getSprite ();

    sf::FloatRect GetBound();

    sf::Vector2f getPosition();

  
private:
    GameDataReference game_data;
    sf::Sprite _characterSprite;
    sf::Vector2f _velocity = {VELOCITY_X,0};
    sf::Vector2f _position;
    sf::Clock _clock;
    sf::Clock _movementClock;
    character_states _characterState;
    int _height = 0;
    bool jump;
};

#endif //CHARACTER_HPP