#ifndef PROJECT_GAME_INPUTMANAGER_HPP
#define PROJECT_GAME_INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

class InputManager {
public:
    bool IsKeyPressed(const sf::Keyboard::Key &key);
    bool IsButtonPressed(const sf::Mouse::Button &button);
    bool IsSpriteClicked(const sf::Sprite &sprite, const sf::Mouse::Button &button, sf::RenderWindow &window);
    sf::Vector2f GetMousePosition(sf::RenderWindow &window);
};


#endif //PROJECT_GAME_INPUTMANAGER_HPP
