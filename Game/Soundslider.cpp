#include "Soundslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

SoundSlider::SoundSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderBlockColorOn, sf::Color sliderBlockColorOff, sf::Vector2f textLocation, int fontSize) :
	Slider(gameData, sliderLocation, length, horizontal, sliderBlockColorOn, gameData->json.getSoundVolume()),
    sliderBlockColorOn(sliderBlockColorOn),
    sliderBlockColorOff(sliderBlockColorOff)
    {
        if (gameData->json.getSoundState()) {
            setSliderBlockColor(sliderBlockColorOn);
        } else {
            setSliderBlockColor(sliderBlockColorOff);
        }
        level.setFont(gameData->assets.getFont("Bauhaus"));
        level.setPosition(textLocation);
        level.setCharacterSize(fontSize);
        level.setString(std::to_string(gameData->json.getSoundVolume()));
        level.setOrigin({level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2});
}

void SoundSlider::update() {
    if (gameData->json.getSoundState()) {
        setSliderBlockColor(sliderBlockColorOn);
    } else {
        setSliderBlockColor(sliderBlockColorOff);
    }
}
void SoundSlider::updateValue(int value) {
    gameData->json.setSoundVolume(value);
    level.setString(std::to_string(value));
    level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
}

void SoundSlider::draw() {
	Slider::draw();
	gameData->window.draw(level);
}
