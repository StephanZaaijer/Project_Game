#include "CustomCharacterState.hpp"
#include <utility>

CustomCharacterState::CustomCharacterState(GameDataReference data) :
        game_data(std::move(data)) {
    coins = game_data->json.Get_Coins();
}

void CustomCharacterState::Init() {
    game_data->assets.loadFontFromFile("Bauhaus font", BAUHAUS_FONT_PATH);

    game_data->assets.loadSoundBufferFromFile("_clickSound", SOUND_CLICK_PATH);
    game_data->assets.loadSoundBufferFromFile("_customClickSound", SOUND_CLICK_CUSTOM_PATH);

    game_data->assets.loadTextureFromFile("Random Button", RANDOM_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Right", ARROW_RIGHT_BUTTON);
    game_data->assets.loadTextureFromFile("Arrow Left", ARROW_LEFT_BUTTON);
    game_data->assets.loadTextureFromFile("Back Button", BACK_BUTTON_PATH);

    _clickSound.setBuffer(game_data->assets.GetSoundBuffer("_clickSound"));
    _customClickSound.setBuffer(game_data->assets.GetSoundBuffer("_customClickSound"));

    _clickSound.setVolume(game_data->json.Get_Soundvolume());
    _customClickSound.setVolume(game_data->json.Get_Soundvolume());

    _coins_text.setFont(game_data->assets.GetFont("Bauhaus font"));
    _coins_text.setCharacterSize(60);
    _coins_text.setFillColor(TEXT_COLOR);
    _coins_text.setString("Coins: " + std::to_string(coins));
    _coins_text.setPosition(SCREEN_WIDTH / 1.2f, SCREEN_HEIGHT / 20.0f);

    counter_Characters = 0;
    character = std::unique_ptr<Character>(new Character(game_data));
    CurrentCharacter = game_data->json.Get_PlayerSprite();
    bool found=false;
    for (const auto &characters: CustomCharacters) {
        game_data->assets.loadTextureFromFile(characters.CharacterName, characters.CharacterFileName);
        if(!found){
            if (characters == CurrentCharacter) {
                found=true;
            }
            counter_Characters++;
        }
    }
    if (counter_Characters > CustomCharacters.size()) {
        counter_Characters = 0;
        CurrentCharacter = CustomCharacters[counter_Characters];
    }

    counter_Theme = 0;
    CurrentTheme = game_data->json.Get_PlayerTheme();
    found = false;
    for (const auto &themes: CustomThemes) {
        game_data->assets.loadTextureFromFile(themes.themeName, themes.themeFileName);
        if(!found){
            if (themes == CurrentTheme) {
                found=true;
            }
            counter_Theme++;
        }
    }
    if (counter_Theme > CustomThemes.size()) {
        counter_Theme = 0;
        CurrentTheme = CustomThemes[counter_Theme];
    }

    character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
    character->getSprite().setScale(2, 2);
    character->getSprite().setPosition(SCREEN_WIDTH / 2.0f - (character->getSprite().getGlobalBounds().width / 2),
                                       SCREEN_HEIGHT / 3.0f - (character->getSprite().getGlobalBounds().height));

    _theme.setTexture(game_data->assets.GetTexture(CurrentTheme.themeName));
    _theme.setPosition(SCREEN_WIDTH / 2.0f - (character->getSprite().getGlobalBounds().width / 2),
                       SCREEN_HEIGHT / 1.5f - (character->getSprite().getGlobalBounds().height));

    _backButton.setTexture(game_data->assets.GetTexture("Back Button"));
    _background.setTexture(game_data->assets.GetTexture("Background"));
    _randomButtonCharacter.setTexture(game_data->assets.GetTexture("Random Button"));
    _arrowLeftCharacter.setTexture(game_data->assets.GetTexture("Arrow Left"));
    _arrowRightCharacter.setTexture(game_data->assets.GetTexture("Arrow Right"));
    _randomButtonTheme.setTexture(game_data->assets.GetTexture("Random Button"));
    _arrowLeftTheme.setTexture(game_data->assets.GetTexture("Arrow Left"));
    _arrowRightTheme.setTexture(game_data->assets.GetTexture("Arrow Right"));

    _backButton.setPosition(SCREEN_WIDTH / 2.0f - (_backButton.getGlobalBounds().width / 2),
                            SCREEN_HEIGHT - (_backButton.getGlobalBounds().height * 1.1));
    _randomButtonCharacter.setPosition(SCREEN_WIDTH / 8.0f - (_randomButtonCharacter.getGlobalBounds().width / 2),
                                       SCREEN_HEIGHT / 3.0f - (_randomButtonCharacter.getGlobalBounds().height));
    _arrowLeftCharacter.setPosition(SCREEN_WIDTH / 3.0f - (_arrowLeftCharacter.getGlobalBounds().width / 2),
                                    SCREEN_HEIGHT / 3.0f - (_arrowLeftCharacter.getGlobalBounds().height));
    _arrowRightCharacter.setPosition(SCREEN_WIDTH / 6.0f * 4.0f - (_arrowRightCharacter.getGlobalBounds().width / 2),
                                     SCREEN_HEIGHT / 3.0f - (_arrowRightCharacter.getGlobalBounds().height));

    _randomButtonTheme.setPosition(SCREEN_WIDTH / 8.0f - (_randomButtonTheme.getGlobalBounds().width / 2),
                                   SCREEN_HEIGHT / 1.5f - (_randomButtonTheme.getGlobalBounds().height));
    _arrowLeftTheme.setPosition(SCREEN_WIDTH / 3.0f - (_arrowLeftTheme.getGlobalBounds().width / 2),
                                SCREEN_HEIGHT / 1.5f - (_arrowLeftTheme.getGlobalBounds().height));
    _arrowRightTheme.setPosition(SCREEN_WIDTH / 6.0f * 4.0f - (_arrowRightTheme.getGlobalBounds().width / 2),
                                 SCREEN_HEIGHT / 1.5f - (_arrowRightTheme.getGlobalBounds().height));
    std::cout<<"init done\n";
}

void CustomCharacterState::HandleInput() {
    sf::Event event{};
    while (game_data->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_data->json.Set_PlayerSprite(CurrentCharacter);
            game_data->json.Set_PlayerTheme(CurrentTheme);
            game_data->window.close();
        }
        if (game_data->input.ChangeMouseWhenHoveringOverButton(ClickableButtons, game_data->window)) {
            if (!prevMousestate) {
                if (game_data->input.IsSpriteClicked(_arrowRightCharacter, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _customClickSound.play();
                    }
                    if (counter_Characters == CustomCharacters.size() - 1) {
                        counter_Characters = 0;
                    } else {
                        counter_Characters += 1;
                    }
                    CurrentCharacter = CustomCharacters[counter_Characters];
                    character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
                }

                if (game_data->input.IsSpriteClicked(_arrowLeftCharacter, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _customClickSound.play();
                    }
                    if (counter_Characters == 0) {
                        counter_Characters = CustomCharacters.size() - 1;
                    } else {
                        counter_Characters -= 1;
                    }
                    CurrentCharacter = CustomCharacters[counter_Characters];
                    character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
                }

                if (game_data->input.IsSpriteClicked(_randomButtonCharacter, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _customClickSound.play();
                    }
                    for (int i = 0; i < 10 + std::rand() % 40; i++) {
                        counter_Characters = std::rand() % CustomCharacters.size();
                        while (CurrentCharacter == CustomCharacters[counter_Characters]) {
                            counter_Characters = std::rand() % CustomCharacters.size();
                        }
                        CurrentCharacter = CustomCharacters[counter_Characters];
                        character->getSprite().setTexture(game_data->assets.GetTexture(CurrentCharacter.CharacterName));
                        Draw(0);
                        sf::sleep(sf::milliseconds(20 + i * 10));
                    }
                }

                if (game_data->input.IsSpriteClicked(_arrowRightTheme, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _customClickSound.play();
                    }
                    if (counter_Theme == CustomThemes.size() - 1) {
                        counter_Theme = 0;
                    } else {
                        counter_Theme += 1;
                    }
                    CurrentTheme = CustomThemes[counter_Theme];
                    _theme.setTexture(game_data->assets.GetTexture(CurrentTheme.themeName));
                }
                if (game_data->input.IsSpriteClicked(_arrowLeftTheme, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _customClickSound.play();
                    }
                    if (counter_Theme == 0) {
                        counter_Theme = CustomThemes.size() - 1;
                    } else {
                        counter_Theme -= 1;
                    }
                    CurrentTheme = CustomThemes[counter_Theme];
                    _theme.setTexture(game_data->assets.GetTexture(CurrentTheme.themeName));
                }
                if (game_data->input.IsSpriteClicked(_randomButtonTheme, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _customClickSound.play();
                    }
                }

                if (game_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, game_data->window)) {
                    if (game_data->json.Get_Soundstate()) {
                        _clickSound.play();
                    }
                    game_data->json.Set_PlayerSprite(CurrentCharacter);
                    game_data->json.Set_PlayerTheme(CurrentTheme);
                    game_data->machine.RemoveGameState();
                }
            }
        }
        prevMousestate = game_data->input.IsButtonPressed(sf::Mouse::Left);
    }
}

void CustomCharacterState::Update(float delta) {}

void CustomCharacterState::Draw(float delta) {
    game_data->window.clear();
    game_data->window.draw(_background);
    game_data->window.draw(_backButton);
    game_data->window.draw(_randomButtonCharacter);
    game_data->window.draw(_arrowRightCharacter);
    game_data->window.draw(_arrowLeftCharacter);
    game_data->window.draw(_randomButtonTheme);
    game_data->window.draw(_arrowRightTheme);
    game_data->window.draw(_arrowLeftTheme);
    game_data->window.draw(_coins_text);
    game_data->window.draw(_theme);
    character->Draw();
    game_data->window.display();
}
