@echo off
SetLocal EnableDelayedExpansion

if not exist .\x64\UsingExternalLibs-Release\freetype.dll (

	if not exist ..\lib\notrealengine\lib\freetype\build-windows\Release\freetype.dll (

		echo Buildling freetype in Release...

		if not exist ..\lib\notrealengine\lib\freetype\include\freetype.h (
			git submodule update --init --recursive --progress ..\lib\notrealengine\
		)
		if not exist ..\lib\notrealengine\lib\freetype\build-windows (
			md ..\lib\notrealengine\lib\freetype\build-windows
		)
		cmake -S ..\lib\notrealengine\lib\freetype\ -D BUILD_SHARED_LIBS=ON -G "Visual Studio 16 2019" -T "v142" -B ..\lib\notrealengine\lib\freetype\build-windows
		cmake --build ..\lib\notrealengine\lib\freetype\build-windows --config Release

	)

	move ..\lib\notrealengine\lib\freetype\build-windows\Release\freetype.dll .\x64\UsingExternalLibs-Release

)