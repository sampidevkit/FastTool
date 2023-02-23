@echo off

copy dist\default\production\USB_CDC_Debug.X.production.unified.hex Production.hex
del /f /s /q ".\dist"
del /f /s /q ".\build"
del /f /s /q ".\debug"

echo Done.