#include "include/candidatos_deserializer.h"
#include "include/candidato.h"
#include "include/partido.h"
#include "include/utils.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map
#include <string>

std::map<int, Partido> processa_candidatos(Cargo cargo, const std::string &file_path){
    std::map<int, Partido> partidos;
    try {
        std::ifstream input(file_path);
        std::string line;
        std::getline(input, line);

        std::string nome, nome_urna, data_nascimento, sigla;
        int numero, numero_partido, numero_federacao;
        Candidato::Genero genero;
        Candidato::SituacaoCandidato situacao_candidato;
        Candidato::SituacaoTurno situacao_turno;
        Candidato::TipoDestinoVoto tipo_destino_voto;
        Cargo cargo_candidato;

        while(std::getline(input, line)) {
            try {
            	line = iso_8859_1_to_utf8(line);
                std::istringstream line_stream(line);
                int i = 0;
                std::string token;
                while(std::getline(line_stream, token, ';')) {
                	token = token.substr(1, token.size() - 2);
                    switch(i++) {
                        case 13:
                            if(std::stoi(token) == 6)
                                cargo_candidato = Cargo::FEDERAL;
                            else
                                cargo_candidato = Cargo::ESTADUAL;
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
                            data_nascimento = token;
                            break;
                        case 45:
                            if(std::stoi(token) == 2) 
                                genero = Candidato::Genero::MASCULINO;
                            else
                                genero = Candidato::Genero::FEMININO;
                            break;
                        case 56:
                            if(std::stoi(token) == 2 || std::stoi(token) == 3)
                                situacao_turno = Candidato::SituacaoTurno::ELEITO;
                            else
                                situacao_turno = Candidato::SituacaoTurno::NAO_ELEITO;
                            break;
                        case 67:
                            if(token == "Válido (legenda)") 
                                tipo_destino_voto = Candidato::TipoDestinoVoto::LEGENDA;              
                            else if(token == "Válido") 
                                tipo_destino_voto = Candidato::TipoDestinoVoto::NOMINAL;
                            else
                                tipo_destino_voto = Candidato::TipoDestinoVoto::NULO;
                            break;
                        case 68:
                            if(std::stoi(token) == 2 || std::stoi(token) == 16)
                                situacao_candidato = Candidato::SituacaoCandidato::DEFERIDO;
                            else
                                situacao_candidato = Candidato::SituacaoCandidato::INDEFERIDO;
                            break;
                        default:
                            break;
                    }
                }

                if(partidos.find(numero_partido) == partidos.end())
                    partidos.insert(std::pair<int, Partido>(numero_partido, Partido(sigla, numero_partido)));
                
                std::tm data = {};
                std::istringstream iss(data_nascimento);
                char delimiter;
                iss >> data.tm_mday >> delimiter >> data.tm_mon >> delimiter >> data.tm_year;
                data.tm_mon -= 1;
                data.tm_year -= 1900;

                if(cargo_candidato == cargo && (tipo_destino_voto == Candidato::TipoDestinoVoto::NOMINAL || tipo_destino_voto == Candidato::TipoDestinoVoto::LEGENDA)) {
                    Candidato c(nome, nome_urna, situacao_candidato, numero, numero_partido, numero_federacao, situacao_turno, genero, data, tipo_destino_voto);
                    partidos.at(numero_partido).add_candidato(c);
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

