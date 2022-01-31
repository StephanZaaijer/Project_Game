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
		json_data["Player"]["File"].asString(),
        json_data["Theme"]["ObstacleColor"].asString(),
        json_data["Theme"]["WallColor"].asString(),
		json_data["Coins"].asInt()
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

int JsonManager::Get_Coins() const {
	return data.Coins;
}

CustomCharacter JsonManager::Get_PlayerSprite() const {
	return { data.PlayerSpriteID, data.PlayerSpriteFile };
}

sf::Color JsonManager::Get_ObstacleColor() const {
    return string_to_color(data.ObstacleColor);
}

sf::Color JsonManager::Get_WallColor() const {
    return string_to_color(data.WallColor);
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

void JsonManager::Set_Coins(int coins){
	if (coins == data.Coins) {
		return;
	}
	data.Coins = coins;
	json_data["Coins"] = coins;
	clock.restart();
	write_out = true;
}

void JsonManager::Set_ObstacleColor(sf::Color ObstacleColor) {
    if (ObstacleColor == string_to_color(data.ObstacleColor)) {
        return;
    }
    data.ObstacleColor = color_to_string(ObstacleColor);
    json_data["Theme"]["ObstacleColor"]=color_to_string(ObstacleColor);
    clock.restart();
    write_out = true;
}

void JsonManager::Set_WallColor(sf::Color WallColor) {
    if (WallColor == string_to_color(data.WallColor)) {
        return;
    }
    data.WallColor = color_to_string(WallColor);
    json_data["Theme"]["WallColor"]=color_to_string(WallColor);
    clock.restart();
    write_out = true;
}

void JsonManager::Update() {
	if (write_out and clock.getElapsedTime().asSeconds() >= JSON_WRITEOUT_TIME) {
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


sf::Color JsonManager::string_to_color(std::string colorstring) const{
    for(const auto &color: colors){
        if(color.color_string==colorstring){
            return color.color_sf;
        }
    }
    throw unknown_color_exception(colorstring);
}

std::string JsonManager::color_to_string(sf::Color color_sf) const{
    for(const auto &color: colors){
        if(color.color_sf == color_sf){
            return color.color_string;
        }
    }
    throw unknown_color_exception(color_sf);
}


Json::Value JsonManager::Get_Json_from_file() {
	std::ifstream Inputfile;
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
