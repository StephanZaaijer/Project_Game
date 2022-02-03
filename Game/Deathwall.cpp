#include "Deathwall.hpp"


Deathwall::Deathwall(GameDataReference gameData, sf::Vector2f position):
    Obstacle(identifier::deathwall),
    gameData(std::move(gameData)),
    position (position)
{
    spawn();
}

sf::Vector2f Deathwall::getPosition(){
    return deathwall.getPosition();
}

void Deathwall::spawn(){
    deathwall.setPosition(sf::Vector2f(position.x, position.y ));
    deathwall.setSize(sf::Vector2f((WALL_WIDTH/2.0f)+ 1.0f, (WALL_HEIGHT/3.0f) + 2));
    deathwall.setFillColor(gameData->json.getObstacleColor());
}

void Deathwall::move(sf::Vector2f moveBy){
    deathwall.move(moveBy);
}
void Deathwall::draw() const{
    gameData->window.draw(deathwall);
}

sf::FloatRect Deathwall::getBounds() {
    return deathwall.getGlobalBounds();
}
