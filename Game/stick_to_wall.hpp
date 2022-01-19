
#ifndef STICK_TO_WALL_HPP
#define STICK_TO_WALL_HPP

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Game.hpp"

class stick_to_wall: public GameState{
public:
        stick_to_wall(GameDataReference data);
        void Draw();
private:
        GameDataReference game_data;
        sf::Sprite _characterSprite;
};

#endif //STICK_TO_WALL_HPP