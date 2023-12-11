#include "include/votos_deserializer.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map

static void processa_votos(std::map<std::string, Partido>, int cargo, std::string filePath){
    try{
        std::ifstream input(filePath);
        std::string line;
        getline(input, line);

        int codigo_cargo, numero_candidato, votos;

        while(getline(input, line)){
            try{
                std::istringstream lineStream(line);
                int i = 0;
                std::string token;

                while(getline(lineStream, token, ';')){
                    switch (i++){
                        case 17:
                            codigo_cargo = stoi(token);
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
                
                if(codigo_cargo == cargo){
                    //if mapa de partido ja tem o candidato, adiciona votos
                    //else adiciona voto
                }
                
            }catch(std::exception &e){
                e.what();
            }
        }
    }catch(std::exception &e){
        e.what();
    }
}