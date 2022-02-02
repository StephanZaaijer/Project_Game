#include "Slider.hpp"

#include <utility>
#include "Exceptions.hpp"

Slider::Slider(GameDataReference gameData, sf::Vector2f location, int par_length, bool horizontal, sf::Color sliderColor) :
	gameData(std::move(gameData)),
	sliderPoint(location),
    length(par_length+1),
    horizontal(horizontal)
{
	if (horizontal) {
		slider.setSize({length/1.0f, 50});
		slider.setOrigin({ 0, slider.getGlobalBounds().height / 2 });
	}
	else {
		slider.setSize({ 50, length/1.0f });
		slider.setOrigin({ slider.getGlobalBounds().width / 2, 0 });

	}
	sliderBlock.setSize({ 60, 60 });
	sliderBlock.setOrigin(sliderBlock.getGlobalBounds().width / 2, sliderBlock.getGlobalBounds().height / 2);
	sliderBlock.setFillColor(sliderColor);


	slider.setFillColor({ 0, 0, 0, 100 });
	slider.setPosition(sliderPoint);
	sliderBlock.setPosition({ sliderPoint.x + (sliderPoint.x - sliderPoint.x) / 2, sliderPoint.y });
}


void Slider::handleInput() {
	if (gameData->input.isRectangleClicked(slider, sf::Mouse::Left, gameData->window)) {
		sf::Vector2f mouse = gameData->input.getMousePosition(gameData->window);
		if (horizontal) {
			sliderBlock.setPosition({ mouse.x, sliderPoint.y });
		}
		else {
			sliderBlock.setPosition({ sliderPoint.x, mouse.y});
		}
	}
}

void Slider::draw() {
	gameData->window.draw(slider);
	gameData->window.draw(sliderBlock);
}


