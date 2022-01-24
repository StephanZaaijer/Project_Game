#include "Slider.hpp"

class Soundslider:public Slider
{
public:
	Soundslider(GameDataReference game_data, sf::Vector2f location, int length, bool horizontal, sf::Color slidercolor);
	void update() override;
	void Draw() override;
	~Soundslider();

private:
	GameDataReference game_data;
	sf::Color slidercolor_on;
	sf::Color slidercolor_off;
	sf::Clock clock;
	int current_soundlevel;
	int slider_min;
	int slider_max;
	bool prev_state;
	int ratio;
	sf::Text sound;
	sf::Vector2f prev_sliderblock_location;
	bool changed = false;
};