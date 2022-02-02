#ifndef PROJECT_GAME_ASSETMANAGER_HPP
#define PROJECT_GAME_ASSETMANAGER_HPP
#include <map>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "Definitions.hpp"
#include <SFML/Audio.hpp>

/// @file AssetManager.hpp
/// @brief
/// Project_Game: AssetManager to read and store textures, fonts and soundbuffers

/// @brief
/// Class that stores all the assets(sf::Textures, sf::SoundBuffers and sf::Fonts)
class AssetManager {
public:
    /// @brief
    /// Function to load a sf::Texture into the assetmanager from a file
    /// @details
    /// Function to read sf::Texture from file and store it in the assetmanager. Throws a LoadException if there is an error while opening.
    /// And does nothing when there already is a texture with the same name stored in the assetmanager.
    /// \param name The name that`s used as a key to store and retrieve the sf::Texture from the AssetManager.
    /// \param filename The name from which the sf::Texture needs to be loaded.
    void loadTextureFromFile(const std::string &name, const std::string &filename);

    /// @brief
    /// Function to get sf::Texture that`s stored in the assetmanager.
    /// @details
    /// Function to get sf::Texture that`s stored in the assetmanager. Throws an ReturnException if there is no sf::Texture stored in the assetmanager with that key.
    /// \param name The key that`s used to load the sf::Texture into the assetmanager.
    /// \return The sf::Texture that`s stored with that particular key.
    sf::Texture &getTexture(const std::string &name);

    /// @brief
    /// Function to load sf::Font into the assetmanager from a fontfile.
    /// @details
    /// Function to read sf::Font from file and store it in the assetmanager. Throws a LoadException if there is an error while opening.
    /// And does nothing when there already is a sf::Font with the same name stored in the assetmanager.
    /// \param name The name that`s used as a key to store and retrieve the sf::Font from the AssetManager
    /// \param filename The name from which the sf::Font needs to be loaded
    void loadFontFromFile(const std::string &name, const std::string &filename);

    /// @brief
    /// Function to get sf::Font that`s stored in the assetmanager.
    /// @details
    /// Function to get sf::Font that`s stored in the assetmanager. Throws an ReturnException if there is no sf::Font stored in the assetmanager with that key.
    /// \param name The key that`s used to load the sf::Font into the assetmanager.
    /// \return The sf::Font that`s stored with that particular key.
    sf::Font &getFont(const std::string &name);

    /// @brief
    /// Function to load sf::SoundBuffer into the assetmanager from a Soundfile
    /// @details
    /// Function to read sf::SoundBuffer from file and store it in the assetmanager. Throws a LoadException if there is an error while opening.
    /// And does nothing when there already is a sf::SoundBuffer with the same name stored in the assetmanager.
    /// \param name The name that`s used as a key to store and retrieve the sf::SoundBuffer from the AssetManager
    /// \param filename The name from which the sf::SoundBuffer needs to be loaded
    void loadSoundBufferFromFile(const std::string &name, const std::string &filename);

    /// @brief
    /// Function to get sf::SoundBuffer that`s stored in the assetmanager.
    /// @details
    /// Function to get sf::SoundBuffer that`s stored in the assetmanager. Throws an ReturnException if there is no sf::SoundBuffer stored in the assetmanager with that key.
    /// \param name The key that`s used to load the sf::SoundBuffer into the assetmanager.
    /// \return The sf::SoundBuffer that`s stored with that particular key.
    sf::SoundBuffer &getSoundBuffer(const std::string &name);

private:
    std::map<std::string, sf::SoundBuffer> sounds;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};


#endif //PROJECT_GAME_ASSETMANAGER_HPP
