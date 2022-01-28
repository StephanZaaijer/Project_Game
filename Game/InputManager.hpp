#ifndef PROJECT_GAME_INPUTMANAGER_HPP
#define PROJECT_GAME_INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include <vector>

class InputManager {
private:
    sf::Cursor hand_cursor;
    sf::Cursor arrow_cursor;
public:
    InputManager();
    bool IsKeyPressed(const sf::Keyboard::Key &key);
    bool IsButtonPressed(const sf::Mouse::Button &button);
    bool IsSpriteClicked(const sf::Sprite &sprite, const sf::Mouse::Button &button, sf::RenderWindow &window);
    bool IsRectangleClicked(const sf::RectangleShape& rectangle, const sf::Mouse::Button& button, sf::RenderWindow& window);
    bool IsMouseIntersectingSprite(const sf::Sprite& sprite, sf::RenderWindow& window);
    bool IsMouseIntersectingSprite(const sf::Sprite* sprite, sf::RenderWindow& window);
    bool ChangeMouseWhenHoveringOverButton(const std::vector<sf::Sprite*>& buttons, sf::RenderWindow &window);
    sf::Vector2f GetMousePosition(sf::RenderWindow &window);
};


#endif //PROJECT_GAME_INPUTMANAGER_HPP
