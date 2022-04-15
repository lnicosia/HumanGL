
L = lib

LIB_TARGET =
EXEC_TARGET = humangl

SRC =	$S/main.cpp \
			$S/HumanGL.cpp \
			$S/InitBobby.cpp \
			$S/Bindings.cpp \

CPPFLAGS = --std=c++20 -O3
LDFLAGS = -lpthread -ldl -lGL
INCLUDE =

LIB_MOD = notrealengine
CMAKE_LIB_MOD = SDL

notrealengine_LIB = libnre.a
notrealengine_INC = inc inc/notrealengine

SDL_LIB = libSDL2.a
SDL_INC = include

LDFLAGS +=
