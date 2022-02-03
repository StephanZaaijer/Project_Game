#ifndef PROJECT_GAME_MUSICSLIDER
#define PROJECT_GAME_MUSICSLIDER

#include "Slider.hpp"
///@file
///@brief
/// Project_Game: This is the MusicSlider which is used to change the musicvolume


///@brief
///MusicSliderclass that is implemented from Slider and is used to change the musicvolume in the SoundSettingsState
class MusicSlider : public Slider
{
public:
    /// @brief
    /// MusicSlider constructor that creates it`s superclass and set all the settings for the text and the color of the sliderBlock
    /// \param gameData GameDataReference used to get the mouselocation and draw to the screen
    /// \param sliderLocation sf::Vector2f which indicates where the slider is placed
    /// \param length integer length of the slider in pixels
    /// \param horizontal boolean that indicates if the slider is horizontal or vertical
    /// \param sliderBlockColorOn the color that the sliderblock is when the music is active
    /// \param sliderBlockColorOff the color that the sliderblock is when the music is inactive
    /// \param textLocation the location of the musicvolume text
    /// \param fontSize the fontsize of the musicvolume text
    MusicSlider(GameDataReference gameData, sf::Vector2f sliderLocation, int length, bool horizontal, sf::Color sliderBlockColorOn, sf::Color sliderBlockColorOff, sf::Vector2f textLocation, int fontSize);
    ///@brief
    /// update function called by the state to update the color of the sliderBlock
    void update() override;
    /// @brief
    /// draw functions that draw`s the musicvolume text and calls the draw function of it`s superclass to draw the slider and the sliderblock
    void draw() override;

private:
    sf::Color sliderBlockColorOn;
    sf::Color sliderBlockColorOff;
    sf::Text level;
    /// @brief
    /// implemented virtual function of Slider called by the handleInputfunction of Slider to update the Musicvolume value
    /// \param value the new musicvolume value
    void updateValue(int value) override;

};

#endif // PROJECT_GAME_MUSICSLIDER