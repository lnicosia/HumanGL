@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\include\notrealengine\NotRealEngine.hpp (

	git submodule update --init ..\lib\notrealengine

)