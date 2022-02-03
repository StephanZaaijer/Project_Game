#include "Character.hpp"
#include <iostream>
#include <utility>

Character::Character(GameDataReference gameData) : gameData(std::move(gameData)) {
    characterSprite.setPosition(SCREEN_WIDTH / 2.0f, CHARACTER_START_HEIGHT);
    characterSprite.setScale(CHARACTER_SCALE, CHARACTER_SCALE);
    position = characterSprite.getPosition();
    characterState = Still;
}

sf::Vector2f Character::getPosition(){
    return characterSprite.getPosition();
}

void Character::moveDownByOffset(const float & y){
    position = characterSprite.getPosition();
    position.y += y;
    characterSprite.setPosition(position);
}

int Character::getHeight() const {
    return height;
}

int Character::getScore() const {
    return score / 100;
}

void Character::addToScore(int add) {
    score += add;
}

void Character::setHeight(const int &value) {
    height = value;
}

void Character::resetJumps(){
    jumpedOnce = false;
    jumpedTwice = false;
}

void Character::setTexture(const sf::Texture& texture){
    characterSprite.setTexture(texture);
}

void Character::setScale(const float& scale) {
    characterSprite.setScale(scale, scale);
}

void Character::setPosition(const sf::Vector2f& newPosition){
    characterSprite.setPosition(newPosition);
}

sf::FloatRect Character::getGlobalBounds() {
    return characterSprite.getGlobalBounds();
}

void Character::draw() {
    gameData->window.draw(characterSprite);
}

void Character::update() {
    if ( characterState == Jumping ) {
        fallVelocity = 0;
        position = characterSprite.getPosition();
        velocity.y += GRAVITY;
        position += velocity;
        characterSprite.setPosition(position);

        height += (int(-velocity.y));
    }
    else if ( characterState == Stick ) {
        float fallRate = fallVelocity += GRAVITY / WALL_SLIDE_DELTA;
        moveDownByOffset(fallRate);
        height -= int(fallRate);
    }
}

void Character::tap() {
    if ( !isJumpPressed && !jumpedTwice) {
        if (jumpedOnce) {
            jumpedTwice = true;
        }
        else{
            jumpedOnce = true;
        }
        characterState = Jumping;
        velocity.y = VELOCITY_Y;
    }
}

void Character::collideWalls(const std::vector<sf::RectangleShape> & Rects) {
    sf::Vector2f ownPos = characterSprite.getPosition();
    sf::FloatRect ownHitbox = characterSprite.getGlobalBounds();
    sf::Vector2f arrOwnPoints[] = {sf::Vector2f(ownPos.x, ownPos.y),
                                     sf::Vector2f(ownPos.x + ownHitbox.width, ownPos.y),
                                     sf::Vector2f(ownPos.x, ownPos.y + ownHitbox.height),
                                     sf::Vector2f(ownPos.x + ownHitbox.width, ownPos.y + ownHitbox.height)};
    bool hitBottom = false;
    bool hitTop = false;
    for (const auto &rect: Rects) {
        if (rect.getGlobalBounds().intersects(ownHitbox)) {
            sf::Vector2f tPos = rect.getPosition();
            sf::FloatRect tHitbox = rect.getGlobalBounds();
            sf::Vector2f arrTargetPoints[] = {sf::Vector2f(tPos.x, tPos.y),
                                                sf::Vector2f(tPos.x + tHitbox.width, tPos.y),
                                                sf::Vector2f(tPos.x, tPos.y + tHitbox.height),
                                                sf::Vector2f(tPos.x + tHitbox.width, tPos.y + tHitbox.height)};

            if(velocity.y > 0 && velocity.x < 0){
                float distTop = arrOwnPoints[2].y - arrTargetPoints[0].y;
                float distSide = arrTargetPoints[1].x - arrOwnPoints[2].x;

                if(distTop < distSide){
                    hitTop = true;
                    characterSprite.setPosition(ownPos.x , ownPos.y - distTop);
                }
                else{
                    characterSprite.setPosition(ownPos.x + distSide, ownPos.y);
                }
            }
            else if(velocity.y > 0 && velocity.x > 0){
                float distTop = arrOwnPoints[3].y - arrTargetPoints[0].y;
                float distSide = arrOwnPoints[3].x - arrTargetPoints[0].x;

                if(distTop < distSide){
                    hitTop = true;
                    characterSprite.setPosition(ownPos.x , ownPos.y - distTop);
                }
                else{
                    characterSprite.setPosition(ownPos.x - distSide, ownPos.y);
                }
            }
            else if(velocity.y < 0 && velocity.x < 0){
                float distbottom = arrTargetPoints[3].y - arrOwnPoints[0].y;
                float distSide = arrTargetPoints[3].x - arrOwnPoints[0].x;

                if(distbottom < distSide){
                    hitBottom = true;
                    characterSprite.setPosition(ownPos.x , ownPos.y + distbottom);
                }
                else{
                    characterSprite.setPosition(ownPos.x + distSide, ownPos.y);
                }
            }
            else if(velocity.y < 0 && velocity.x > 0){
                float distbottom = arrTargetPoints[2].y - arrOwnPoints[1].y;
                float distSide = arrOwnPoints[1].x - arrTargetPoints[2].x;

                if(distbottom < distSide){
                    hitBottom = true;
                    characterSprite.setPosition(ownPos.x , ownPos.y + distbottom);
                }
                else{
                    characterSprite.setPosition(ownPos.x - distSide, ownPos.y);
                }
            }

            if(hitBottom){
                velocity.y = 0;
                characterState = Jumping;
            }
            else if (hitTop){
                characterState = Still;
                resetJumps();
            }
            else{
                velocity.x *= -1;
                characterState = Stick;
                resetJumps();
            }
        }
    }

}

