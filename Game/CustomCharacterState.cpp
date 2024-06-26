#include "CustomCharacterState.hpp"
#include <utility>
#include <iostream>

CustomCharacterState::CustomCharacterState(GameDataReference gameData) :
    gameData(std::move(gameData))
{
    coins = this->gameData->json.getCoins();
    skinBought = this->gameData->json.getBoughtSkins();
}

void CustomCharacterState::init() {
    clickSound.setBuffer(gameData->assets.getSoundBuffer("clickSound"));
    customClickSound.setBuffer(gameData->assets.getSoundBuffer("customClickSound"));
    clickSound.setVolume(gameData->json.getSoundVolume());
    customClickSound.setVolume(gameData->json.getSoundVolume());

    backButton.setTexture(gameData->assets.getTexture("Back Button"));
    background.setTexture(gameData->assets.getTexture("Background"));
    randomButtonCharacter.setTexture(gameData->assets.getTexture("Random Button"));
    arrowLeftCharacter.setTexture(gameData->assets.getTexture("Arrow Left"));
    arrowRightCharacter.setTexture(gameData->assets.getTexture("Arrow Right"));
    randomButtonTheme.setTexture(gameData->assets.getTexture("Random Button"));
    arrowLeftTheme.setTexture(gameData->assets.getTexture("Arrow Left"));
    arrowRightTheme.setTexture(gameData->assets.getTexture("Arrow Right"));
    equipButtonTheme.setTexture(gameData->assets.getTexture("Equip Button"));

    coinsText.setFont(gameData->assets.getFont("Bauhaus"));
    coinsText.setCharacterSize(60);
    coinsText.setFillColor(TEXT_COLOR);
    coinsText.setString("coins: " + std::to_string(coins));
    coinsText.setPosition(SCREEN_WIDTH / 1.2f, SCREEN_HEIGHT / 20.0f);

    equippedCharacter.setFont(gameData->assets.getFont("Bauhaus"));
    equippedCharacter.setCharacterSize(30);
    equippedCharacter.setFillColor(TEXT_COLOR);
    equippedCharacter.setString("EQUIPPED");

     auto tmpRect = equippedCharacter.getLocalBounds();
    equippedCharacter.setOrigin(tmpRect.left + tmpRect.width / 2,
        tmpRect.top + tmpRect.height / 2);
    equippedCharacter.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 10.0f);

    equippedTheme.setFont(gameData->assets.getFont("Bauhaus"));
    equippedTheme.setCharacterSize(30);
    equippedTheme.setFillColor(TEXT_COLOR);
    equippedTheme.setString("EQUIPPED");

    tmpRect = equippedTheme.getLocalBounds();
    equippedTheme.setOrigin(tmpRect.left + tmpRect.width / 2,
                                tmpRect.top + tmpRect.height / 2);
    equippedTheme.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.3f);

    counterCharacters = 0;
    character = std::unique_ptr<Character>(new Character(gameData));
    currentCharacter = gameData->json.getPlayerSprite();
    bool found = false;
    for (const auto &characters: customCharacters) {
        gameData->assets.loadTextureFromFile(characters.characterName, characters.characterFileName);
        if (!found) {
            if (characters == currentCharacter) {
                found = true;
            } else {
                counterCharacters++;
            }
        }
    }
    if (counterCharacters > (int) customCharacters.size() - 1) {
        counterCharacters = 0;
    }
    currentCharacter = customCharacters[counterCharacters];

    buyEquipButton.setTexture(gameData->assets.getTexture("Equip Button"));

    counterTheme = 0;
    currentTheme = gameData->json.getPlayerTheme();
    found = false;
    for (const auto &themes: customThemes) {
        gameData->assets.loadTextureFromFile(themes.themeName, themes.themeFileName);
        if (!found) {
            if (themes == currentTheme) {
                found = true;
            } else {
                counterTheme++;
            }
        }
    }
    if (counterTheme > (int) customThemes.size() - 1) {
        counterTheme = 0;
    }
    currentTheme = customThemes[counterTheme];

    character->setTexture(gameData->assets.getTexture(currentCharacter.characterName));
    character->setScale(2);
    character->setPosition({SCREEN_WIDTH / 2.0f - (character->getGlobalBounds().width / 2),
                            SCREEN_HEIGHT / 3.0f - (character->getGlobalBounds().height)});

    theme.setTexture(gameData->assets.getTexture(currentTheme.themeName));
    theme.setScale(2, 2);
    theme.setPosition(SCREEN_WIDTH / 2.0f - (character->getGlobalBounds().width / 2),
                       SCREEN_HEIGHT / 1.5f - (character->getGlobalBounds().height));

    backButton.setPosition(SCREEN_WIDTH / 2.0f - (backButton.getGlobalBounds().width / 2),
                            SCREEN_HEIGHT - (backButton.getGlobalBounds().height * 1.1));
    buyEquipButton.setPosition(SCREEN_WIDTH / 8.0f * 6.5f - (buyEquipButton.getGlobalBounds().width / 2),
                                SCREEN_HEIGHT / 3.3f - (buyEquipButton.getGlobalBounds().height));
    randomButtonCharacter.setPosition(SCREEN_WIDTH / 8.0f - (randomButtonCharacter.getGlobalBounds().width / 2),
                                       SCREEN_HEIGHT / 3.0f - (randomButtonCharacter.getGlobalBounds().height));
    arrowLeftCharacter.setPosition(SCREEN_WIDTH / 3.0f - (arrowLeftCharacter.getGlobalBounds().width / 2),
                                    SCREEN_HEIGHT / 3.0f - (arrowLeftCharacter.getGlobalBounds().height));
    arrowRightCharacter.setPosition(SCREEN_WIDTH / 6.0f * 4.0f - (arrowRightCharacter.getGlobalBounds().width / 2),
                                     SCREEN_HEIGHT / 3.0f - (arrowRightCharacter.getGlobalBounds().height));

    equipButtonTheme.setPosition(SCREEN_WIDTH / 8.0f * 6.5f - (equipButtonTheme.getGlobalBounds().width / 2),
                                SCREEN_HEIGHT /1.59f - (equipButtonTheme.getGlobalBounds().height));
    randomButtonTheme.setPosition(SCREEN_WIDTH / 8.0f - (randomButtonTheme.getGlobalBounds().width / 2),
                                   SCREEN_HEIGHT / 1.5f - (randomButtonTheme.getGlobalBounds().height));
    arrowLeftTheme.setPosition(SCREEN_WIDTH / 3.0f - (arrowLeftTheme.getGlobalBounds().width / 2),
                                SCREEN_HEIGHT / 1.5f - (arrowLeftTheme.getGlobalBounds().height));
    arrowRightTheme.setPosition(SCREEN_WIDTH / 6.0f * 4.0f - (arrowRightTheme.getGlobalBounds().width / 2),
                                 SCREEN_HEIGHT / 1.5f - (arrowRightTheme.getGlobalBounds().height));
}

