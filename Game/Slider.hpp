#ifndef PROJECT_GAME_SLIDER
#define PROJECT_GAME_SLIDER

#include <SFML/Graphics.hpp>
#include "Game.hpp"


///@file
///@brief
/// Project_Game: This is the virtual class Slider


///@brief
///Virtual Sliderclass

class Slider {
private:
    sf::RectangleShape slider;
    sf::RectangleShape sliderBlock;
    sf::Vector2f sliderPoint;
    int length;
    bool horizontal;
    int sliderMin;
    int sliderMax;
    int ratio;
    ///@brief
    /// function to calculate the current percentage of the block in relation to the min and max of the slider
    int getPercentage();

protected:
	GameDataReference gameData;
    /// @brief
    /// virtual function that needs to be implemented by the subclasse to handle a change in value
    /// \param value the new value that given to the subclasse
    virtual void updateValue(int value)=0;

    /// @brief
    /// function to change to color of the sliderblock from the subclasse
    /// \param newColor the new color of the sliderblock
    void setSliderBlockColor(sf::Color newColor);

public:
    /// @brief
    ///constructor that creates the slider, calculates the ratio and set the position of the sliderblock
    /// \param gameData  GameDataReference used to get the mouselocation and draw to the screen
    /// \param location sf::Vector2f which indicates where the slider is placed
    /// \param length integer length of the slider in pixels
    /// \param horizontal boolean that indicates if the slider is horizontal or vertical
    /// \param sliderBlockColor the color that the sliderblock is when the sound on creation
    /// \param startPercentage the start percentage of the sliderblock
	Slider(GameDataReference gameData, sf::Vector2f location, int length, bool horizontal, sf::Color sliderBlockColor, int startPercentage);
	///@brief
	/// virtual function to draw the slider the current implementation draws the slider and it`s sliderblock
    virtual void draw();
    /// @brief
    /// handleInput function to move the sliderblock when clicked and calls the updateValue function of it`s subclass with the value calculated by getPercentage
    void handleInput();

    /// purely virtual function that can be implemented however necessary
    virtual void update()=0;
};

#endif // PROJECT_GAME_SLIDER