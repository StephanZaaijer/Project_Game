#include "Soundslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

Soundslider::Soundslider(GameDataReference gameData, sf::Vector2f slider_location, int length, bool horizontal, sf::Color slidercolor_on, sf::Color slidercolor_off, sf::Vector2f Textlocation, int fontsize) :
	Slider(gameData, slider_location, length, horizontal, slidercolor_on),
	slidercolor_on(slidercolor_on),
	slidercolor_off(slidercolor_off)
{
	prev_state = gameData->json.Get_Soundstate();
	if (!prev_state) {
		slider_block.setFillColor(slidercolor_off);
	}
	if (horizontal) {
		slider_min = slider_location.x;
		slider_max = slider_location.x + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { slider_location.x + length - (gameData->json.Get_Soundvolume()) * ratio, slider_location.y };
	}
	else {
		slider_min = slider_location.y;
		slider_max = slider_location.y + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { slider_location.x, slider_location.y + length - (gameData->json.Get_Soundvolume()) *  ratio};

	}
	slider_block.setPosition(prev_sliderblock_location);
	level.setFont(gameData->assets.getFont("Bauhaus"));
	level.setPosition(Textlocation);
	level.setCharacterSize(fontsize);
	level.setString(std::to_string(gameData->json.Get_Soundvolume()));
	level.setOrigin({ level.getGlobalBounds().width/2, level.getGlobalBounds().height/2});
}

void Soundslider::update() {
	if (gameData->json.Get_Soundstate() and !prev_state) {
		slider_block.setFillColor(slidercolor_on);
		prev_state = true;
	}
	else if (!gameData->json.Get_Soundstate() and prev_state) {
		slider_block.setFillColor(slidercolor_off);
		prev_state = false;
	}
	if (prev_sliderblock_location != slider_block.getPosition()) {
		if (horizontal) {
			gameData->json.Set_Soundstate(true);
			int temp = slider_block.getPosition().x;
			int current_level = 100 - (temp - slider_point.x) / ratio;
			level.setString(std::to_string(current_level));
			level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
			gameData->json.Set_Soundvolume(current_level);
		}
		else {
			gameData->json.Set_Soundstate(true);
			int temp = slider_block.getPosition().y;
			int current_level = 100 - (temp - slider_point.y) / ratio;
			level.setString(std::to_string(current_level));
			level.setOrigin({ level.getGlobalBounds().width / 2, level.getGlobalBounds().height / 2 });
			gameData->json.Set_Soundvolume(current_level);
		}
		prev_sliderblock_location = slider_block.getPosition();
	}
}

void Soundslider::Draw() {
	gameData->window.draw(slider);
	gameData->window.draw(slider_block);
	gameData->window.draw(level);
}
