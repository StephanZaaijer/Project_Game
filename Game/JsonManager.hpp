#ifndef PROJECT_GAME_JSONMANAGER_HPP
#define PROJECT_GAME_JSONMANAGER_HPP

#include "Definitions.hpp"
#include "../Library/JSON/json/json.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>

///@file JsonManager.hpp
///@brief
/// Project_Game: JsonManager used to interact with the Jsonfile



///@brief
/// JsonManager class used to read from and write to the Jsonfile
class JsonManager {
public:
    /// @brief
    /// Constructor that loades the data from the Jsonfile in to the JsonData-struct
    /// \param gameFile The filelocation of the Jsonfile containing all setting and additional gamedata
    JsonManager(const std::string &gameFile);

    /// @brief
    /// Function that returns a boolean that tells if the sound is on or off
    /// \return boolean that is equal to the current soundstate
    bool getSoundState() const;

    /// @brief
    /// Function that returns a integer that is equal to the current soundlevel
    /// \return integer that tells the current soundlevel set in the json and settingsmenu
    int getSoundVolume() const;

    /// @brief
    /// Function that returns a boolean that tells if the music is on or off
    /// \return boolean that is equal to the current musicstate
    bool getMusicState() const;

    /// @brief
    /// Function that returns a integer that is equal to the current musiclevel
    /// \return integer that tells the current musiclevel set in the json and settingsmenu
    int getMusicVolume() const;

    /// @brief
    /// Function that returns a integer that is stored in the JsonManager as the current highscore
    /// \return integer that tells the current highscore stored in the Jsonfile
    int getHighscore() const;

    /// @brief
    /// Function that returns a integer that is stored in the JsonManager as the current amount of coins
    /// \return integer that tells the current amount of coins set in the json
    int getCoins() const;

    /// @brief
    /// Function that returns a vector of bools matching all skins so that we can determine which skins are already bought and which are not
    /// \return std::vector of bools of the same length as the amount of skins
    std::vector<bool> getBoughtSkins() const;

    /// @brief
    /// Function that returns a vector of std::string so that they can be shown in the MainMenuState
    /// \return std::vector of quotes that were stored in the jsonfile
    std::vector<std::string> getQuotes() const;

    /// @brief
    /// function that returns the data of the character-sprite stored in the Json
    /// @details
    /// The data that is returned contains the name of the character-sprite and the path to the file
    /// \return CostumCharacter-struct containing the name and path of the character-sprite
    CustomCharacter getPlayerSprite() const;

    /// @brief
    /// function that returns the data of the colorTheme stored in the Json
    /// @details
    /// The data that is returned contains the name of the colortheme, the path to the color-theme-sprite for the costumizestate and the wallcolor and obstaclecolor for the MainGameState
    /// \return CustomTheme-struct containing the name, path of the color-theme-sprite, the wallcolor and the obstaclecolor
    CustomTheme getPlayerTheme() const;

    /// @brief
    /// function that returns the obstaclecolor
    /// \return The sf::Color that is equal to the string stored in the jsonfile
    sf::Color getObstacleColor() const;

    /// @brief
    /// function that returns the wallcolor
    /// \return The sf::Color that is equal to the string stored in the jsonfile
    sf::Color getWallColor() const;

    /// @brief
    /// function that changes the soundstatevalue in the jsonfile, only changes the value if the value is different to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param state the new soundstate
    void setSoundState(const bool &state);

    /// @brief
    /// function that changes the soundvolumevalue in the jsonfile, only changes the value if the value is different to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param volume the new volumelevel
    void setSoundVolume(const int &volume);

    /// @brief
    /// function that changes the musicstatevalue in the jsonfile, only changes the value if the value is different to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param state the new musicstate

    void setMusicState(const bool &state);

    /// @brief
    /// function that changes the musicvolumevalue in the jsonfile, only changes the value if the value is different to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param volume the new volumelevel
    void setMusicVolume(const int &volume);

    /// @brief
    /// function that changes the highscore in the jsonfile, only changes the value if the value is higher than the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param highscore the new highscore
    void setHighscore(const int &highscore);

    /// @brief
    /// function that changes the playerspritedata in the jsonfile, only changes the value if the value is unequal to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param playerSprite the new CostumCharacter settings
    void setPlayerSprite(const CustomCharacter &playerSprite);

    /// @brief
    /// function that changes the colortheme in the jsonfile, only changes the value if the value is unequal to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param playerTheme the new CostumTheme settings
    void setPlayerTheme(const CustomTheme &playerTheme);

    /// @brief
    /// function that changes the amount of coins in the jsonfile, only changes the value if the value is unequal to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param coins the new amount of coins
    void setCoins(const int &coins);

    /// @brief
    /// function that changes a index of the list of boughtskins in the jsonfile, only changes the value if the value is unequal to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param index the index of the bought skin in the vector
    /// \param value the new value for that index
    void setBoughtSkins(const int &index, const bool &value);

    /// @brief
    /// function that changes a index of the list of quotes in the jsonfile, only changes the value if the value is unequal to the previous value
    /// @details
    /// The function sets a boolean and resets the clock so that the jsondata is written to the jsonfile 5 seconds after the last change.
    /// \param index the index of the quote in the vector
    /// \param quote the new value for that index
    void setQuotes(const int &index, const std::string &quote);

    /// @brief
    /// Update function that runs on closing of the game that checks if the boolean is set if that is the case it writes the data to the jsonfile.
    void write();

private:
    /// @brief
    /// JsonData struct that contains all data read from the Jsonfile
    struct JsonData {
        bool sound;
        int soundVolume;
        bool music;
        int musicVolume;
        int highscore;
        std::string playerSpriteID;
        std::string playerSpriteFile;
        std::string playerThemeID;
        std::string playerThemeFile;
        std::string wallColor;
        std::string obstacleColor;
        int coins;
        std::vector<bool> boughtSkins;
        std::vector<std::string> quotes;
    };

    bool start;

    /// @brief
    /// function that is called by the constructor that calls getJsonFromFile to read the data from the jsonfile and stores the returned data in the JsonData-struct
    void getData();

    JsonData data;
    Json::Value jsonData;


    /// @brief
    /// function that turn std::string into sf::color using the colors vector
    sf::Color stringToColor(const std::string &colorString) const;

    /// @brief
    /// function that turn sf::color into std::string using the colors vector
    std::string colorToString(const sf::Color &colorSf) const;

    /// @brief
    /// function that reads the data from the jsonfile
    /// \return all the data in the jsonfile in the Json::Value type which can be converted in integers, boolean, const char* and std::strings
    Json::Value getJsonFromFile();

    /// @brief
    /// function that writes the data stored in JsonManager::jsonData to the jsonfile
    void writeJsonToFile();

    std::string gameFile;
    bool writeOut;

    struct Color {
        const std::string colorString;
        const sf::Color colorSf;
    };
    const std::vector<Color> colors = {{"Black",   sf::Color::Black},
                                       {"White",   sf::Color::White},
                                       {"Red",     sf::Color::Red},
                                       {"Green",   sf::Color::Green},
                                       {"Blue",    sf::Color::Blue},
                                       {"Yellow",  sf::Color::Yellow},
                                       {"Magenta", sf::Color::Magenta},
                                       {"Cyan",    sf::Color::Cyan}};

};

#endif // PROJECT_GAME_JSONMANAGER_HPP
