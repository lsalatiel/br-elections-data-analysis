#include "include/partido.h"

Partido::Partido(std::string sigla, int numero) :
            sigla(sigla),
            numero(numero) {}

int Partido::get_numero() {
    return numero;
}

std::string Partido::get_sigla() {
    return sigla;
}

void Partido::add_candidato(Candidato &c) {
    candidatos[c.get_numero_candidato()] = c;
}

Candidato &Partido::get_candidato(int numero_candidato) {
    /* if(candidatos.find(numero_candidato) == candidatos.end()) */
    /*     throw std::invalid_argument("Candidato não encontrado"); */
    return candidatos[numero_candidato];
}

std::vector<Candidato> Partido::get_candidato_vector() {
    std::vector<Candidato> candidatos_vector;
    candidatos_vector.reserve(candidatos.size());
    for(const auto &[key, value] : candidatos) {
        candidatos_vector.push_back(value);
    }
    return candidatos_vector;
}

int Partido::get_votos_legenda() {
    return votos_legenda;
}

int Partido::get_votos_nominais() {
    return votos_nominais;
}

int Partido::get_votos_totais() {
    return votos_legenda + votos_nominais;
}

void Partido::add_votos_legenda(int qtd_votos) {
    votos_legenda += qtd_votos;
}

void Partido::add_votos_nominais(int qtd_votos) {
    votos_nominais += qtd_votos;
}

Candidato &Partido::get_candidato_mais_votado() {

}

Candidato &Partido::get_candidato_menos_votado() {

}
