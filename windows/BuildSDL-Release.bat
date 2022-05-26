@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\lib\SDL\build-windows\Release\SDL2.lib (

	if not exist ..\lib\notrealengine\lib\SDL\include\SDL.h (
		git submodule update --init ..\lib\notrealengine\lib\SDL
	)
	if not exist ..\lib\notrealengine\lib\SDL\build-windows (
		md ..\lib\notrealengine\lib\SDL\build-windows
	)
	cmake -S ..\lib\notrealengine\lib\SDL\ -B ..\lib\notrealengine\lib\SDL\build-windows
	cmake --build ..\lib\notrealengine\lib\SDL\build-windows --config Release
	cp ..\lib\notrealengine\lib\SDL\build-windows\Release\SDL2.dll x64\Release

)

if not exist x64\Release\SDL2.dll  (
	copy ..\lib\notrealengine\lib\SDL\build-windows\Release\SDL2.dll x64\Release
)