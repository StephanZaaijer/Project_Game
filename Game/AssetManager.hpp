//
// Created by stephan on 18-1-2022.
//

#ifndef PROJECT_GAME_ASSETMANAGER_HPP
#define PROJECT_GAME_ASSETMANAGER_HPP
#include <map>
#include <SFML/Graphics.hpp>
#include <string.h>


#ifdef ENABLE_SOUND
    #include <SFML/Audio.hpp>
#endif //ENABLE_SOUND


class AssetManager {
public:

    AssetManager() {}
    ~AssetManager() {}


    void loadTextureFromFile(const std::string &name, const std::string &Filename);
    sf::Texture &GetTexture(const std::string &name);

    #ifdef ENABLE_FONT
        void loadFontFromFile(const std::string &name, const std::string &Filename);
        sf::Font &GetFont(const std::string &name);
    #endif //ENABLE_FONT

    #ifdef ENABLE_SOUND
        void loadSoundBufferFromFile(const std::string &name, const std::string &Filename);
        sf::SoundBuffer &GetSoundBuffer(const std::string &name);
    #endif //ENABLE_SOUND

private:
    std::map<std::string, sf::Texture> textures;
    #ifdef ENABLE_FONT
        std::map<std::string, sf::Font> fonts;
    #endif //ENABLE_FONT
    #ifdef ENABLE_SOUND
        std::map<std::string, sf::SoundBuffer> sounds;
    #endif //ENABLE_SOUND
};


#endif //PROJECT_GAME_ASSETMANAGER_HPP
