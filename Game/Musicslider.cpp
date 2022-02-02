#include "Musicslider.hpp"
#include "Exceptions.hpp"

MusicSlider::MusicSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderColorOn, sf::Color sliderColorOff, sf::Vector2f textLocation, int fontSize) :
	Slider(gameData, sliderLocation, length, horizontal, sliderColorOn),
	sliderColorOn(sliderColorOn),
	sliderColorOff(sliderColorOff)
{
	prevState = gameData->json.getMusicState();
	if (!prevState) {
		sliderBlock.setFillColor(sliderColorOff);
	}
	if (horizontal) {
		sliderMin = sliderLocation.x;
		sliderMax = sliderLocation.x + length;
		ratio = ((sliderMax - sliderMin) / 100);
		prevSliderblockLocation = { sliderLocation.x + length - (gameData->json.getMusicVolume()) * ratio, sliderLocation.y };
	}
	else {
		sliderMin = sliderLocation.y;
		sliderMax = sliderLocation.y + length;
		ratio = ((sliderMax - sliderMin) / 100);
		prevSliderblockLocation = { sliderLocation.x, sliderLocation.y + length - (gameData->json.getMusicVolume()) * ratio };

	}
	sliderBlock.setPosition(prevSliderblockLocation);
	level.setFont(gameData->assets.getFont("Bauhaus"));
	level.setPosition(textLocation);
	level.setCharacterSize(fontSize);
	level.setString(std::to_string(gameData->json.getMusicVolume()));
	level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
}

void MusicSlider::update() {
	if (gameData->json.getMusicState() and !prevState) {
		sliderBlock.setFillColor(sliderColorOn);
		prevState = true;
	}
	else if (!gameData->json.getMusicState() and prevState) {
		sliderBlock.setFillColor(sliderColorOff);
		prevState = false;
	}
	if (prevSliderblockLocation != sliderBlock.getPosition()){
		if (horizontal) {
			gameData->json.setMusicState(true);
			int temp = sliderBlock.getPosition().x;
			int currentLevel = 100 - (temp - sliderPoint.x)/ratio;
			level.setString(std::to_string(currentLevel));
			level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
			gameData->json.setMusicVolume(currentLevel);
		}
		else {
			gameData->json.setMusicState(true);
			int temp = sliderBlock.getPosition().y;
			int currentLevel = 100 - (temp - sliderPoint.y) / ratio;
			level.setString(std::to_string(currentLevel));
			level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
			gameData->json.setMusicVolume(currentLevel);
		}
		prevSliderblockLocation = sliderBlock.getPosition();
	}
}

void MusicSlider::draw() {
	gameData->window.draw(slider);
	gameData->window.draw(sliderBlock);
	gameData->window.draw(level);
}