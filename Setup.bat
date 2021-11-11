@echo off
SetLocal EnableDelayedExpansion

if not exist lib\notrealengine\.git (
	git submodule update --init lib/notrealengine
	)

	
if not exist lib\SDL\include\SDL.h (
	git submodule update --init lib/SDL
	)
	
if not exist SDL2d.dll goto MoveSDL	

:MoveSDL

if not exist lib\SDL\build-windows\Debug\SDL2d.dll goto BuildSDL
move lib\SDL\build-windows\Debug\SDL2d.dll .

:BuildSDL

md lib\SDL\build-windows
if not exist lib\SDL\build-windows\SDL2.sln (
	cmake -S lib\SDL\ -B lib\SDL\build-windows
	)
for /f "delims=" %%i in ('lib\vswhere.exe -version 16 -property installationPath -nologo') do (
	set msbuild-path="%%i\MSBuild\Current\Bin\MSBuild.exe"
	echo Launching !msbuild-path!...
	!msbuild-path! lib\SDL\build-windows\SDL2.sln
	)