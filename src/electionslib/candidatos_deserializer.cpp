#include "include/candidatos_deserializer.h"
#include "include/candidato.h"
#include "include/partido.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map
#include <string>

std::map<int, Partido> &processa_candidatos(int cargo, std::string &filePath){
    std::map<int, Partido> partidos;
    try {
        std::ifstream input(filePath);
        std::string line;
        getline(input, line);

        std::string nome, nome_urna, numero, data_nascimento, nome_tipo_dest_voto, sigla;
        int codigo_situacao_candidato, numero, numero_partido, codigo_cargo, numero_federacao, codigo_situacao_turno;
        bool genero;

        while(getline(input, line)){
            try {
                std::istringstream lineStream(line);
                int i = 0;
                std::string token;

                while(getline(lineStream, token, ';')) {
                    switch(i++){
                        case 13:
                            codigo_cargo = std::stoi(token);
                            break;
                        case 16:
                            numero = std::stoi(token);
                            break;
                        case 17:
                            nome = token;
                            break;
                        case 18:
                            nome_urna = token;
                            break;
                        case 27:
                            numero_partido = std::stoi(token);
                            break;
                        case 28:
                            sigla = token;
                            break;
                        case 30:
                            numero_federacao = std::stoi(token);
                            break;
                        case 42:
                            data_nascimento = token.replace(",", "/");
                            break;
                        case 45:
                            genero = std::stoi(token);
                            break;
                        case 56:
                            codigo_situacao_turno = std::stoi(token);
                            break;
                        case 67:
                            nome_tipo_dest_voto = token;
                            break;
                        case 68:
                            codigo_situacao_candidato = std::stoi(token);
                            break;
                        default:
                            break;
                    }
                }

                if(!partidos.count(numero_partido))
                    partidos.emplace(numero_partido, Partido(sigla, numero_partido));
                
                //TO DO: processar a data

                if(codigo_cargo == cargo && (nome_tipo_dest_voto == "Válido" || nome_tipo_dest_voto == "Válido (legenda)")) {
                    Candidato c(nome, nome_urna, codigo_situacao_candidato, numero, numero_partido, numero_federacao, codigo_situacao_turno, genero, nome_tipo_dest_voto, 0);
                    //partidos.at(numero_partido).add_candidato(c);
                }

            } catch(std::exception &e){
                e.what();
            }
        }
    } catch(std::exception &e){
        e.what();
    }

    return partidos;
}
