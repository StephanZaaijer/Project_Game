#ifndef PROJECT_GAME_JSONMANAGER_HPP
#define PROJECT_GAME_JSONMANAGER_HPP

#include "Definitions.hpp"
#include "../Library/JSON/json/json.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>

class JsonManager {
public:
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

	JsonManager(std::string gameFile);
	bool getSoundState() const;
	int getSoundVolume() const;
	bool getMusicState() const;
	int getMusicVolume() const;
	int getHighscore() const;
    int getCoins() const;
    std::vector<bool> getBoughtSkins() const;
    std::vector<std::string> getQuotes() const;
	CustomCharacter getPlayerSprite() const;
    CustomTheme getPlayerTheme() const;
    sf::Color getObstacleColor() const;
    sf::Color getWallColor() const;
    void setSoundState(const bool &state);
	void setSoundVolume(const int &volume);
	void setMusicState(const bool &state);
	void setMusicVolume(const int &volume);
	void setHighscore(const int &highscore);
	void setPlayerSprite(const CustomCharacter& playerSprite);
    void setPlayerTheme(const CustomTheme& playerTheme);
    void setCoins(const int &coins);
    void setBoughtSkins(const int &index, const bool &value);
    void setQuotes(const int &index, const std::string &quote);

    void update();
	void directWrite();

private:
	void getData();
	JsonData data;
	Json::Value jsonData;
    sf::Color stringToColor(const std::string &colorString) const;
    std::string colorToString(const sf::Color &colorSf) const;

    Json::Value getJsonFromFile();
	void writeJsonToFile();
	std::string gameFile;
	sf::Clock clock;
	bool writeOut;

    struct Color{const std::string colorString; const sf::Color colorSf;};
    const std::vector<Color> colors={{"Black", sf::Color::Black},
                                     {"White", sf::Color::White},
                                     {"Red", sf::Color::Red},
                                     {"Green", sf::Color::Green},
                                     {"Blue", sf::Color::Blue},
                                     {"Yellow", sf::Color::Yellow},
                                     {"Magenta", sf::Color::Magenta},
                                     {"Cyan", sf::Color::Cyan}};

};

#endif // PROJECT_GAME_JSONMANAGER_HPP
