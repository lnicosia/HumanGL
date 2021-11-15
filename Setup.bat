@echo off
SetLocal EnableDelayedExpansion

if not exist SDL2d.dll (

	if not exist lib\SDL\build-windows\Debug\SDL2d.dll (

		if not exist lib\SDL\build-windows\SDL2.sln (

			if not exist lib\SDL\include\SDL.h (
				git submodule update --init lib/SDL
			)
			if not exist lib\SDL\build-windows (
				md lib\SDL\build-windows
			)
			cmake -S lib\SDL\ -B lib\SDL\build-windows
			
		)
		for /f "delims=" %%i in ('lib\vswhere.exe -version 16 -property installationPath -nologo') do (
			set msbuild-path="%%i\MSBuild\Current\Bin\MSBuild.exe"
			echo Launching !msbuild-path!...
			!msbuild-path! lib\SDL\build-windows\SDL2.sln
		)
	)
	move lib\SDL\build-windows\Debug\SDL2d.dll windows\
)

if not exist NotRealEngine.dll (

	if not exist lib\notrealengine\windows\x64\Debug\NotRealEngine.dll (
	
		if not exist lib\notrealengine\.git (
			git submodule update --init lib/notrealengine
			
		)
		echo Launching !msbuild-path!
		!msbuild-path! "lib\notrealengine\windows\Not Real Engine.sln"
	)
	move lib\notrealengine\windows\x64\Debug\NotRealEngine.dll windows\
)
