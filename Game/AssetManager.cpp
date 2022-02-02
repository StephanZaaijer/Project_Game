#include "AssetManager.hpp"
#include "Exceptions.hpp"

void AssetManager::loadTextureFromFile(const std::string& name, const std::string& filename) {
    if(textures.count(name)==0){
        sf::Texture temp;
        if (temp.loadFromFile(filename)){
            textures[name]=temp;
        }
        else{
            throw LoadException("Texture", name, filename);
        }
    }
}

sf::Texture &AssetManager::getTexture(const std::string &name) {
    if (textures.count(name)==1){
        return textures.at(name);
    }
    throw ReturnException("Texture", name);
}

void AssetManager::loadFontFromFile(const std::string &name, const std::string &filename) {
    if (fonts.count(name) == 0) {
        sf::Font temp;
        if (temp.loadFromFile(filename)) {
            fonts[name] = temp;
        } else {
            throw LoadException("Fonts", name, filename);
        }
    }
}

sf::Font &AssetManager::getFont(const std::string &name){
    if (fonts.count(name)==1){
        return fonts.at(name);
    }
    throw ReturnException("Fonts", name);
}

void AssetManager::loadSoundBufferFromFile(const std::string &name, const std::string &filename){
    if(sounds.count(name)==0) {
        sf::SoundBuffer temp;
        if (temp.loadFromFile(filename)) {
            sounds[name] = temp;
        } else {
            throw LoadException("Sounds", name, filename);
        }
    }
}

sf::SoundBuffer &AssetManager::getSoundBuffer(const std::string &name) {
    if (sounds.count(name)==1){
        return sounds.at(name);
    }
    throw ReturnException("Sounds", name);
}
