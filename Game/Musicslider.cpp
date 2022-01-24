#include "Musicslider.hpp"
#include "Exceptions.hpp"
#include <iostream>

Musicslider::Musicslider(GameDataReference game_data, sf::Vector2f location, int length, bool horizontal, sf::Color slidercolor) :
	Slider(game_data, location, length, horizontal, slidercolor),
	game_data(game_data),
	slidercolor_on(slidercolor)
{
	slidercolor_off = { slidercolor_on.r, slidercolor_on.g, slidercolor_on.b, 100 };
	prev_state = game_data->json.Get_Musicstate();
	if (!prev_state) {
		slider_block.setFillColor(slidercolor_off);
	}
	if (horizontal) {
		slider_min = location.x;
		slider_max = location.x + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { location.x + (game_data->json.Get_Musicvolume()) * ratio, location.y };
	}
	else {
		slider_min = location.y;
		slider_max = location.y + length;
		ratio = ((slider_max - slider_min) / 100);
		prev_sliderblock_location = { location.x, location.y + (game_data->json.Get_Musicvolume()) *  ratio};

	}
	slider_block.setPosition(prev_sliderblock_location);
	level.setFont(game_data->assets.GetFont("Bauhaus font"));
	level.setPosition({ location.x, location.y - 100 });

}

void Musicslider::update() {
	if (game_data->json.Get_Musicstate() and !prev_state) {
		slider_block.setFillColor(slidercolor_on);
		prev_state = true;
	}
	else if (!game_data->json.Get_Musicstate() and prev_state) {
		slider_block.setFillColor(slidercolor_off);
		prev_state = false;
	}
	if (prev_sliderblock_location != slider_block.getPosition()){
		if (horizontal) {
			game_data->json.Set_Musicstate(true);
			int temp = slider_block.getPosition().x;
			int current_level = (temp - slider_point.x)/ratio;
			level.setString(std::to_string(current_level));
			game_data->json.Set_Musicvolume(current_level);

		}
		else {
			game_data->json.Set_Musicstate(true);
			int temp = slider_block.getPosition().y;
			int current_level = (temp - slider_point.y) / ratio;
			level.setString(std::to_string(current_level));
			game_data->json.Set_Musicvolume(current_level);

		}
		prev_sliderblock_location = slider_block.getPosition();
	}
}

void Musicslider::Draw() {
	game_data->window.draw(slider);
	game_data->window.draw(slider_block);
	game_data->window.draw(level);
}