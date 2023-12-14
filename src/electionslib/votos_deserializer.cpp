#include "include/votos_deserializer.h"
#include "include/candidato.h"
#include "include/candidatos_deserializer.h"
#include "include/partido.h"
#include "include/utils.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map

static void processa_votos(std::map<int, Partido> partidos, Cargo cargo, std::string filePath){
    /* try{ */
        std::ifstream input(filePath);
        std::string line;
        getline(input, line);

        int codigo_cargo, numero_candidato, votos;
        Cargo cargo_candidato;

        while(std::getline(input, line)){
            /* try{ */
            	line = iso_8859_1_to_utf8(line);
                std::istringstream lineStream(line);
                int i = 0;
                std::string token;

                while(std::getline(lineStream, token, ';')){
                    //token = token.substr(1, token.size() - 2); //ATIVAR CASO ESTEJAM OS VALORES ENTRE ASPAS
                    switch (i++){
                        case 17:
                            if(std::stoi(token) == 6) {
                                cargo_candidato = Cargo::FEDERAL;
                                break;
                            }
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
                
                std::string numero_partido = std::to_string(numero_candidato).substr(0, 2);
                if(cargo_candidato == cargo){
                    /* if(partidos.find(numero_partido) == partidos.end()) */
                       // partidos[numeroCandidato].addVotosLegenda(votos); //usar substring para pegar apenas os dois primeiros numeros do candidato ?  else{
                        // std::string numeroPartido = numeroCandidato; //aqui tem que fazer substring, porem e int
                    //}da pra literalmente fazer uma funcao em candidato getNumeroPartido e retornar os dois primeuiros numero
                        //se for deptuado estadual, divide por 1000. federal divide por 100
                }
                // olha isso aqui :
                // int valor = 45642;

                // Converte o valor inteiro em uma string.
                /* std::string numero_partido = std::to_string(valor).substr(0, 2); */

                // Extrai os dois primeiros dígitos da string.
                // std::string doisPrimeirosNumeros = stringValor.substr(0, 2);
            /* }catch(std::exception &e){ */
            /*     e.what(); */
            /* } */
        /* } */
/*     }catch(std::exception &e){ */
/*         e.what(); */
/*     } */
    }
}
