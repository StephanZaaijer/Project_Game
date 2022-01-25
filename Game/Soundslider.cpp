#include "Soundslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

Soundslider::Soundslider(GameDataReference game_data, sf::Vector2f slider_location, int length, bool horizontal, sf::Color slidercolor_on, sf::Color slidercolor_off, sf::Vector2f Textlocation, int fontsize) :
	Slider(game_data, slider_location, length, horizontal, slidercolor_on),
	game_data(game_data),
	slidercolor_on(slidercolor_on),
	slidercolor_off(slidercolor_off)
{
	prev_state = game_data->json.Get_Soundstate();
	if (!prev_state) {
		slider_block.setFillColor(slidercolor_off);
	}
	if (horizontal) {
		slider_min = slider_location.x;
		slider_max = slider_location.x + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { slider_location.x + (game_data->json.Get_Soundvolume()) * ratio, slider_location.y };
	}
	else {
		slider_min = slider_location.y;
		slider_max = slider_location.y + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { slider_location.x, slider_location.y + (game_data->json.Get_Soundvolume()) *  ratio};

	}
	slider_block.setPosition(prev_sliderblock_location);
	level.setFont(game_data->assets.GetFont("Bauhaus font"));
	level.setPosition(Textlocation);
	level.setCharacterSize(fontsize);
	level.setString(std::to_string(game_data->json.Get_Soundvolume()));
	level.setOrigin({ level.getGlobalBounds().width, level.getGlobalBounds().height });
}

void Soundslider::update() {
	if (game_data->json.Get_Soundstate() and !prev_state) {
		slider_block.setFillColor(slidercolor_on);
		prev_state = true;
	}
	else if (!game_data->json.Get_Soundstate() and prev_state) {
		slider_block.setFillColor(slidercolor_off);
		prev_state = false;
	}
	if (prev_sliderblock_location != slider_block.getPosition()) {
		if (horizontal) {
			game_data->json.Set_Soundstate(true);
			int temp = slider_block.getPosition().x;
			int current_level = (temp - slider_point.x) / ratio;
			level.setString(std::to_string(current_level));
			level.setOrigin({ level.getGlobalBounds().width, level.getGlobalBounds().height });
			game_data->json.Set_Soundvolume(current_level);
		}
		else {
			game_data->json.Set_Soundstate(true);
			int temp = slider_block.getPosition().y;
			int current_level = (temp - slider_point.y) / ratio;
			level.setString(std::to_string(current_level));
			level.setOrigin({ level.getGlobalBounds().width, level.getGlobalBounds().height });
			game_data->json.Set_Soundvolume(current_level);
		}
		prev_sliderblock_location = slider_block.getPosition();
	}
}

void Soundslider::Draw() {
	game_data->window.draw(slider);
	game_data->window.draw(slider_block);
	game_data->window.draw(level);
}