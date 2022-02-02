#ifndef PROJECT_GAME_SLIDER
#define PROJECT_GAME_SLIDER

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Slider {
protected:
	GameDataReference gameData;
	sf::RectangleShape slider;
	sf::RectangleShape sliderBlock;
	sf::Vector2f sliderPoint;
	int length;
	bool horizontal;

public:
	Slider(GameDataReference gameData, sf::Vector2f location, int par_length, bool horizontal, sf::Color sliderColor);
	virtual void draw();
	void handleInput();
	virtual void update(){};
};

#endif // PROJECT_GAME_SLIDER