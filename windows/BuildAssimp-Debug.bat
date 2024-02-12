@echo off
SetLocal EnableDelayedExpansion

if not exist .\x64\UsingExternalLibs-Debug\assimp-vc142-mtd.dll (

	if not exist ..\lib\notrealengine\lib\assimp\build-windows\bin\Debug\assimp-vc142-mtd.dll (

		echo Buildling assimp in Debug...

		if not exist ..\lib\notrealengine\lib\assimp\include\assimp.h (
			git submodule update --init --recursive --progress ..\lib\notrealengine\
		)
		if not exist ..\lib\notrealengine\lib\assimp\build-windows (
			md ..\lib\notrealengine\lib\assimp\build-windows
		)
		cmake -S ..\lib\notrealengine\lib\assimp\ -G "Visual Studio 16 2019" -T "v142" -D ASSIMP_BUILD_ZLIB=ON -B ..\lib\notrealengine\lib\assimp\build-windows
		cmake --build ..\lib\notrealengine\lib\assimp\build-windows --config Debug
		
	)

	move ..\lib\notrealengine\lib\assimp\build-windows\bin\Debug\assimp-vc142-mtd.dll .\x64\UsingExternalLibs-Debug

)