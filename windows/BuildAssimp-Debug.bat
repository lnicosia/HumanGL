@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\lib\assimp\build-windows\lib\Debug\assimp-vc142-mtd.lib (

	echo Buildling assimp...

	if not exist ..\lib\notrealengine\lib\assimp\include\assimp.h (
		git submodule update --init --recursive --progress ..\lib\notrealengine\
	)
	if not exist ..\lib\notrealengine\lib\assimp\build-windows (
		md ..\lib\notrealengine\lib\assimp\build-windows
	)
	cmake -S ..\lib\notrealengine\lib\assimp\ -G "Visual Studio 16 2019" -T "v142" -D ASSIMP_BUILD_ZLIB=ON -B ..\lib\notrealengine\lib\assimp\build-windows
	cmake --build ..\lib\notrealengine\lib\assimp\build-windows --config Debug
		
)