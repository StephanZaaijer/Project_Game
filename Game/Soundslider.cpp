#include "Soundslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

Soundslider::Soundslider(GameDataReference game_data, sf::Vector2f location, int length, bool horizontal, sf::Color slidercolor) :
	Slider(game_data, location, length, horizontal, slidercolor),
	game_data(game_data),
	slidercolor_on(slidercolor)
{
	slidercolor_off = { slidercolor_on.r, slidercolor_on.g, slidercolor_on.b, 100 };
	prev_state = game_data->json.Get_Soundstate();
	if (!prev_state) {
		slider_block.setFillColor(slidercolor_off);
	}
	if (horizontal) {
		slider_min = location.x;
		slider_max = location.x + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { location.x + (game_data->json.Get_Soundvolume()) * ratio, location.y };
	}
	else {
		slider_min = location.y;
		slider_max = location.y + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { location.x, location.y + (game_data->json.Get_Soundvolume()) *  ratio};

	}
	slider_block.setPosition(prev_sliderblock_location);
	sound.setFont(game_data->assets.GetFont("Bauhaus font"));
	sound.setPosition({ location.x, location.y - 100 });

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
			sound.setString(std::to_string(current_level));
			game_data->json.Set_Soundvolume(current_level);
		}
		else {

			game_data->json.Set_Soundstate(true);
			int temp = slider_block.getPosition().y;
			int current_level = (temp - slider_point.y) / ratio;
			sound.setString(std::to_string(current_level));
			game_data->json.Set_Soundvolume(current_level);

		}
		prev_sliderblock_location = slider_block.getPosition();
	}
}

void Soundslider::Draw() {
	game_data->window.draw(slider);
	game_data->window.draw(slider_block);
	game_data->window.draw(sound);
}