#include "JsonManager.hpp"
#include <iostream>
#include <utility>
#include "Exceptions.hpp"

JsonManager::JsonManager(std::string gameFile):
	gameFile(std::move(gameFile))
{
    this->getData();
}

void JsonManager::getData() {
	jsonData = getJsonFromFile();
    std::vector<bool> boughtSkins;
    for( const auto& skin : jsonData["Bought_Skins"]){
        boughtSkins.push_back(skin.asBool());
    }
    std::vector<std::string> quotes;
    for( const auto& quote : jsonData["Quotes"]){
        quotes.push_back(quote.asString());
    }
    data = {
		jsonData["Audio"]["Sound"].asBool(),
		jsonData["Audio"]["Soundlevel"].asInt(),
		jsonData["Audio"]["Music"].asBool(),
		jsonData["Audio"]["Musiclevel"].asInt(),
		jsonData["Score"]["Highscore"].asInt(),
		jsonData["Player"]["ID"].asString(),
		jsonData["Player"]["File"].asString(),
        jsonData["Theme"]["ID"].asString(),
        jsonData["Theme"]["File"].asString(),
        jsonData["Theme"]["WallColor"].asString(),
        jsonData["Theme"]["ObstacleColor"].asString(),
		jsonData["Coins"].asInt(),
        boughtSkins,
        quotes
    };
}

bool JsonManager::getSoundState() const {
	return data.sound;
}

int JsonManager::getSoundVolume() const {
	return data.soundVolume;
}

bool JsonManager::getMusicState() const {
	return data.music;
}

int JsonManager::getMusicVolume() const {
	return data.musicVolume;
}

int JsonManager::getHighscore() const {
	return data.highscore;
}

int JsonManager::getCoins() const {
	return data.coins;
}

CustomCharacter JsonManager::getPlayerSprite() const {
	return { data.playerSpriteID, data.playerSpriteFile };
}
CustomTheme JsonManager::getPlayerTheme() const {
    return {stringToColor(data.wallColor), stringToColor(data.obstacleColor), data.playerThemeID, data.playerThemeFile };
}

sf::Color JsonManager::getObstacleColor() const {
    return stringToColor(data.obstacleColor);
}

sf::Color JsonManager::getWallColor() const {
    return stringToColor(data.wallColor);
}

std::vector<bool> JsonManager::getBoughtSkins() const{
    return data.boughtSkins;
}

std::vector<std::string> JsonManager::getQuotes() const{
    return data.quotes;
}

void JsonManager::setSoundState(const bool &state) {
	if (state == data.sound) {
		return;
	}
	data.sound = state;
	jsonData["Audio"]["Sound"] = state;
	clock.restart();
	writeOut = true;
}
void JsonManager::setSoundVolume(const int &volume) {
	if (volume == data.soundVolume) {
		return;
	}
	data.sound = volume!=0;
	jsonData["Audio"]["Sound"] = volume != 0;
	data.soundVolume = volume;
	jsonData["Audio"]["Soundlevel"] = volume;
	clock.restart();
	writeOut = true;
}
void JsonManager::setMusicState(const bool &state) {
	if (state == data.music) {
		return;
	}
	data.music = state;
	jsonData["Audio"]["Music"] = state;
	clock.restart();
	writeOut = true;
}
void JsonManager::setMusicVolume(const int &volume) {
	if (volume == data.musicVolume) {
		return;
	}
	data.music = volume != 0;
	jsonData["Audio"]["Music"] = volume != 0;
	data.musicVolume = volume;
	jsonData["Audio"]["Musiclevel"] = volume;
	clock.restart();
	writeOut = true;
}
void JsonManager::setHighscore(const int &highscore) {
	if (highscore <= data.highscore) {
		return;
	}
	data.highscore = highscore;
	jsonData["Score"]["Highscore"] = highscore;
	clock.restart();
	writeOut = true;
}

void JsonManager::setPlayerSprite(const CustomCharacter& playerSprite) {
	if (playerSprite.characterName == data.playerSpriteID) {
		return;
	}
	data.playerSpriteID = playerSprite.characterName;
	data.playerSpriteFile = playerSprite.characterFileName;
	jsonData["Player"]["ID"] = playerSprite.characterName;
	jsonData["Player"]["File"] = playerSprite.characterFileName;
	clock.restart();
	writeOut = true;
}

void JsonManager::setPlayerTheme(const CustomTheme& playerTheme) {
    if (playerTheme.themeName == data.playerThemeID) {
        return;
    }
    data.playerThemeID = playerTheme.themeName;
    data.playerThemeFile = playerTheme.themeFileName;
    data.wallColor = colorToString(playerTheme.wallColor);
    data.obstacleColor = colorToString(playerTheme.objectColor);
    jsonData["Theme"]["ID"] = playerTheme.themeName;
    jsonData["Theme"]["File"]= playerTheme.themeFileName;
    jsonData["Theme"]["WallColor"]= colorToString(playerTheme.wallColor);
    jsonData["Theme"]["ObstacleColor"] = colorToString(playerTheme.objectColor);
    clock.restart();
    writeOut = true;
}

void JsonManager::setCoins(const int &coins){
	if (coins == data.coins) {
		return;
	}
	data.coins = coins;
	jsonData["Coins"] = coins;
	clock.restart();
	writeOut = true;
}

void JsonManager::setBoughtSkins(const int &index, const bool &value) {
    if(data.boughtSkins[index]==value){
        return;
    }
    data.boughtSkins[index] = value;
    jsonData["Bought_Skins"][index] = value;
    clock.restart();
    writeOut = true;
}

void JsonManager::setQuotes(const int &index, const std::string &quote){
    if(data.quotes[index]==quote){
        return;
    }
    data.quotes[index]=quote;
    jsonData["Quotes"][index]=quote;
    clock.restart();
    writeOut=true;
}

void JsonManager::update() {
	if (writeOut and clock.getElapsedTime().asSeconds() >= JSON_WRITEOUT_TIME) {
		writeOut = false;
		writeJsonToFile();
	}
}

void JsonManager::directWrite() {
	if (writeOut) {
		writeOut = false;
		writeJsonToFile();
	}
}


sf::Color JsonManager::stringToColor(const std::string &colorString) const{
    for(const auto &color: colors){
        if(color.colorString==colorString){
            return color.colorSf;
        }
    }
    throw UnknownColorException(colorString);
}

std::string JsonManager::colorToString(const sf::Color &colorSf) const{
    for(const auto &color: colors){
        if(color.colorSf == colorSf){
            return color.colorString;
        }
    }
    throw UnknownColorException(colorSf);
}


Json::Value JsonManager::getJsonFromFile() {
	std::ifstream inputFile;
	Json::CharReaderBuilder builder;
	inputFile.open(gameFile);
	if (!inputFile.is_open()) {
		throw OpenFileException(gameFile);
	}
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, inputFile, &jsonData, &errs)) {
		throw InvalidJsonException(errs);
	}
	inputFile.close();
	return jsonData;
}

void JsonManager::writeJsonToFile() {
	std::ofstream outputFile;
	outputFile.open(gameFile);
	if (!outputFile.is_open()) {
		throw OpenFileException(gameFile);
	}
	outputFile << jsonData;
	outputFile.close();
}
