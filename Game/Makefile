COMPILER = c++
CFLAGS_LINUX = -I ../Library/JSON/json/ -I ../Library/JSON/ -I ./

.DEFAULT_GOAL := all
.PHONY: all run build clean

all: run

build: JuuJuu.out

run: build
	@echo "Starting JuuJuu..."
	@./JuuJuu.out

AssetManager.o: AssetManager.cpp AssetManager.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Character.o: Character.cpp Character.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Coin.o: Coin.cpp Coin.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

CoinContainer.o: CoinContainer.cpp CoinContainer.hpp Coin.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

CustomCharacterState.o: CustomCharacterState.cpp CustomCharacterState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Deathwall.o: Deathwall.cpp Deathwall.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Game.o: Game.cpp Game.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

GameOverState.o: GameOverState.cpp GameOverState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

InputManager.o: InputManager.cpp InputManager.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

jsoncpp.o: ../Library/JSON/jsoncpp.cpp ../Library/JSON/json/json.h ../Library/JSON/json/json-forwards.h
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

JsonManager.o: JsonManager.cpp JsonManager.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Main.o: main.cpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

MainGameState.o: MainGameState.cpp MainGameState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

MainMenuState.o: MainMenuState.cpp MainMenuState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Musicslider.o: Musicslider.cpp Musicslider.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

ObstaclesContainer.o: ObstaclesContainer.cpp ObstaclesContainer.hpp Obstacle.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

PauseState.o: PauseState.cpp PauseState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Slider.o: Slider.cpp Slider.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

SoundSettingsState.o: SoundSettingsState.cpp SoundSettingsState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Soundslider.o: Soundslider.cpp Soundslider.hpp Slider.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Spike.o: Spike.cpp Spike.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

StartUpState.o: StartUpState.cpp StartUpState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

StateMachine.o: StateMachine.cpp StateMachine.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

TutorialState.o: TutorialState.cpp TutorialState.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Wall.o: Wall.cpp Wall.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Line.o: Line.cpp Line.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

JuuJuu.out: AssetManager.o Character.o Coin.o CoinContainer.o CustomCharacterState.o Deathwall.o Game.o GameOverState.o InputManager.o jsoncpp.o JsonManager.o Main.o MainGameState.o MainMenuState.o Musicslider.o ObstaclesContainer.o PauseState.o Slider.o SoundSettingsState.o Soundslider.o Spike.o StartUpState.o StateMachine.o TutorialState.o Wall.o Line.o
	@echo "Linking $@..."
	@$(COMPILER) $(CFLAGS_LINUX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *.out