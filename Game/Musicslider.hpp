#ifndef PROJECT_GAME_MUSICSLIDER
#define PROJECT_GAME_MUSICSLIDER

#include "Slider.hpp"

class Musicslider :public Slider
{
public:
	Musicslider(GameDataReference gameData, sf::Vector2f slider_location, int length, bool horizontal, sf::Color slidercolor_on, sf::Color slidercolor_off, sf::Vector2f Textlocation, int fontsize);
    void update() override;
	void Draw() override;

private:
	sf::Color slidercolor_on;
	sf::Color slidercolor_off;
	int slider_min;
	int slider_max;
	bool prev_state;
	int ratio;
	sf::Text level;
	sf::Vector2f prev_sliderblock_location;
};

#endif // PROJECT_GAME_MUSICSLIDER