#include <iostream>

#include "Localizador.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char **argv) {
#if defined(_WIN32)
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "Localizador de arquivos!" << std::endl;
    Localizador localizador;
    return localizador.executar(argc, argv);
}
