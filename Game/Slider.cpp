#include "Slider.hpp"

#include <utility>

Slider::Slider(GameDataReference gameData, sf::Vector2f location, int length, bool horizontal, sf::Color sliderBlockColor, int startPercentage) :
	sliderPoint(location),
    length(length),
    horizontal(horizontal),
    gameData(std::move(gameData))

{
    sliderBlock.setSize({60, 60});
    sliderBlock.setOrigin(sliderBlock.getGlobalBounds().width / 2, sliderBlock.getGlobalBounds().height / 2);
    sliderBlock.setFillColor(sliderBlockColor);
    if (horizontal) {
        sliderMin = sliderPoint.x;
        sliderMax = sliderPoint.x + (length);
        ratio = ((sliderMax - sliderMin) / 100);
        slider.setSize({length+2 / 1.0f, 50});
        slider.setOrigin({0, slider.getGlobalBounds().height / 2});
        sliderBlock.setPosition({ sliderPoint.x + length - startPercentage * ratio, sliderPoint.y });
        slider.setPosition(sliderPoint.x-1, sliderPoint.y);
    } else {
        sliderMin = sliderPoint.y;
        sliderMax = sliderPoint.y + (length);
        ratio = ((sliderMax - sliderMin) / 100);
        slider.setSize({50, length+2 / 1.0f});
        slider.setOrigin({slider.getGlobalBounds().width / 2, 0});
        sliderBlock.setPosition({sliderPoint.x, sliderPoint.y + length - startPercentage *  ratio});
        slider.setPosition(sliderPoint.x, sliderPoint.y-1);
    }
    slider.setFillColor({0, 0, 0, 100});
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
        updateValue(getPercentage());
	}
}

void Slider::setSliderBlockColor(sf::Color newColor){
    sliderBlock.setFillColor(newColor);
}

void Slider::draw() {
	gameData->window.draw(slider);
	gameData->window.draw(sliderBlock);
}

int Slider::getPercentage(){
    if (horizontal){
        int temp = sliderBlock.getPosition().x;
        return 100 - (temp - sliderPoint.x) / ratio;
    }
    else {
        int temp = sliderBlock.getPosition().y;
        return 100 - (temp - sliderPoint.y) / ratio;
    }
}
