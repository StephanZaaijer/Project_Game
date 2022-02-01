#include "Deathwall.hpp"


Deathwall::Deathwall(GameDataReference game_data, sf::Vector2f position):
    Obstacle(identifier::deathwall),
    game_data(std::move(game_data))
{
    deathwall.setPosition(sf::Vector2f(position.x, position.y ));
    deathwall.setSize(sf::Vector2f(WALL_WIDTH/2.0f + 1.0f, WALL_HEIGHT/3.0f));
    deathwall.setFillColor(game_data->json.Get_ObstacleColor());
}

sf::Vector2f Deathwall::getPosition(){
    return deathwall.getPosition();
}

//void Deathwall::spawn(){
//
//}

void Deathwall::move(sf::Vector2f move_by){
    deathwall.move(move_by);
}
void Deathwall::draw() const{
    game_data -> window.draw(deathwall);
}

sf::FloatRect Deathwall::getBounds() {
    return deathwall.getGlobalBounds();
}
