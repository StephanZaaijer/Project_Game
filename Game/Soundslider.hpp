#ifndef PROJECT_GAME_SOUNDSLIDER
#define PROJECT_GAME_SOUNDSLIDER

#include "Slider.hpp"

class SoundSlider : public Slider
{
public:
	SoundSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderColorOn, sf::Color sliderColorOff, sf::Vector2f Textlocation, int fontsize);
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

#endif // PROJECT_GAME_SOUNDSLIDER