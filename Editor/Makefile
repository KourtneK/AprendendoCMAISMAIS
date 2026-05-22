all:
	g++ main.cpp -o editor.exe -Iinclude -Llib -Wfatal-errors

run:
	-taskkill /F /IM editor.exe /T 2>nul
	@$(MAKE) -s all
	@cmd /c start editor.exe
