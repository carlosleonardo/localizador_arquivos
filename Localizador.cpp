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
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

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
    std::cout << "Buscando arquivos com extensão " << m_extensao << " em " << m_diretorio << std::endl;
    try {
        for (const auto &entry: fs::recursive_directory_iterator(m_diretorio)) {
            if (entry.is_regular_file() && entry.path().extension() == m_extensao) {
                std::cout << entry.path().string() << std::endl;
            }
        }
    } catch (fs::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}