void  Character::setJumpPressed(bool set) {
    isJumpPressed = set;
}

bool Character::getJumpedTwice() const {
    if(jumpedTwice){
        return false;
    } else{
        return true;
    }
}

bool Character::collideSpike(const std::unique_ptr<Obstacle> &spike) {
    sf::FloatRect ownHitbox = characterSprite.getGlobalBounds();

    if(spike->getFace() == right){
        sf::Vector2f pos = spike->getPosition();
        sf::Vector2f upperLeft = spike->getPoint(0) + pos;
        sf::Vector2f midRight  = spike->getPoint(1) + pos;
        sf::Vector2f lowerLeft = spike->getPoint(2) + pos;

        Line l1(upperLeft, midRight);
        Line l2(lowerLeft, midRight);
        std::vector<sf::Vector2f> pointsArrayTop = l1.getPoints();
        std::vector<sf::Vector2f> pointsArrayBottom = l2.getPoints();

        auto iterator = std::find_if(pointsArrayTop.begin(), pointsArrayTop.end(), [&ownHitbox](const sf::Vector2f & v)->bool{
            return ownHitbox.contains(v);
        });

        if(iterator != pointsArrayTop.end()){
            return true;
        }

        iterator = std::find_if(pointsArrayBottom.begin(), pointsArrayBottom.end(), [&ownHitbox](const sf::Vector2f & v)->bool{
            return ownHitbox.contains(v);
        });

        if(iterator != pointsArrayBottom.end()){
            return true;
        }
    }

    if(spike->getFace() == left){
        sf::Vector2f pos = spike->getPosition();
        sf::Vector2f upperRight = spike->getPoint(0) + pos;
        sf::Vector2f midLeft    = spike->getPoint(1) + pos;
        sf::Vector2f lowerRight = spike->getPoint(2) + pos;

        Line l1(upperRight, midLeft);
        Line l2(lowerRight, midLeft);
        std::vector<sf::Vector2f> pointsArrayTop = l1.getPoints();
        std::vector<sf::Vector2f> pointsArrayBottom = l2.getPoints();

        auto iterator = std::find_if(pointsArrayTop.begin(), pointsArrayTop.end(), [this](const sf::Vector2f & v)->bool{
            return characterSprite.getGlobalBounds().contains(v);
        });

        if(iterator != pointsArrayTop.end()){
            return true;
        }

        iterator = std::find_if(pointsArrayBottom.begin(), pointsArrayBottom.end(), [this](const sf::Vector2f & v)->bool{
            return characterSprite.getGlobalBounds().contains(v);
        });

        if(iterator != pointsArrayBottom.end()){
            return true;
        }
    }
    return false;
}





