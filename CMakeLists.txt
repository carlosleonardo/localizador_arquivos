cmake_minimum_required(VERSION 4.3)
project(localizador_arquivos)

set(CMAKE_CXX_STANDARD 20)

add_executable(localizador_arquivos main.cpp
        Localizador.cpp
        Localizador.h)
find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(localizador_arquivos PRIVATE Boost::program_options)