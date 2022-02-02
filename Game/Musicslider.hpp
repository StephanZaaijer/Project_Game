#ifndef PROJECT_GAME_MUSICSLIDER
#define PROJECT_GAME_MUSICSLIDER

#include "Slider.hpp"

class MusicSlider :public Slider
{
public:
	MusicSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderColorOn, sf::Color sliderColorOff, sf::Vector2f textLocation, int fontSize);
    void update() override;
	void draw() override;

private:
	sf::Color sliderColorOn;
	sf::Color sliderColorOff;
	int sliderMin;
	int sliderMax;
	bool prevState;
	int ratio;
	sf::Text level;
	sf::Vector2f prevSliderblockLocation;
};

#endif // PROJECT_GAME_MUSICSLIDER