//
// Created by stephan on 18-1-2022.
//

#include "InputManager.hpp"
bool InputManager::IsKeyPressed(sf::Keyboard::Key key){
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::IsButtonPressed(sf::Mouse::Button button, sf::Mouse::Button button1) {
    return sf::Mouse::isButtonPressed(button);
}

bool InputManager::IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow window) {
    if (sf::Mouse::isButtonPressed(button)) {
        return (sprite.getGlobalBounds().contains(GetMousePosition(window)));
    }
    return false;
}

sf::Vector2f InputManager::GetMousePosition(sf::RenderWindow &window) {
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
}