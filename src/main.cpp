#include <iostream>
#include "electionslib/include/candidatos_deserializer.h"
#include "electionslib/include/partido.h"
#include "electionslib/include/votos_deserializer.h"
#include "electionslib/include/candidato.h"
#include "electionslib/include/utils.h"

int main(int argc, char** argv) {
    check_arguments(argc, argv, 5, "<cargo> <candidatos.csv> <votacao.csv> <data_eleicao>");

    Cargo cargo = update_cargo(argv[1], "--federal", "--estadual", "Invalid cargo. Usage: --federal or --estadual");

    const std::string &candidatos_file_path = argv[2];
    const std::string &votacao_file_path = argv[3];

    std::map<int, Partido> partidos = processa_candidatos(cargo, candidatos_file_path);
    processa_votos(partidos, cargo, votacao_file_path);

    return 0;
}
