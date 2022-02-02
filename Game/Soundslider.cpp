#include "Soundslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

SoundSlider::SoundSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderColorOn, sf::Color sliderColorOff, sf::Vector2f textLocation, int fontSize) :
	Slider(gameData, sliderLocation, length, horizontal, sliderColorOn),
	sliderColorOn(sliderColorOn),
	sliderColorOff(sliderColorOff)
{
	prevState = gameData->json.getSoundState();
	if (!prevState) {
		sliderBlock.setFillColor(sliderColorOff);
	}
	if (horizontal) {
		sliderMin = sliderLocation.x;
		sliderMax = sliderLocation.x + length;
		ratio = ((sliderMax - sliderMin) / 100);
		prevSliderblockLocation = { sliderLocation.x + length - (gameData->json.getSoundVolume()) * ratio, sliderLocation.y };
	}
	else {
		sliderMin = sliderLocation.y;
		sliderMax = sliderLocation.y + length;
		ratio = ((sliderMax - sliderMin) / 100);
		prevSliderblockLocation = { sliderLocation.x, sliderLocation.y + length - (gameData->json.getSoundVolume()) *  ratio};

	}
	sliderBlock.setPosition(prevSliderblockLocation);
	level.setFont(gameData->assets.getFont("Bauhaus"));
	level.setPosition(textLocation);
	level.setCharacterSize(fontSize);
	level.setString(std::to_string(gameData->json.getSoundVolume()));
	level.setOrigin({ level.getGlobalBounds().width/2, level.getGlobalBounds().height/2});
}

void SoundSlider::update() {
	if (gameData->json.getSoundState() and !prevState) {
		sliderBlock.setFillColor(sliderColorOn);
		prevState = true;
	}
	else if (!gameData->json.getSoundState() and prevState) {
		sliderBlock.setFillColor(sliderColorOff);
		prevState = false;
	}
	if (prevSliderblockLocation != sliderBlock.getPosition()) {
		if (horizontal) {
			gameData->json.setSoundState(true);
			int temp = sliderBlock.getPosition().x;
			int currentLevel = 100 - (temp - sliderPoint.x) / ratio;
			level.setString(std::to_string(currentLevel));
			level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
			gameData->json.setSoundVolume(currentLevel);
		}
		else {
			gameData->json.setSoundState(true);
			int temp = sliderBlock.getPosition().y;
			int currentLevel = 100 - (temp - sliderPoint.y) / ratio;
			level.setString(std::to_string(currentLevel));
			level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
			gameData->json.setSoundVolume(currentLevel);
		}
		prevSliderblockLocation = sliderBlock.getPosition();
	}
}

void SoundSlider::draw() {
	gameData->window.draw(slider);
	gameData->window.draw(sliderBlock);
	gameData->window.draw(level);
}
