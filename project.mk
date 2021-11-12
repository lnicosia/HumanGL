
L = lib

LIB_TARGET =
EXEC_TARGET = humangl

SRC =	$S/main.cpp \

CPPFLAGS =
LDFLAGS = -lpthread -ldl
INCLUDE =

LIB_MOD = notrealengine
CMAKE_LIB_MOD = SDL

notrealengine_LIB = libnre.a
notrealengine_INC = inc

SDL_LIB = libSDL2.a
SDL_INC = include

LDFLAGS += 
