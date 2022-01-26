#include "JsonManager.hpp"
#include <iostream>
#include <utility>
#include "Exceptions.hpp"

JsonManager::JsonManager(std::string Gamefile):
	Gamefile(std::move(Gamefile))
{
	data = JsonData();
	Get_data();
}

void JsonManager::Get_data() {
	json_data = Get_Json_from_file();
	data = {
		json_data["Audio"]["Sound"].asBool(),
		json_data["Audio"]["Soundlevel"].asInt(),
		json_data["Audio"]["Music"].asBool(),
		json_data["Audio"]["Musiclevel"].asInt(),
		json_data["Score"]["Highscore"].asInt(),
		json_data["Player"]["ID"].asString(),
		json_data["Player"]["File"].asString()
	};
}

bool JsonManager::Get_Soundstate() const {
	return data.Sound;
}

int JsonManager::Get_Soundvolume() const {
	return data.Soundvolume;
}

bool JsonManager::Get_Musicstate() const {
	return data.Music;
}

int JsonManager::Get_Musicvolume() const {
	return data.Musicvolume;
}

int JsonManager::Get_Highscore() const {
	return data.Highscore;
}

CustomCharacter JsonManager::Get_PlayerSprite() const {
	return { data.PlayerSpriteID, data.PlayerSpriteFile };
}

void JsonManager::Set_Soundstate(bool state) {
	if (state == data.Sound) {
		return;
	}
	data.Sound = state;
	json_data["Audio"]["Sound"] = state;
	clock.restart();
	write_out = true;
}
void JsonManager::Set_Soundvolume(int volume) {
	if (volume == data.Soundvolume) {
		return;
	}
	data.Sound = volume!=0;
	json_data["Audio"]["Sound"] = volume != 0;
	data.Soundvolume = volume;
	json_data["Audio"]["Soundlevel"] = volume;
	clock.restart();
	write_out = true;
}
void JsonManager::Set_Musicstate(bool state) {
	if (state == data.Music) {
		return;
	}
	data.Music = state;
	json_data["Audio"]["Music"] = state;
	clock.restart();
	write_out = true;
}
void JsonManager::Set_Musicvolume(int volume) {
	if (volume == data.Musicvolume) {
		return;
	}
	data.Music = volume != 0;
	json_data["Audio"]["Music"] = volume != 0;
	data.Musicvolume = volume;
	json_data["Audio"]["Musiclevel"] = volume;
	clock.restart();
	write_out = true;
}
void JsonManager::Set_Highscore(int highscore) {
	if (highscore <= data.Highscore) {
		return;
	}
	data.Highscore = highscore;
	json_data["Score"]["Highscore"] = highscore;
	clock.restart();
	write_out = true;
}

void JsonManager::Set_PlayerSprite(CustomCharacter PlayerSprite) {
	if (PlayerSprite.CharacterName == data.PlayerSpriteID) {
		return;
	}
	data.PlayerSpriteID = PlayerSprite.CharacterName;
	data.PlayerSpriteFile = PlayerSprite.CharacterFileName;
	json_data["Player"]["ID"] = PlayerSprite.CharacterName;
	json_data["Player"]["File"] = PlayerSprite.CharacterFileName;
	clock.restart();
	write_out = true;
}


void JsonManager::Update() {
	if (write_out and clock.getElapsedTime().asSeconds() >= 5) {
		write_out = false;
		Write_Json_to_file();
	}
}

void JsonManager::Direct_write() {
	if (write_out) {
		write_out = false;
		Write_Json_to_file();
	}
}

Json::Value JsonManager::Get_Json_from_file() {
	std::ifstream Inputfile;
	Json::Value json_data;
	Json::CharReaderBuilder builder;
	Inputfile.open(Gamefile);
	if (!Inputfile.is_open()) {
		throw open_file_exception(Gamefile);
	}
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, Inputfile, &json_data, &errs)) {
		throw invalid_json_exception(errs);
	}
	Inputfile.close();
	return json_data;
}

void JsonManager::Write_Json_to_file() {
	std::ofstream Outputfile;
	Outputfile.open(Gamefile);
	if (!Outputfile.is_open()) {
		throw open_file_exception(Gamefile);
	}
	Outputfile << json_data;
	Outputfile.close();
}
