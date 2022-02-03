#include "Musicslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

MusicSlider::MusicSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderBlockColorOn, sf::Color sliderBlockColorOff, sf::Vector2f textLocation, int fontSize) :
        Slider(gameData, sliderLocation, length, horizontal, sliderBlockColorOn, gameData->json.getMusicVolume()),
        sliderBlockColorOn(sliderBlockColorOn),
        sliderBlockColorOff(sliderBlockColorOff)
{
    if (gameData->json.getMusicState()) {
        setSliderBlockColor(sliderBlockColorOn);
    } else {
        setSliderBlockColor(sliderBlockColorOff);
    }
    level.setFont(gameData->assets.getFont("Bauhaus"));
    level.setPosition(textLocation);
    level.setCharacterSize(fontSize);
    level.setString(std::to_string(gameData->json.getMusicVolume()));
    level.setOrigin({level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2});
}

void MusicSlider::update() {
    if (gameData->json.getMusicState()) {
        setSliderBlockColor(sliderBlockColorOn);
    } else {
        setSliderBlockColor(sliderBlockColorOff);
    }
}
void MusicSlider::updateValue(int value) {
    gameData->json.setMusicVolume(value);
    level.setString(std::to_string(value));
    level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
}

void MusicSlider::draw() {
    Slider::draw();
    gameData->window.draw(level);
}
