#ifndef PROJECT_GAME_JSONMANAGER_HPP
#define PROJECT_GAME_JSONMANAGER_HPP

#include "Definitions.hpp"
#include "../Library/JSON/json/json.h"
#include <fstream>
#include <SFML/Graphics.hpp>

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
	};

	JsonManager(std::string Gamefile);
	bool Get_Soundstate() const;
	int Get_Soundvolume() const;
	bool Get_Musicstate() const;
	int Get_Musicvolume() const;
	int Get_Highscore() const;
	CustomCharacter Get_PlayerSprite() const;
	void Set_Soundstate(bool state);
	void Set_Soundvolume(int volume);
	void Set_Musicstate(bool state);
	void Set_Musicvolume(int volume);
	void Set_Highscore(int highscore);
	void Set_PlayerSprite(CustomCharacter PlayerSprite);
	void Update();
	void Direct_write();

private:
	bool start;
	void Get_data();
	JsonData data;
	Json::Value json_data;
	Json::Value Get_Json_from_file();
	void Write_Json_to_file();
	std::string Gamefile;
	sf::Clock clock;
	bool write_out;
};

#endif // PROJECT_GAME_JSONMANAGER_HPP
