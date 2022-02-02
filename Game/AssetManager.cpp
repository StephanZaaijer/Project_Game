#include "AssetManager.hpp"
#include "Exceptions.hpp"

void AssetManager::loadTextureFromFile(const std::string& name, const std::string& Filename) {
    if(textures.count(name)==0){
        sf::Texture temp;
        if (temp.loadFromFile(Filename)){
            textures[name]=temp;
        }
        else{
            throw load_exception("Texture", name, Filename);
        }
    }
}

sf::Texture &AssetManager::GetTexture(const std::string &name) {
    if (textures.count(name)==1){
        return textures.at(name);
    }
    throw return_exception("Texture", name);
}

void AssetManager::loadFontFromFile(const std::string &name, const std::string &Filename) {
    if (fonts.count(name) == 0) {
        sf::Font temp;
        if (temp.loadFromFile(Filename)) {
            fonts[name] = temp;
        } else {
            throw load_exception("Fonts", name, Filename);
        }
    }
}

sf::Font &AssetManager::GetFont(const std::string &name){
    if (fonts.count(name)==1){
        return fonts.at(name);
    }
    throw return_exception("Fonts", name);
}

void AssetManager::loadSoundBufferFromFile(const std::string &name, const std::string &Filename){
    if(sounds.count(name)==0) {
        sf::SoundBuffer temp;
        if (temp.loadFromFile(Filename)) {
            sounds[name] = temp;
        } else {
            throw load_exception("Sounds", name, Filename);
        }
    }
}

sf::SoundBuffer &AssetManager::GetSoundBuffer(const std::string &name) {
    if (sounds.count(name)==1){
        return sounds.at(name);
    }
    throw return_exception("Sounds", name);
}
