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

void print_candidatos(const std::vector<Candidato>& candidatos, const std::vector<Federacao>& federacoes, const std::map<int, Partido>& partidos) {
	int i = 1;
	for(const Candidato &c : candidatos) {
		std::cout << i << " - ";
		for(const Federacao &f : federacoes) {
			if(f.get_numero() == c.get_numero_federacao()) {
				std::cout << "*";
				break;
			}
		}

		std::string numero_partido = std::to_string(c.get_numero_candidato()).substr(0, 2);
		auto it = partidos.find(std::stoi(numero_partido));
		const Partido &p = it->second;

		//std::cout << c.print_candidato();
		std::cout << "" << c.get_nome_na_urna();
		std::cout << " (" << p.get_sigla() << ", " << c.get_quantidade_votos() << " votos)" << std::endl;
		i++;
	}
}