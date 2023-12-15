#include <cstdlib>
#include <iostream>
#include "include/utils.h"
#include <stdint.h>

std::string iso_8859_1_to_utf8(std::string &str){
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

void check_arguments(int argc, char **argv, int expected_argc, const std::string &usage) {
    if(argc < expected_argc) {
        std::cout << "Not enough arguments. Usage: " << argv[0] << " " << usage << std::endl;
        exit(1);
    }
}

Cargo update_cargo(const std::string &cmp, const std::string &federal, const std::string &estadual, const std::string &error_msg) {
    Cargo cargo;
    if(cmp == federal)
        cargo = Cargo::FEDERAL;
    else if(cmp == estadual)
        cargo = Cargo::ESTADUAL;
    else {
        std::cout << error_msg << std::endl;
        exit(1);
    }

    return cargo;
}