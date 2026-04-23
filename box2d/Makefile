all:
	g++ main.cpp -o box.exe -Iinclude -Llib -lSDL3 -lbox2d -mwindows -Wfatal-errors

run:
	-taskkill /F /IM box.exe /T 2>nul
	@$(MAKE) -s all
	@cmd /c start box.exe