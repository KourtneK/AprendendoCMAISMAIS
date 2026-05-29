all:
	g++ main.cpp -o editor.exe -Iinclude -Llib -Wfatal-errors
	g++ lspServer.cpp -o lspServer.exe -Iinclude -Llib -Wfatal-errors

run-editor:
	-taskkill /F /IM editor.exe /T 2>nul
	@$(MAKE) -s all
	@cmd /c start editor.exe

run-server:
	-taskkill /F /IM lspServer.exe /T 2>nul
	@$(MAKE) -s all
	@cmd /c start lspServer.exe
