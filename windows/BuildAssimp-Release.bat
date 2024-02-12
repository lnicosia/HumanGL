@echo off
SetLocal EnableDelayedExpansion

if not exist .\x64\UsingExternalLibs-Release\assimp-vc142-mt.dll (

	echo No dll
	if not exist ..\lib\notrealengine\lib\assimp\build-windows\lib\Release\assimp-vc142-mt.dll (

		echo Buildling assimp in Release...

		if not exist ..\lib\notrealengine\lib\assimp\include\assimp.h (
			git submodule update --init --recursive --progress ..\lib\notrealengine\
		)
		if not exist ..\lib\notrealengine\lib\assimp\build-windows (
			md ..\lib\notrealengine\lib\assimp\build-windows
		)
		cmake -S ..\lib\notrealengine\lib\assimp\ -G "Visual Studio 16 2019" -T "v142" -D ASSIMP_BUILD_ZLIB=ON -B ..\lib\notrealengine\lib\assimp\build-windows
		cmake --build ..\lib\notrealengine\lib\assimp\build-windows --config Release

	)

	move ..\lib\notrealengine\lib\assimp\build-windows\bin\Release\assimp-vc142-mt.dll .\x64\UsingExternalLibs-Release

)