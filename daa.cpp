#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>


// 1. Declarar a funcao que processa as mensagens do sistema (cliques, fechar, etc)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main() {
    // --- DECLARAÇÕES (Estilo Lucas) ---
    const char CLASS_NAME[] = "Janela";
    std::string titulo;
    WNDCLASS wc = { }; // Estrutura da classe da janela
    HWND hwnd;         // "Handle" ou identificador da janela
    MSG msg = { };     // Estrutura para capturar mensagens do sistema

    titulo = "Janela";

    // --- AÇÃO: Configurar a Classe ---
    wc.lpfnWndProc   = WindowProc; // Aponta para a nossa funcao de processamento
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Garante que o mouse apareça

    RegisterClass(&wc);

    // --- AÇÃO: Criar a Janela ---
    // WS_OVERLAPPEDWINDOW é o que garante os botões de Fechar, Minimizar e Ampliar
    hwnd = CreateWindowEx(
        0,                              
        CLASS_NAME,                     
        titulo.c_str(),                 
        WS_OVERLAPPEDWINDOW,            
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, // Posicao e tamanho (800x600)
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);

    // --- O LOOP "MUDO" ---
    // Essencial para a janela nao travar ou sumir instantaneamente
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// 2. Definir a funcao de processamento (Mesmo que nao queira capturar nada)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0); // Fecha o programa ao clicar no X
            return 0;
    }
    // Deixa o Windows cuidar de todo o resto (minimizar, ampliar, etc)
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}