#include "include/candidatos_deserializer.h"
#include "include/candidato.h"
#include "include/partido.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map
#include <string>


std::string _iso_8859_1_to_utf8(std::string &str){
	// adaptado de: https://stackoverflow.com/a/39884120 :-)
	std::string strOut;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it){
		uint8_t ch = *it;
		if (ch < 0x80){
			// já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
			strOut.push_back(ch);
		}
		else{
			// está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
			// o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
			strOut.push_back(0b11000000 | (ch >> 6));
			// o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
			strOut.push_back(0b10000000 | (ch & 0b00111111));
		}
	}

	return strOut;
}

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
            	line = _iso_8859_1_to_utf8(line);
                std::istringstream line_stream(line);
                int i = 0;
                std::string token;
                std::cout << "\n\n\n\n";
                while(std::getline(line_stream, token, ';')) {
                    //token.replace("\"", "");
                	token = token.substr(1, token.size() - 2);
                	std::cout << token << std::endl;
                    switch(i++) {
                        case 13:
                            /* codigo_cargo = std::stoi(token); */
                            if(std::stoi(token) == 6) {
                                cargo_candidato = Cargo::FEDERAL;
                                break;
                            }
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
                            data_nascimento = token; //token.replace(",", "/");
                            break;
                        case 45:
                            /* genero = std::stoi(token); */
                            if(std::stoi(token) == 2) {
                                genero = Candidato::Genero::FEMININO;
                                break;
                            }
                            genero = Candidato::Genero::MASCULINO;
                            break;
                        case 56:
                            /* codigo_situacao_turno = std::stoi(token); */
                            if(std::stoi(token) == 2 || std::stoi(token) == 3) {
                                situacao_turno = Candidato::SituacaoTurno::ELEITO;
                                break;
                            }
                            situacao_turno = Candidato::SituacaoTurno::NAO_ELEITO;
                            break;
                        case 67:
                            /* nome_tipo_dest_voto = token; */
                            if(token == "Válido (legenda)") {
                                tipo_destino_voto = Candidato::TipoDestinoVoto::LEGENDA;
                                break;
                            }
                            if(token == "Válido") {
                                tipo_destino_voto = Candidato::TipoDestinoVoto::NOMINAL;
                                break;
                            }
                            tipo_destino_voto = Candidato::TipoDestinoVoto::NULO;
                            break;
                        case 68:
                            /* codigo_situacao_candidato = std::stoi(token); */
                            if(std::stoi(token) == 2 || std::stoi(token) == 16) {
                                situacao_candidato = Candidato::SituacaoCandidato::DEFERIDO;
                                break;
                            }
                            situacao_candidato = Candidato::SituacaoCandidato::INDEFERIDO;
                            break;
                        default:
                            break;
                    }
                }

                /* std::string nome, nome_urna, data_nascimento, sigla; */
                /* int numero, numero_partido, numero_federacao; */
                /* Candidato::Genero genero; */
                /* Candidato::SituacaoCandidato situacao_candidato; */
                /* Candidato::SituacaoTurno situacao_turno; */
                /* Candidato::TipoDestinoVoto tipo_destino_voto; */
                /* Cargo cargo_candidato; */

                std::cout << nome << nome_urna << sigla << numero << numero_partido << numero_federacao << (int)cargo_candidato;

                /* if(!partidos.count(numero_partido)) */
                /*     partidos.emplace(numero_partido, Partido(sigla, numero_partido)); */
                
                std::tm data;
                std::istringstream iss(data_nascimento);
                iss >> data.tm_mday >> data.tm_mon >> data.tm_year;

                std::cout << "\nDia: " << data.tm_mday << " ,Mês: " << data.tm_mon + 1 << " ,Ano: " << data.tm_year + 1900 << std::endl;


                if(cargo_candidato == cargo && (tipo_destino_voto == Candidato::TipoDestinoVoto::NOMINAL || tipo_destino_voto == Candidato::TipoDestinoVoto::LEGENDA)) {
                    Candidato c(nome, nome_urna, situacao_candidato, numero, numero_partido, numero_federacao, situacao_turno, genero, tipo_destino_voto);
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

