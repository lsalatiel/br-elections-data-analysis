#include "include/votos_deserializer.h"
#include "include/candidato.h"
#include "include/partido.h"
#include "include/utils.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map

void processa_votos(std::map<int, Partido> &partidos, Cargo cargo, std::string filePath) {
    try {
        std::ifstream input(filePath);
        std::string line;
        getline(input, line);

        int  numero_candidato, votos;
        Cargo cargo_candidato;

        while(std::getline(input, line)) {
            try {
            	line = iso_8859_1_to_utf8(line);
                std::istringstream lineStream(line);
                int i = 0;
                std::string token;

                while(std::getline(lineStream, token, ';')){
                    token = token.substr(1, token.size() - 2);
                    switch (i++){
                        case 17:
                            if(std::stoi(token) == 6)
                                cargo_candidato = Cargo::FEDERAL;
                            else
                                cargo_candidato = Cargo::ESTADUAL;
                            break;
                        case 19:
                            numero_candidato = std::stoi(token);
                            break;
                        case 21:
                            votos = std::stoi(token);
                            break;
                        default:
                            break;
                    }
                }

                if(numero_candidato == 95 || numero_candidato == 96 || numero_candidato == 97 || numero_candidato == 98)
                    continue;

                if(cargo_candidato == cargo) {
                    if(partidos.find(numero_candidato) != partidos.end()) {
                        Partido &p = partidos[numero_candidato];
                        p.add_votos_legenda(votos);
                    }
                    else {
                        std::string numero_partido = std::to_string(numero_candidato).substr(0, 2);
                        if(partidos.find(std::stoi(numero_partido)) != partidos.end()) {
                            Partido &p = partidos[std::stoi(numero_partido)];
                            Candidato &c = p.get_candidato(numero_candidato);
                            if(c.is_candidatura_deferida()) {
                                c.add_quantidade_votos(votos);
                                p.add_votos_nominais(votos);
                            }
                            else if(c.get_nome_tipo_dest_votos() == Candidato::TipoDestinoVoto::LEGENDA)
                                p.add_votos_legenda(votos);
                        }
                    }
                }

            } catch(std::exception &e) {
                e.what();
            }
        } 
    } catch(std::exception &e) {
        e.what();
    }
}
