@echo off
SetLocal EnableDelayedExpansion

if not exist .\x64\Debug\SDL2d.dll (

	if not exist ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.lib (

		echo Buildling SDL...

		if not exist ..\lib\notrealengine\lib\SDL\include\SDL.h (
			git submodule update --init --recursive --progress ..\lib\notrealengine\
		)
		if not exist ..\lib\notrealengine\lib\SDL\build-windows (
			md ..\lib\notrealengine\lib\SDL\build-windows
		)
		cmake -S ..\lib\notrealengine\lib\SDL\ -G "Visual Studio 16 2019" -T "v142" -B ..\lib\notrealengine\lib\SDL\build-windows
		cmake --build ..\lib\notrealengine\lib\SDL\build-windows --config Debug
		
	)

	move ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.dll .\x64\Debug
	
)