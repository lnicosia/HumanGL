@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\.git (
	git submodule update --init --recursive ..\lib\notrealengine
)

if not exist SDL2d.dll (

	if not exist ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.dll (

		if not exist ..\lib\notrealengine\lib\SDL\build-windows\SDL2.sln (

			if not exist ..\lib\notrealengine\lib\SDL\build-windows (
				md ..\lib\notrealengine\lib\SDL\build-windows
			)
			cmake -S ..\lib\notrealengine\lib\SDL\ -B ..\lib\notrealengine\lib\SDL\build-windows
			
		)
		for /f "delims=" %%i in ('..\lib\vswhere.exe -version 16 -property installationPath -nologo') do (
			set msbuild-path="%%i\MSBuild\Current\Bin\MSBuild.exe"
			echo Launching !msbuild-path!...
			!msbuild-path! ..\lib\notrealengine\lib\SDL\build-windows\SDL2.sln
		)
	)
	move ..\lib\notrealengine\lib\SDL\build-windows\Debug\SDL2d.dll .\
)

if not exist src (
	mklink /j src ..\src
)

if not exist inc (
	mklink /j inc ..\inc
)