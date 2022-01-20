#ifndef PROJECT_GAME_INPUTMANAGER_HPP
#define PROJECT_GAME_INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>

class InputManager {
    bool IsButtonPressed(sf::Sprite object, sf::Keyboard::Key key);
    sf::Vector2f GetMousePosition(sf::RenderWindow &window);
};


#endif //PROJECT_GAME_INPUTMANAGER_HPP
