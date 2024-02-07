@echo off
SetLocal EnableDelayedExpansion

if not exist .\x64\Release\SDL2.dll (

	if not exist ..\lib\notrealengine\lib\SDL\build-windows\Release\SDL2.lib (

		echo Buildling SDL...

		if not exist ..\lib\notrealengine\lib\SDL\include\SDL.h (
			git submodule update --init --recursive --progress ..\lib\notrealengine\
		)
		if not exist ..\lib\notrealengine\lib\SDL\build-windows (
			md ..\lib\notrealengine\lib\SDL\build-windows
		)
		cmake -S ..\lib\notrealengine\lib\SDL\ -G "Visual Studio 16 2019" -T "v142" -B ..\lib\notrealengine\lib\SDL\build-windows
		cmake --build ..\lib\notrealengine\lib\SDL\build-windows --config Release
		
	)

	echo Copying SDL2.dll...
	
	move ..\lib\notrealengine\lib\SDL\build-windows\Release\SDL2.dll .\x64\Release

)