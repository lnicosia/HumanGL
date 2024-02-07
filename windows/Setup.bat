@echo off
SetLocal EnableDelayedExpansion

if not exist ..\lib\notrealengine\.git (
	git submodule update --init --recursive ..\lib\notrealengine
)

if not exist src (
	mklink /j src ..\src
)

if not exist inc (
	mklink /j inc ..\inc
)