@echo off

copy dist\default\production\QWIIC.X.production.unified.hex Production.hex
del /f /s /q ".\dist"
del /f /s /q ".\build"
del /f /s /q ".\debug"

echo Done.