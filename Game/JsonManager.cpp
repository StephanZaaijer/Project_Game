#include "JsonManager.hpp"
#include <iostream>
JsonManager::JsonManager(std::string Gamefile):
	Gamefile(Gamefile)
{
	data = JsonData();
	Get_data();
}

void JsonManager::Get_data() {
	if (json_data == NULL){
		json_data = Get_Json_from_file();
	}
	data = {
		json_data["Audio"]["Sound"].asBool(),
		json_data["Audio"]["Soundlevel"].asInt(),
		json_data["Audio"]["Music"].asBool(),
		json_data["Audio"]["Musiclevel"].asInt(),
		json_data["Score"]["Highscore"].asInt(),
	};
	std::cout << json_data<<'\n';
}

bool JsonManager::Get_Soundstate() {
	return data.Sound;
}

int JsonManager::Get_Soundvolume() {
	return data.Soundvolume;
}

bool JsonManager::Get_Musicstate() {
	return data.Music;
}

int JsonManager::Get_Musicvolume() {
	return data.Musicvolume;
}

int JsonManager::Get_Highscore() {
	return data.Highscore;
}

void JsonManager::Set_Soundstate(bool state) {
	if (state == data.Sound) {
		return;
	}
	data.Sound = state;
	json_data["Audio"]["Sound"] = state;
	Write_Json_to_file();

}
void JsonManager::Set_Soundvolume(int volume) {
	data.Sound = true;
	json_data["Audio"]["Sound"] = true;
	if (volume == data.Soundvolume) {
		return;
	}
	data.Soundvolume = volume;
	json_data["Audio"]["Soundlevel"] = volume;
	Write_Json_to_file();
}
void JsonManager::Set_Musicstate(bool state) {
	if (state == data.Music) {
		return;
	}
	data.Sound = state;
	json_data["Audio"]["Music"] = state;
	Write_Json_to_file();
}
void JsonManager::Set_Musicvolume(int volume) {
	data.Music = true;
	json_data["Audio"]["Music"] = true;
	if (volume == data.Soundvolume) {
		return;
	}
	data.Soundvolume = volume;
	json_data["Audio"]["Musiclevel"] = volume;
	Write_Json_to_file();
}
void JsonManager::Set_Highscore(int highscore) {
	if (highscore <= data.Highscore) {
		return;
	}
	data.Highscore = highscore;
	json_data["Score"]["Highscore"] = highscore;
	Write_Json_to_file();
}

Json::Value JsonManager::Get_Json_from_file() {
	std::ifstream Inputfile;
	Json::Value json_data;
	Json::CharReaderBuilder builder;
	Inputfile.open(Gamefile);

	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, Inputfile, &json_data, &errs)) {
		json_data.clear();
		return json_data;
	}
	Inputfile.close();
	return json_data;
}

void JsonManager::Write_Json_to_file() {
	std::ofstream Outputfile;
	Outputfile.open(Gamefile);
	Outputfile << json_data;
	Outputfile.close();
}
