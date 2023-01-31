@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\lib\assimp\build-windows\lib\Release\assimp-vc142-mt.lib (

	if not exist ..\lib\notrealengine\lib\assimp\include\assimp.h (
		git submodule update --init --recursive --progress ..\lib\notrealengine\
	)
	if not exist ..\lib\notrealengine\lib\assimp\build-windows (
		md ..\lib\notrealengine\lib\assimp\build-windows
	)
	cmake -S ..\lib\notrealengine\lib\assimp\ -D BUILD_SHARED_LIBS=OFF -B ..\lib\notrealengine\lib\assimp\build-windows
	cmake --build ..\lib\notrealengine\lib\assimp\build-windows --config Release

)