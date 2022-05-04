@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\SDL\build-windows\Release\SDL2.lib (

	if not exist ..\lib\SDL\include\SDL.h (
		git submodule update --init ..\lib\SDL
	)
	if not exist ..\lib\SDL\build-windows (
		md ..\lib\SDL\build-windows
	)
	cmake -S ..\lib\SDL\ -B ..\lib\SDL\build-windows
	cmake --build ..\lib\SDL\build-windows --config Release
	cp ..\lib\SDL\build-windows\Release\SDL2.dll x64\Release

)

if not exist x64\Release\SDL2.dll  (
	copy ..\lib\SDL\build-windows\Release\SDL2.dll x64\Release
)