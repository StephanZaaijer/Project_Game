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
    void CollideWalls(const std::vector<sf::RectangleShape> & Rects );
    void setHeight(const int &value);
    void moveDownByOffset(const float & y);
    void resetJumps();
    int getHeight() const;
    int getScore() const;
    void addToScore(int add);
    sf::Sprite & getSprite ();
    sf::FloatRect GetBounds();
    sf::Vector2f getPosition();
    void setJumpPressed(bool set);
    bool getJumpedTwice();
    bool _death = false;

private:
    GameDataReference game_data;
    sf::Sprite _characterSprite;
    sf::Vector2f _velocity = {VELOCITY_X,0};
    sf::Vector2f _position;
    character_states _characterState;
    float _fallVelocity = 0;
    int _height = SCREEN_HEIGHT - CHARACTER_START_HEIGHT;
    int _score = 0;
    bool _jumped_once = false;
    bool _jumped_twice = false;
    bool isJumpPressed = false;
};

#endif //CHARACTER_HPP