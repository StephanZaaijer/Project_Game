//
// Created by stephan on 18-1-2022.
//
#include "Game.hpp"
#include "AssetManager.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <SFML/Audio.hpp>
int main(){
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    std::cout << "starting window";
    AssetManager assets = AssetManager();
    assets.loadSoundBufferFromFile("test", "D:/TI_SOFTWARE/Project_Game2/Project_Game/Project_Game/Hit.wav");
    sf::Sound hit_sound;
    hit_sound.setBuffer(assets.GetSoundBuffer("test"));
    sf::Clock Clock;
    hit_sound.play();
    while (true) {
        hit_sound.play();
        //if (Clock.getElapsedTime().asSeconds() >= 2){
        //    Clock.restart();
        //}
    }
}
