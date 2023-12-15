#include <iostream>
#include "electionslib/include/candidatos_deserializer.h"
#include "electionslib/include/partido.h"
#include "electionslib/include/votos_deserializer.h"
#include "electionslib/include/candidato.h"

int main(int argc, char** argv) {
    if(argc < 5) {
        std::cout << "Not enough arguments. Usage: " << argv[0] << " <cargo> <candidatos.csv> <votacao.csv> <data_eleicao>" << std::endl;
        return 1;
    }

    Cargo cargo;
    if(std::string(argv[1]) == "--federal")
        cargo = Cargo::FEDERAL;
    else if(std::string(argv[1]) == "--estadual")
        cargo = Cargo::ESTADUAL;
    else {
        std::cout << "Invalid cargo. Usage: --federal or --estadual" << std::endl;
        return 1;
    }

    std::string candidatos_file_path = argv[2];
    std::string votacao_file_path = argv[3];

    std::map<int, Partido> partidos = processa_candidatos(cargo, candidatos_file_path);

    for(const std::pair<int, Partido> x : partidos) {
        const Partido &p = x.second;
        p.print_partido();
    }

    /* std::cout << "LENDO VOTOS" << std::endl; */
    processa_votos(partidos, cargo, votacao_file_path);

    for(const std::pair<int, Partido> x : partidos) {
        const Partido &p = x.second;
        p.print_partido();
    }

    return 0;
}
