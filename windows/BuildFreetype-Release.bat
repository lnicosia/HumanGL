@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\lib\freetype\build-windows\Release\freetype.lib (

	echo Buildling freetype...

	if not exist ..\lib\notrealengine\lib\freetype\include\freetype.h (
		git submodule update --init --recursive --progress ..\lib\notrealengine\
	)
	if not exist ..\lib\notrealengine\lib\freetype\build-windows (
		md ..\lib\notrealengine\lib\freetype\build-windows
	)
	cmake -S ..\lib\notrealengine\lib\freetype\ -B ..\lib\notrealengine\lib\freetype\build-windows
	cmake --build ..\lib\notrealengine\lib\freetype\build-windows --config Release

)