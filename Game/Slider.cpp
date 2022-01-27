#include "Slider.hpp"
#include "Exceptions.hpp"

Slider::Slider(GameDataReference game_data, sf::Vector2f location, int par_length, bool horizontal, sf::Color slidercolor) :
	game_data(game_data),
	slider_point(location),
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
	slider_block.setSize({ 60, 60 });
	slider_block.setOrigin(slider_block.getGlobalBounds().width / 2, slider_block.getGlobalBounds().height / 2);
	slider_block.setFillColor(slidercolor);


	slider.setFillColor({ 0, 0, 0, 100 });
	slider.setPosition(slider_point);
	slider_block.setPosition({ slider_point.x + (slider_point.x - slider_point.x) / 2, slider_point.y });
}


void Slider::handleinput() {
	if (game_data->input.IsRectangleClicked(slider, sf::Mouse::Left, game_data->window)) {
		sf::Vector2f mouse = game_data->input.GetMousePosition(game_data->window);
		if (horizontal) {
			slider_block.setPosition({ mouse.x, slider_point.y });
		}
		else {
			slider_block.setPosition({ slider_point.x, mouse.y});
		}
	}
}

void Slider::Draw() {
	game_data->window.draw(slider);
	game_data->window.draw(slider_block);
}

sf::RectangleShape& Slider::get_slider_block() {
	return slider_block;
}


