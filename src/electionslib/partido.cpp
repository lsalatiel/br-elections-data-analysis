#include "include/partido.h"

Partido::Partido(std::string sigla, int numero) :
            sigla(sigla),
            numero(numero) {votos_nominais = 0; votos_legenda = 0;}

int Partido::get_numero() const {
    return numero;
}

std::string Partido::get_sigla() const {
    return sigla;
}

void Partido::add_candidato(Candidato &c) {
    /* candidatos[c.get_numero_candidato()] = c; */    
    candidatos.insert(std::pair<int, Candidato>(c.get_numero_candidato(), c));
}

Candidato &Partido::get_candidato(int numero_candidato) {
    /* if(candidatos.find(numero_candidato) == candidatos.end()) */
    /*     throw std::invalid_argument("Candidato não encontrado"); */
    return candidatos[numero_candidato];
}

const std::vector<Candidato> Partido::get_candidato_vector() const {
    std::vector<Candidato> candidatos_vector;
    candidatos_vector.reserve(candidatos.size());
    for(const auto &[key, value] : candidatos) {
        candidatos_vector.push_back(value);
    }
    return candidatos_vector;
}

int Partido::get_votos_legenda() const {
    return votos_legenda;
}

int Partido::get_votos_nominais() const {
    return votos_nominais;
}

int Partido::get_votos_totais() const {
    return votos_legenda + votos_nominais;
}

void Partido::add_votos_legenda(int qtd_votos) {
    votos_legenda += qtd_votos;
}

void Partido::add_votos_nominais(int qtd_votos) {
    votos_nominais += qtd_votos;
}

const Candidato &Partido::get_candidato_mais_votado() const {

}

const Candidato &Partido::get_candidato_menos_votado() const {

}

void Partido::print_partido() {
    std::cout << sigla << "\n" << numero << std::endl;
    
    for(const std::pair<int, std::string> x : map){
        // std::cout << x.first << std::endl;
        Candidato c = x.second;
        c.print_candidato;
        std::cout << x.second << std::endl;
    } //ta aqui oq vc quer
    // 1.84.2


}
