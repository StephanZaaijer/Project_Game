#pragma once
#include "Definitions.hpp"
#include "../Library/JSON/json/json.h"
#include <fstream>

class JsonManager {
public:
	struct JsonData {
		bool Sound;
		int Soundvolume;
		bool Music;
		int Musicvolume;
		int Highscore;
		std::string PlayerSprite;
	};

	JsonManager(std::string Gamefile);
	bool Get_Soundstate();
	int Get_Soundvolume();
	bool Get_Musicstate();
	int Get_Musicvolume();
	int Get_Highscore();
	std::string Get_PlayerSprite();
	void Set_Soundstate(bool state);
	void Set_Soundvolume(int volume);
	void Set_Musicstate(bool state);
	void Set_Musicvolume(int volume);
	void Set_Highscore(int highscore);
	void Set_PlayerSprite(std::string PlayerSpriteID);

private:
	bool start;
	void Get_data();
	JsonData data;
	Json::Value json_data;
	Json::Value Get_Json_from_file();
	void Write_Json_to_file();
	std::string Gamefile;
};

