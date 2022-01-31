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
		bool Sound;
		int Soundvolume;
		bool Music;
		int Musicvolume;
		int Highscore;
		std::string PlayerSpriteID;
		std::string PlayerSpriteFile;
        std::string ObstacleColor;
        std::string WallColor;
	};

	JsonManager(std::string Gamefile);
	bool Get_Soundstate() const;
	int Get_Soundvolume() const;
	bool Get_Musicstate() const;
	int Get_Musicvolume() const;
	int Get_Highscore() const;
	CustomCharacter Get_PlayerSprite() const;
    sf::Color Get_ObstacleColor() const;
    sf::Color Get_WallColor() const;
    void Set_Soundstate(bool state);
	void Set_Soundvolume(int volume);
	void Set_Musicstate(bool state);
	void Set_Musicvolume(int volume);
	void Set_Highscore(int highscore);
	void Set_PlayerSprite(CustomCharacter PlayerSprite);
    void Set_ObstacleColor(sf::Color ObstacleColor);
    void Set_WallColor(sf::Color WallColor);

    void Update();
	void Direct_write();

private:
	bool start;
	void Get_data();
	JsonData data;
	Json::Value json_data;
    sf::Color string_to_color(std::string colorstring) const;
    std::string color_to_string(sf::Color color_sf) const;

    Json::Value Get_Json_from_file();
	void Write_Json_to_file();
	std::string Gamefile;
	sf::Clock clock;
	bool write_out;

    struct Color{const std::string color_string; const sf::Color color_sf;};
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
