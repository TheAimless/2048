$SDL = "https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-2.24.0-win32-x64.zip"
$EXT_LIBS = ".\libs"
Invoke-WebRequest -Uri $SDL -OutFile (Join-Path $EXT_LIBS SDL.zip)