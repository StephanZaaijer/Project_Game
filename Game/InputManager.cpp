#include "InputManager.hpp"
InputManager::InputManager() {
    arrow_cursor.loadFromSystem(sf::Cursor::Arrow);
    hand_cursor.loadFromSystem(sf::Cursor::Hand);
}


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

bool InputManager::IsRectangleClicked(const sf::RectangleShape& rectangle, const sf::Mouse::Button& button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(button)) {
        return (rectangle.getGlobalBounds().contains(GetMousePosition(window)));
    }
    return false ;
}


bool InputManager::IsMouseIntersectingSprite(const sf::Sprite& sprite, sf::RenderWindow& window) {
    return (sprite.getGlobalBounds().contains(GetMousePosition(window)));
}

bool InputManager::IsMouseIntersectingSprite(const sf::Sprite* sprite, sf::RenderWindow& window) {
    return (sprite->getGlobalBounds().contains(GetMousePosition(window)));
}

bool InputManager::ChangeMouseWhenHoveringOverButton(const std::vector<sf::Sprite*>& buttons, sf::RenderWindow& window) {
    for (const auto& button : buttons) {
        if (IsMouseIntersectingSprite(button, window)) {
            window.setMouseCursor(hand_cursor);
            return true;
        }
    }
    window.setMouseCursor(arrow_cursor);
    return false;
}

sf::Vector2f InputManager::GetMousePosition(sf::RenderWindow &window) {
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
}