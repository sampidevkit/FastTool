@echo off

copy dist\default\production\PWM.X.production.unified.hex Production.hex
del /f /s /q ".\dist"
del /f /s /q ".\build"
del /f /s /q ".\debug"

echo Done.