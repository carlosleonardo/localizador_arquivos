//
// Created by S861321135 on 09/09/2026.
//

#ifndef LOCALIZADOR_ARQUIVOS_LOCALIZADOR_H
#define LOCALIZADOR_ARQUIVOS_LOCALIZADOR_H
#include <string>

class Localizador {
public:
    Localizador() = default;

    int executar(int argc, char **argv);

    bool buscar();

private:
    std::string m_diretorio;
    std::string m_extensao;
};


#endif //LOCALIZADOR_ARQUIVOS_LOCALIZADOR_H
