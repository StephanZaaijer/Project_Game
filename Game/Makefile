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
SOURCES := AssetManager.cpp Game.cpp InputManager.cpp StateMachine.cpp

# header files in this project
HEADERS := AssetManager.hpp Definitions.hpp Game.hpp GameState.hpp InputManager.hpp StateMachine.hpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
