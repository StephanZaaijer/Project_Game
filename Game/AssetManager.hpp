//
// Created by stephan on 18-1-2022.
//

#ifndef PROJECT_GAME_ASSETMANAGER_HPP
#define PROJECT_GAME_ASSETMANAGER_HPP
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager {
    void getTextureFromFile(const std::string &name, const std::string &Filename);
    sf::Texture &GetTexture(const std::string &name);

    void loadFontFromFile(const std::string &name, const std::string &Filename);
    sf::Font &GetFont(const std::string &name);

    void loadSoundBufferFromFile(const std::string &name, const std::string &Filename);
    sf::SoundBuffer &GetSoundBuffer(const std::string &name);


private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> sounds;
};


#endif //PROJECT_GAME_ASSETMANAGER_HPP
