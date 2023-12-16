#include <cstdlib>
#include <iostream>
#include "include/utils.h"
#include <stdint.h>
#include <bits/stdc++.h>

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

std::tm initialize_date(const std::string &date) {
    std::tm data_eleicao = {};
    std::istringstream iss(date);
    char delimiter;
    iss >> data_eleicao.tm_mday >> delimiter >> data_eleicao.tm_mon >> delimiter >> data_eleicao.tm_year;
    data_eleicao.tm_mon -= 1;
    data_eleicao.tm_year -= 1900;

    return data_eleicao;
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

std::vector<Federacao> cria_federacoes(std::map<int, Partido> &partidos) {
    std::vector<Federacao> federacoes;

    for(const std::pair<int, Partido> x : partidos){
		Partido p = x.second;
        std::vector<Candidato> candidatos = p.get_candidato_vector();
        
		if(candidatos.empty()) continue;

		const Candidato &c = candidatos.front();
		
		if(c.get_numero_federacao() != -1){
			bool federacaoExiste = false;
			for(Federacao f : federacoes){
				if(f.get_numero() == c.get_numero_federacao()){
					f.add_partido(p);
					federacaoExiste = true;
					break;
				}
			}

			if(!federacaoExiste){
				Federacao f(c.get_numero_federacao());
				f.add_partido(p);
				federacoes.push_back(f);
			}
		}
    }

    return federacoes;
}

