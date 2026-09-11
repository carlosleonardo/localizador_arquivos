//
// Created by S861321135 on 09/09/2026.
//

#include "Localizador.h"

#include <iostream>
#include <filesystem>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace fs = std::filesystem;

int Localizador::executar(int argc, char **argv) {
    po::options_description desc("Opções disponíveis");
    desc.add_options()("dir,d", po::value<std::string>(), "Diretório a partir do qual localizar arquivos")
            ("ajuda,a", "Esta ajuda")("extensao,e", po::value<std::string>(), "Extensão de arquivo a localizar");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (const po::error &e) {
        std::cerr << "Erro ao processar argumentos: " << e.what() << std::endl;
        std::cout << desc << std::endl;
        return EXIT_FAILURE;
    }
    if (vm.count("ajuda") || !vm.count("dir") || !vm.count("extensao")) {
        std::cout << desc << std::endl;
        return 0;
    }

    m_diretorio = vm["dir"].as<std::string>();
    m_extensao = vm["extensao"].as<std::string>();
    if (!buscar()) {
        std::cerr << "Erro ao buscar arquivos." << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}

bool Localizador::buscar() {
    if (m_diretorio.empty() || m_extensao.empty()) {
        std::cerr << "Diretório ou extensão não especificados." << std::endl;
        return false;
    }
    if (!fs::is_directory(m_diretorio)) {
        std::cerr << m_diretorio << " não é um diretório válido." << std::endl;
        return false;
    }
    unsigned long totalArquivos = 0;
    std::cout << "Buscando arquivos com extensão " << m_extensao << " em " << m_diretorio << std::endl;
    m_extensao = (m_extensao[0] == '.') ? m_extensao : "." + m_extensao; // Garante que a extensão comece com '.'
    try {
        for (const auto &entry: fs::recursive_directory_iterator(m_diretorio,
                                                                 fs::directory_options::skip_permission_denied)) {
            if (entry.is_regular_file() && entry.path().extension() == m_extensao) {
                std::cout << entry.path().string() << std::endl;
                ++totalArquivos;
            }
        }
    } catch (fs::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    std::cout << "Total de arquivos encontrados: " << totalArquivos << std::endl;
    return true;
}
