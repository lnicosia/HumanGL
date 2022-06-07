
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
LDFLAGS = -lGL -ldl -lpthread
INCLUDE =

LIB_MOD = notrealengine
CMAKE_LIB_MOD = SDL 

ifdef USING_EXTERNAL
notrealengine_LIB = libnre-external.a
CMAKE_LIB_MOD += assimp freetype
CPPFLAGS += -D USING_EXTERNAL_LIBS
LDFLAGS += -lz -lpng -lharfbuzz -lbz2
else
notrealengine_LIB = libnre.a
endif
notrealengine_INC = inc inc/notrealengine

SDL_DIR = lib/notrealengine/lib/SDL
SDL_LIB = libSDL2.a
SDL_INC = include

assimp_DIR = lib/notrealengine/lib/assimp
assimp_LIB = lib/libassimp.a
assimp_INC = include build/include

freetype_DIR = lib/notrealengine/lib/freetype
freetype_LIB = libfreetype.a
freetype_INC = include

LDFLAGS +=
