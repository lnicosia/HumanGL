@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\SDL\build-windows\Debug\SDL2d.lib (

	if not exist ..\lib\SDL\include\SDL.h (
		git submodule update --init ..\lib\SDL
	)
	if not exist ..\lib\SDL\build-windows (
		md ..\lib\SDL\build-windows
	)
	cmake -S ..\lib\SDL\ -B ..\lib\SDL\build-windows
	cmake --build ..\lib\SDL\build-windows --config Debug
	cp ..\lib\SDL\build-windows\Debug\SDL2d.dll x64\Debug
		
)

if not exist x64\Debug\SDL2.dll  (
	copy ..\lib\SDL\build-windows\Debug\SDL2d.dll x64\Debug
)