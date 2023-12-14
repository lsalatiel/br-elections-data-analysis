#include "include/votos_deserializer.h"
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <map>     // map

std::string __iso_8859_1_to_utf8(std::string &str){
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

static void processa_votos(std::map<int, Partido> partidos, int cargo, std::string filePath){
    try{
        std::ifstream input(filePath);
        std::string line;
        getline(input, line);

        int codigo_cargo, numero_candidato, votos;

        while(getline(input, line)){
            try{
            	line = __iso_8859_1_to_utf8(line);
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
                    //TO DO
                }
                
            }catch(std::exception &e){
                e.what();
            }
        }
    }catch(std::exception &e){
        e.what();
    }
}
