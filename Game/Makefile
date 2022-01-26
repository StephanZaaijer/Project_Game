#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
# header files in this project

SOURCES := AssetManager.cpp Character.cpp CustomCharacterState.cpp Deathwall.cpp Game.cpp GameOverState.cpp InputManager.cpp jsoncpp.cpp JsonManager.cpp MainGameState.cpp MainMenuState.cpp Musicslider.cpp ObstaclesContainer.cpp PauseState.cpp Slider.cpp SoundSettingsState.cpp Soundslider.cpp Spike.cpp StartupState.cpp StateMachine.cpp Wall.cpp

# header files in this project
HEADERS := AssetManager.hpp Character.hpp CustomCharacterState.hpp Deathwall.hpp Definitions.hpp Exceptions.hpp Game.hpp GameOverState.hpp GameState.hpp InputManager.hpp json.h json-forwards.h JsonManager.hpp MainGameState.hpp MainMenuState.hpp Musicslider.hpp Obstacle.hpp ObstaclesContainer.hpp PauseState.hpp Slider.hpp SoundSettingsState.hpp Soundslider.hpp Spike.hpp StartupState.hpp StateMachine.hpp Wall.hpp

# other places to look for files for this project
SEARCH  := ../Library/JSON/json ../Library/JSON

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
