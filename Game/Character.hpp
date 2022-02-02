#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Line.hpp"
#include "Obstacle.hpp"
#include "Definitions.hpp"
#include "Game.hpp"
#include "GameOverState.hpp"


/// @file Character.hpp
/// @brief
/// Project_Game: This character is used to play the game. It controls the character.
class Character {
public:

    /// @brief
    /// This is the constructor to construct an object of Character
    /// @details
    /// This constructor initializes the position, scale and character state of the character.
    /// \param data The game_data of a state, which contains the StateMachine, window, AssetManager, InputManager and JsonManager.
    Character(GameDataReference data);

    /// @brief
    /// This function draws the character on the screen
    void draw();

    /// @brief
    /// This function updates the character
    /// @details
    /// This function checks in what state the character is.
    /// If the character is in the jumping state, it will update the character's velocity, position and height.
    /// And if the character is in the stick state, it will update it's fallRate, position and height.
    void update();

    /// @brief
    /// This function enables the character to jump
    /// @details
    /// This function checks if it was your first jump or your second jump.
    /// Sets the character state to jumping and resets your velocity to its maximum.
    void tap();

    /// @brief
    /// This function checks if the character collides with a wall.
    /// @details
    /// This function determines which side of the wall the character collides.
    /// If it collides, it sets back the character the same amount of pixels as it was inside the wall.
    /// Afterwards it sets the character to the state that corresponds to the side of the wall that has been hit.
    ///
    /// If the character collides with a side of the wall, it goes into the Stick state.
    /// If the character collides with the top of the wall, it goes into the Still state.
    /// If the character collides with the bottom of the wall, it remains in the Jumping state but with velocity equal to 0, so it falls down instantly.
    /// \param Rects This is a list of all the rectangles that are currently loaded in.
    void collideWalls(const std::vector<sf::RectangleShape> & Rects );

    /// @brief
    /// This function checks if the character collides with a spike
    /// @details
    /// This function creates a Line for each the end-point of the spike.
    /// These are used to getPoints across the Line to see if the characterSprite contains one of them
    /// If it contains a point, it returns true.
    /// \param spike This contains all the Spikes that are currently loaded in.
    /// \return boolean for if the character collides or not.
    bool collideSpike(const std::unique_ptr<Obstacle> & spike);

    /// @brief
    /// This function sets the character's height to the given value.
    /// \param value This is the new height value.
    void setHeight(const int &value);

    /// @brief
    /// This function moves the character down by a given offset.
    /// \param y This is the offset by which the character is moved down.
    void moveDownByOffset(const float & y);

    /// @brief
    /// This function resets the jump booleans.
    void resetJumps();

    /// @brief
    /// This function returns the current height of the character.
    /// \return An integer of the current height.
    int getHeight() const;

    /// @brief
    /// This function returns the current score of the character.
    /// \return An integer of the current score.
    int getScore() const;

    /// @brief
    /// This function adds score to the current score of the character.
    /// \param add This is the amount of score added to the character score.
    void addToScore(int add);

    /// @brief
    /// This function returns the characterSprite as a reference.
    /// \return The characterSprite of the character.
    sf::Sprite & getSprite ();

    /// @brief
    /// This function returns the characterSprite Global Boundaries.
    /// \return A sf::FloatRect representing the boundaries of the characterSprite.
    sf::FloatRect GetBounds();

    /// @brief
    /// This function returns the current position of the character
    /// \return A sf::Vector2f containing 2 float numbers of the x and y position of the character
    sf::Vector2f getPosition();

    /// @brief
    /// This function sets the isJumpPressed boolean
    void setJumpPressed(bool set);

    /// @brief
    /// This function returns if the player has jumped twice or not
    /// \return A boolean if the player has jumped twice.
    bool getJumpedTwice();

    bool death = false;

private:
    GameDataReference gameData;
    sf::Sprite characterSprite;
    sf::Vector2f velocity = {VELOCITY_X,0};
    sf::Vector2f position;
    character_states characterState;
    float fallVelocity = 0;
    int height = SCREEN_HEIGHT - CHARACTER_START_HEIGHT;
    int score = 0;
    bool jumpedOnce = false;
    bool jumpedTwice = false;
    bool isJumpPressed = false;
};

#endif //CHARACTER_HPP