void CustomCharacterState::handleInput() {
    sf::Event event{};
    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        if (skinBought[counterCharacters]) {
            buyEquipButton.setTexture(gameData->assets.getTexture("Equip Button"));
        } else {
            buyEquipButton.setTexture(gameData->assets.getTexture("Buy Button"));
        }

        if(currentCharacter.characterName == gameData->json.getPlayerSprite().characterName){
            equippedCharacter.setString("EQUIPPED");
        }else if (skinBought[counterCharacters]){
            equippedCharacter.setString("");
        }
        else{
            equippedCharacter.setString(std::to_string(SKIN_PRICE) + " coins");
        }

        if(currentTheme.themeName == gameData->json.getPlayerTheme().themeName){
            equippedTheme.setString("EQUIPPED");
        }else{
            equippedTheme.setString("");
        }

        if (gameData->input.changeMouseWhenHoveringOverButton(clickableButtons, gameData->window)) {
            if (!prevMouseState) {
                if (gameData->input.isSpriteClicked(arrowRightCharacter, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        customClickSound.play();
                    }
                    if (counterCharacters == (int) customCharacters.size() - 1) {
                        counterCharacters = 0;
                    } else {
                        counterCharacters += 1;
                    }
                    currentCharacter = customCharacters[counterCharacters];
                    character->setTexture(gameData->assets.getTexture(currentCharacter.characterName));
                }

                if (gameData->input.isSpriteClicked(arrowLeftCharacter, sf::Mouse::Left, gameData->window)) {
                    if(currentCharacter.characterName == gameData->json.getPlayerSprite().characterName){
                        equippedCharacter.setString("EQUIPPED");
                    }else{
                        equippedCharacter.setString("");
                    }
                    if (gameData->json.getSoundState()) {
                        customClickSound.play();
                    }
                    if (counterCharacters == 0) {
                        counterCharacters = (int) customCharacters.size() - 1;
                    } else {
                        counterCharacters -= 1;
                    }
                    currentCharacter = customCharacters[counterCharacters];
                    character->setTexture(gameData->assets.getTexture(currentCharacter.characterName));
                }

                if (gameData->input.isSpriteClicked(randomButtonCharacter, sf::Mouse::Left, gameData->window)) {
                    equippedCharacter.setString("");
                    for (int i = 0; i < 10 + std::rand() % 40; i++) {
                        if (gameData->json.getSoundState()) {
                            customClickSound.play();
                        }
                        counterCharacters = std::rand() % customCharacters.size();
                        while ((currentCharacter == customCharacters[counterCharacters]) || (!skinBought[counterCharacters])) {
                            counterCharacters = std::rand() % customCharacters.size();
                        }
                        currentCharacter = customCharacters[counterCharacters];
                        character->setTexture(gameData->assets.getTexture(currentCharacter.characterName));
                        draw();
                        sf::sleep(sf::milliseconds(20 + i * 10));
                    }
                    gameData->json.setPlayerSprite(currentCharacter);
                }

                if (gameData->input.isSpriteClicked(buyEquipButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        customClickSound.play();
                    }
                    //if skin not bought (buy button)
                    if (!skinBought[counterCharacters]) {
                        if (coins >= SKIN_PRICE) {
                            coins -= SKIN_PRICE;
                            coinsText.setString("coins: " + std::to_string(coins));
                            skinBought[counterCharacters] = true;
                            character->setTexture(gameData->assets.getTexture(currentCharacter.characterName));
                            gameData->json.setCoins(coins);
                            gameData->json.setBoughtSkins(counterCharacters, true);
                            equippedCharacter.setString("EQUIPPED");
                            gameData->json.setPlayerSprite(currentCharacter);
                        }
                    } else {
                        equippedCharacter.setString("EQUIPPED");
                        character->setTexture(gameData->assets.getTexture(currentCharacter.characterName));
                        gameData->json.setPlayerSprite(currentCharacter);
                    }
                }

                if (gameData->input.isSpriteClicked(arrowRightTheme, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        customClickSound.play();
                    }
                    if (counterTheme == (int) customThemes.size() - 1) {
                        counterTheme = 0;
                    } else {
                        counterTheme += 1;
                    }
                    currentTheme = customThemes[counterTheme];
                    theme.setTexture(gameData->assets.getTexture(currentTheme.themeName));

                }

                if (gameData->input.isSpriteClicked(arrowLeftTheme, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        customClickSound.play();
                    }
                    if (counterTheme == 0) {
                        counterTheme = (int) customThemes.size() - 1;
                    } else {
                        counterTheme -= 1;
                    }
                    currentTheme = customThemes[counterTheme];
                    theme.setTexture(gameData->assets.getTexture(currentTheme.themeName));
                }

                if (gameData->input.isSpriteClicked(randomButtonTheme, sf::Mouse::Left, gameData->window)) {
                    equippedTheme.setString("");
                    for (int i = 0; i < 10 + std::rand() % 40; i++) {
                        if (gameData->json.getSoundState()) {
                            customClickSound.play();
                        }
                        counterTheme = std::rand() % customThemes.size();
                        while (currentTheme == customThemes[counterTheme]) {
                            counterTheme = std::rand() % customThemes.size();
                        }
                        currentTheme = customThemes[counterTheme];
                        theme.setTexture(gameData->assets.getTexture(currentTheme.themeName));
                        draw();
                        sf::sleep(sf::milliseconds(20 + i * 10));
                    }
                    gameData->json.setPlayerTheme(currentTheme);
                }

                if (gameData->input.isSpriteClicked(equipButtonTheme, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        customClickSound.play();
                    }
                    equippedTheme.setString("EQUIPPED");
                    gameData->json.setPlayerTheme(currentTheme);
                }

                if (gameData->input.isSpriteClicked(backButton, sf::Mouse::Left, gameData->window)) {
                    if (gameData->json.getSoundState()) {
                        clickSound.play();
                    }
                    gameData->machine.removeGameState();
                }
            }
        }
        prevMouseState = gameData->input.isButtonPressed(sf::Mouse::Left);
    }
}

void CustomCharacterState::draw() {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(backButton);
    gameData->window.draw(randomButtonCharacter);
    gameData->window.draw(arrowRightCharacter);
    gameData->window.draw(arrowLeftCharacter);
    gameData->window.draw(randomButtonTheme);
    gameData->window.draw(arrowRightTheme);
    gameData->window.draw(arrowLeftTheme);
    gameData->window.draw(coinsText);
    gameData->window.draw(theme);
    gameData->window.draw(buyEquipButton);
    gameData->window.draw(equipButtonTheme);
    gameData->window.draw(equippedCharacter);
    gameData->window.draw(equippedTheme);
    character->draw();
    gameData->window.display();
}
