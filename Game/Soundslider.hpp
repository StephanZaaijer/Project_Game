#ifndef PROJECT_GAME_SOUNDSLIDER
#define PROJECT_GAME_SOUNDSLIDER

#include "Slider.hpp"

class Soundslider:public Slider
{
public:
	Soundslider(GameDataReference game_data, sf::Vector2f slider_location, int length, bool horizontal, sf::Color slidercolor_on, sf::Color slidercolor_off, sf::Vector2f Textlocation, int fontsize);
	~Soundslider() override = default;
    void update() override;
	void Draw() override;

private:
	GameDataReference game_data;
	sf::Color slidercolor_on;
	sf::Color slidercolor_off;
	int slider_min;
	int slider_max;
	bool prev_state;
	int ratio;
	sf::Text level;
	sf::Vector2f prev_sliderblock_location;
};

#endif // PROJECT_GAME_SLIDER