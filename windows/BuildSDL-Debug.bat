@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.lib (

	if not exist ..\lib\notrealengine\lib\SDL\include\SDL.h (
		git submodule update --init ..\lib\notrealengine\lib\SDL
	)
	if not exist ..\lib\notrealengine\lib\SDL\build-windows (
		md ..\lib\notrealengine\lib\SDL\build-windows
	)
	cmake -S ..\lib\notrealengine\lib\SDL\ -B ..\lib\notrealengine\lib\SDL\build-windows
	cmake --build ..\lib\notrealengine\lib\SDL\build-windows --config Debug
	cp ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.dll x64\Debug
		
)

if not exist x64\Debug\SDL2.dll  (
	copy ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.dll x64\Debug
)