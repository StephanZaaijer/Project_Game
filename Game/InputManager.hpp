#ifndef PROJECT_GAME_INPUTMANAGER_HPP
#define PROJECT_GAME_INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>

class InputManager {
public:
    bool IsKeyPressed(sf::Keyboard::Key key);
    bool IsButtonPressed(sf::Mouse::Button button);
    bool IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window);
    sf::Vector2f GetMousePosition(sf::RenderWindow &window);
};


#endif //PROJECT_GAME_INPUTMANAGER_HPP
