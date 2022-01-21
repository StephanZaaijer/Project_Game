#include "Wall.hpp"

Wall::Wall(GameDataReference data):
    game_data (data)
{}

void Wall::spawn_Wall(){
    sf::RectangleShape* rectangle = new sf::RectangleShape();
    rectangle->setSize(sf::Vector2f(30, 250));
    rectangle->setPosition(sf::Vector2f(
            SCREEN_WIDTH / 2 - rectangle->getSize().x / 2,
            0 - rectangle->getSize().y));
    rectangle->setFillColor(sf::Color::White);
    walls.push_back(rectangle);
}

void Wall::move_Wall(sf::Vector2f new_position){
    for(unsigned int i = 0; i < walls.size(); i++){
        walls[i]->move(new_position);
    }
}

void Wall::draw_Wall(){
    for(unsigned int i = 0; i < walls.size(); i++){
        game_data->window.draw(*walls[i]);
    }
}
std::vector<sf::RectangleShape*> & Wall::GetWall() {
    return walls;
}