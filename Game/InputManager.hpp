#ifndef PROJECT_GAME_INPUTMANAGER_HPP
#define PROJECT_GAME_INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include <vector>

class InputManager {
private:
    sf::Cursor handCursor;
    sf::Cursor arrowCursor;
public:
    InputManager();
    bool isKeyPressed(const sf::Keyboard::Key &key);
    bool isButtonPressed(const sf::Mouse::Button &button);
    bool isSpriteClicked(const sf::Sprite &sprite, const sf::Mouse::Button &button, sf::RenderWindow &window);
    bool isRectangleClicked(const sf::RectangleShape& rectangle, const sf::Mouse::Button& button, sf::RenderWindow& window);
    bool isMouseIntersectingSprite(const sf::Sprite& sprite, sf::RenderWindow& window);
    bool isMouseIntersectingSprite(const sf::Sprite* sprite, sf::RenderWindow& window);
    bool changeMouseWhenHoveringOverButton(const std::vector<sf::Sprite*>& buttons, sf::RenderWindow &window);
    sf::Vector2f getMousePosition(sf::RenderWindow &window);
};


#endif //PROJECT_GAME_INPUTMANAGER_HPP
