
L = lib

LIB_TARGET =
EXEC_TARGET = humangl

SRC =	$S/main.cpp \
			$S/HumanGL.cpp \
			$S/InitBobby.cpp \
			$S/InitBobbyPlus.cpp \
			$S/InitRoundy.cpp \
			$S/InitRoundyPlus.cpp \
			$S/Bindings.cpp \
			$S/UI/InitUI.cpp \
			$S/UI/TransformPannel.cpp \
			$S/UI/ModelPannel.cpp \
			$S/UI/AnimationListPannel.cpp \
			$S/UI/AnimationPannel.cpp \

CC = clang++ --std=c++20
CPPFLAGS = -O3 -flto
LDFLAGS = -lpthread -ldl -lGL
INCLUDE =

LIB_MOD = notrealengine
CMAKE_LIB_MOD = SDL

notrealengine_LIB = libnre.a
notrealengine_INC = inc inc/notrealengine

SDL_LIB = libSDL2.a
SDL_INC = include

LDFLAGS +=
