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
SOURCES := AssetManager.cpp Game.cpp InputManager.cpp StateMachine.cpp MainGameState.cpp Wall.cpp SoundSettingsState.cpp StartupState.cpp MainMenuState.cpp GameOverState.cpp Character.cpp JsonManager.cpp jsoncpp.cpp Spike.cpp ObstaclesContainer.cpp PauseState.cpp

# header files in this project
HEADERS := AssetManager.hpp Definitions.hpp Game.hpp GameState.hpp InputManager.hpp StateMachine.hpp MainGameState.hpp Wall.hpp SoundSettingsState.hpp StartupState.hpp MainMenuState.hpp GameOverState.hpp Character.hpp JsonManager.hpp json.h json-forwards.h Exceptions.hpp Obstacle.hpp Spike.hpp ObstaclesContainer.hpp PauseState.hpp

# other places to look for files for this project
SEARCH  := ../Library/JSON/json ../Library/JSON

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
