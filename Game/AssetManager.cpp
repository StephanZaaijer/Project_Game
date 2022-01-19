//
// Created by stephan on 18-1-2022.
//

#include "AssetManager.hpp"

class load_exception: public std::exception{
private:
    std::string error;

public:
    load_exception(const std::string& type, const std::string& name, const std::string& filename):
        error{"Error with loading item of type: '" + type + "' with name: '" + name + "' and filename: '" + filename + "'"}
    {}
    [[nodiscard]] const char *what() const noexcept override{
        return error.c_str();
    }
};

class return_exception: public std::exception{
private:
    std::string error;

public:
    return_exception(const std::string& type, const std::string& name):
            error{"Error with returning item of type: '" + type + "' with name: '" + name + "' the item doesn't exist"}
    {}
    [[nodiscard]] const char *what() const noexcept override{
        return error.c_str();
    }
};

void AssetManager::loadTextureFromFile(const std::string& name, const std::string& Filename) {
    sf::Texture temp;

    if (temp.loadFromFile(Filename)){
        textures[name]=temp;
    }
    else{
        throw load_exception("Texture", name, Filename);
    }
}

sf::Texture &AssetManager::GetTexture(const std::string &name) {
    if (textures.count(name)==1){
        return textures.at(name);
    }
    throw return_exception("Texture", name);
}

#ifdef ENABLE_FONT
void AssetManager::loadFontFromFile(const std::string &name, const std::string &Filename){
    sf::Font temp;
    if (temp.loadFromFile(Filename)){
        fonts[name]=temp;
    }
    else{
        throw load_exception("Fonts", name, Filename);
    }
}
sf::Font &AssetManager::GetFont(const std::string &name){
    if (fonts.count(name)==1){
        return fonts.at(name);
    }
    throw return_exception("Fonts", name);
}
#endif //ENABLE_FONT

#ifdef ENABLE_SOUND

void AssetManager::loadSoundBufferFromFile(const std::string &name, const std::string &Filename){
    sf::SoundBuffer temp;
    if (temp.loadFromFile(Filename)){
        sounds[name]=temp;
    }
    else{
        throw load_exception("Sounds", name, Filename);
    }
}
sf::SoundBuffer &AssetManager::GetSoundBuffer(const std::string &name) {
    if (sounds.count(name)==1){
        return sounds.at(name);
    }
    throw return_exception("Sounds", name);
}
#endif //ENABLE_SOUND
