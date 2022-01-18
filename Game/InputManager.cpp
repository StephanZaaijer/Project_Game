//
// Created by stephan on 18-1-2022.
//

#include "InputManager.hpp"
bool InputManager::IsButtonPressed(sf::Sprite object, sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

sf::Vector2f InputManager::GetMousePosition(sf::RenderWindow &window) {
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
}