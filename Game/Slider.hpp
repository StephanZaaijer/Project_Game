#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Slider
{
protected:
	GameDataReference game_data;
	sf::RectangleShape slider;
	sf::RectangleShape slider_block;
	sf::Vector2f slider_point;
	int length;
	bool horizontal;

public:
	Slider(GameDataReference game_data, sf::Vector2f location, int par_length, bool horizontal, sf::Color slidercolor);
	virtual void Draw();
	void handleinput();
	virtual void update(){};
	sf::RectangleShape& get_slider_block();
};

