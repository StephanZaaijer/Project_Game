#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Line.hpp"
#include "Obstacle.hpp"
#include "Definitions.hpp"
#include "Game.hpp"
#include "GameOverState.hpp"

class Character {
public:
    Character(GameDataReference gameData);

    void draw();
    void update();
    void tap();
    void collideWalls(const std::vector<sf::RectangleShape> & Rects );
    bool collideSpike(const std::unique_ptr<Obstacle> & spike);
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
    bool death = false;

private:
    GameDataReference gameData;
    sf::Sprite characterSprite;
    sf::Vector2f velocity = {VELOCITY_X,0};
    sf::Vector2f position;
    character_states characterState;
    float fallVelocity = 0;
    int height = SCREEN_HEIGHT - CHARACTER_START_HEIGHT;
    int score = 0;
    bool jumpedOnce = false;
    bool jumpedTwice = false;
    bool isJumpPressed = false;
};

#endif //CHARACTER_HPP
