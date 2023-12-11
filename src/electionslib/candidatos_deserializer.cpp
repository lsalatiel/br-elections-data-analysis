#include "include/candidatos_deserializer.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map

static std::map<std::string, Partido> processa_candidatos(int cargo, std::string &filePath){
    std::map<std::string, Partido> partidos;
    try{
        std::ifstream input(filePath);
        std::string line;
        getline(input, line);

        std::string nome, nome_urna, numero, data_nascimento, nome_tipo_dest_voto, total_votos, sigla;
        int codigo_situacao_candidato, numero, numero_partido, codigo_cargo, numero_federacao, codigo_situacao_turno;
        bool genero;

        while(getline(input, line)){
            try{
                std::istringstream lineStream(line);
                int i = 0;
                std::string token;

                while(getline(lineStream, token, ';')){
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

                //if mapa partidos nao possui a chave numero_partido, cria-se partido
               //if codigocargo é igual a cargo e nome tipodesvoto é valido ou valido legenda, cria candidato



            }catch(std::exception &e){
                e.what();
            }
        }
    }catch(std::exception &e){
        e.what();
    }

    return partidos;
}
