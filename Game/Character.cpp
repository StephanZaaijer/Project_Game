#include "Character.hpp"
#include <iostream>
#include <utility>

Character::Character(GameDataReference data) : gameData(std::move(data)) {
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

sf::Sprite & Character::getSprite() {
    return characterSprite;
}

sf::FloatRect Character::GetBounds() {
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

        height += (int(velocity.y) * -1);
    }
    else if ( characterState == Stick ) {
        float fallRate = fallVelocity += GRAVITY / WALL_SLIDE_DELTA;
        moveDownByOffset(fallRate);
        height -= int(fallRate);
    }

    if(characterSprite.getPosition().y >SCREEN_HEIGHT){
        death = true;
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

    sf::Vector2f ownpos = characterSprite.getPosition();
    sf::FloatRect ownhitbox = characterSprite.getGlobalBounds();
    sf::Vector2f arrownpoints[] = {sf::Vector2f(ownpos.x, ownpos.y),
                                     sf::Vector2f(ownpos.x + ownhitbox.width, ownpos.y),
                                     sf::Vector2f(ownpos.x, ownpos.y + ownhitbox.height),
                                     sf::Vector2f(ownpos.x + ownhitbox.width, ownpos.y + ownhitbox.height)};
    bool hitbottom = false;
    bool hittop = false;
    for (const auto &rect: Rects) {

        if (rect.getGlobalBounds().intersects(ownhitbox)) {
            sf::Vector2f tpos = rect.getPosition();
            sf::FloatRect thitbox = rect.getGlobalBounds();
            sf::Vector2f arrtargetpoints[] = {sf::Vector2f(tpos.x, tpos.y),
                                                sf::Vector2f(tpos.x + thitbox.width, tpos.y),
                                                sf::Vector2f(tpos.x, tpos.y + thitbox.height),
                                                sf::Vector2f(tpos.x + thitbox.width, tpos.y + thitbox.height)};

            if(velocity.y > 0 && velocity.x < 0){
                float disttop = arrownpoints[2].y - arrtargetpoints[0].y;
                float distside = arrtargetpoints[1].x - arrownpoints[2].x;

                if(disttop < distside){
                    hittop = true;
                    characterSprite.setPosition(ownpos.x , ownpos.y - disttop);
                }
                else{
                    characterSprite.setPosition(ownpos.x + distside, ownpos.y);
                }
            }
            else if(velocity.y > 0 && velocity.x > 0){
                float disttop = arrownpoints[3].y - arrtargetpoints[0].y;
                float distside = arrownpoints[3].x - arrtargetpoints[0].x;

                if(disttop < distside){
                    hittop = true;
                    characterSprite.setPosition(ownpos.x , ownpos.y - disttop);
                }
                else{
                    characterSprite.setPosition(ownpos.x - distside, ownpos.y);
                }
            }
            else if(velocity.y < 0 && velocity.x < 0){
                float distbottom = arrtargetpoints[3].y - arrownpoints[0].y;
                float distside = arrtargetpoints[3].x - arrownpoints[0].x;

                if(distbottom < distside){
                    hitbottom = true;
                    characterSprite.setPosition(ownpos.x , ownpos.y + distbottom);
                }
                else{
                    characterSprite.setPosition(ownpos.x + distside, ownpos.y);
                }
            }
            else if(velocity.y < 0 && velocity.x > 0){
                float distbottom = arrtargetpoints[2].y - arrownpoints[1].y;
                float distside = arrownpoints[1].x - arrtargetpoints[2].x;

                if(distbottom < distside){
                    hitbottom = true;
                    characterSprite.setPosition(ownpos.x , ownpos.y + distbottom);
                }
                else{
                    characterSprite.setPosition(ownpos.x - distside, ownpos.y);
                }
            }


            if(hitbottom){
                velocity.y = 0;
                characterState = Jumping;
            }
            else if (hittop){
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

bool Character::getJumpedTwice() {
    if(jumpedTwice){
        return false;
    } else{
        return true;
    }

}

bool Character::collideSpike(const std::unique_ptr<Obstacle> &spike) {
    sf::FloatRect ownhitbox = characterSprite.getGlobalBounds();

    if(spike->getFace() == right){
        sf::Vector2f pos = spike->getPosition();
        sf::Vector2f upperleft = spike->get_point(0) + pos;
        sf::Vector2f midright  = spike->get_point(1) + pos;
        sf::Vector2f lowerleft = spike->get_point(2) + pos;

        Line l1(upperleft, midright);
        Line l2(lowerleft, midright);
        std::vector<sf::Vector2f> pointsarraytop = l1.get_points();
        std::vector<sf::Vector2f> pointsarraybottom = l2.get_points();

        auto iterator = std::find_if(pointsarraytop.begin(), pointsarraytop.end(), [&ownhitbox](const sf::Vector2f & v) -> bool{
            return ownhitbox.contains(v);
        });

        if(iterator != pointsarraytop.end()){
            return true;
        }

        iterator = std::find_if(pointsarraybottom.begin(), pointsarraybottom.end(), [&ownhitbox](const sf::Vector2f & v) -> bool{
            return ownhitbox.contains(v);
        });

        if(iterator != pointsarraybottom.end()){
            return true;
        }
    }

    if(spike->getFace() == left){
        sf::Vector2f pos = spike->getPosition();
        sf::Vector2f upperright = spike->get_point(0) + pos;
        sf::Vector2f midleft    = spike->get_point(1) + pos;
        sf::Vector2f lowerright = spike->get_point(2) + pos;

        Line l1(upperright, midleft);
        Line l2(lowerright, midleft);
        std::vector<sf::Vector2f> pointsarraytop = l1.getPoints();
        std::vector<sf::Vector2f> pointsarraybottom = l2.getPoints();


        auto iterator = std::find_if(pointsarraytop.begin(), pointsarraytop.end(), [this](const sf::Vector2f & v) -> bool{
            return characterSprite.getGlobalBounds().contains(v);
        });

        if(iterator != pointsarraytop.end()){
            return true;
        }

        iterator = std::find_if(pointsarraybottom.begin(), pointsarraybottom.end(), [this](const sf::Vector2f & v) -> bool{
            return characterSprite.getGlobalBounds().contains(v);
        });

        if(iterator != pointsarraybottom.end()){
            return true;
        }
    }
    return false;
}





