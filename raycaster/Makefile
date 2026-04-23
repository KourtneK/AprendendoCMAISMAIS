all:
	g++ poly.cpp -o poly.exe -Iinclude -Llib -lSDL3 -lbox2d -mwindows -Wfatal-errors

run:
	-taskkill /F /IM poly.exe /T 2>nul
	@$(MAKE) -s all
	@cmd /c start poly.exe