all:
	g++ main.cpp -o prompt.exe -Iinclude -Llib -Wfatal-errors

run:
	-taskkill /F /IM prompt.exe /T 2>nul
	@$(MAKE) -s all
	@cmd /c start prompt.exe
