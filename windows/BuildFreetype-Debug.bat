@echo off
SetLocal EnableDelayedExpansion

if not exist .\x64\UsingExternalLibs-Debug\freetyped.dll (

	if not exist ..\lib\notrealengine\lib\freetype\build-windows\Debug\freetyped.dll (

		echo Buildling freetype in Debug...

		if not exist ..\lib\notrealengine\lib\freetype\include\freetype.h (
			git submodule update --init --recursive --progress ..\lib\notrealengine\
		)
		if not exist ..\lib\notrealengine\lib\freetype\build-windows (
			md ..\lib\notrealengine\lib\freetype\build-windows
		)
		cmake -S ..\lib\notrealengine\lib\freetype\ -D BUILD_SHARED_LIBS=ON -G "Visual Studio 16 2019" -T "v142" -B ..\lib\notrealengine\lib\freetype\build-windows
		cmake --build ..\lib\notrealengine\lib\freetype\build-windows --config Debug
		
	)

	move ..\lib\notrealengine\lib\freetype\build-windows\Debug\freetyped.dll .\x64\UsingExternalLibs-Debug

)