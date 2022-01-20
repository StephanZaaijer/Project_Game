#include "InputManager.hpp"
bool InputManager::IsKeyPressed(const sf::Keyboard::Key &key){
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::IsButtonPressed(const sf::Mouse::Button &button){
    return sf::Mouse::isButtonPressed(button);
}

bool InputManager::IsSpriteClicked(const sf::Sprite &sprite, const sf::Mouse::Button &button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(button)) {
        return (sprite.getGlobalBounds().contains(GetMousePosition(window)));
    }
    return false;
}

sf::Vector2f InputManager::GetMousePosition(sf::RenderWindow &window) {
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
}