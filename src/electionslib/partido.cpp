#include "include/partido.h"

Partido::Partido(const std::string &sigla, int numero) :
            sigla(sigla),
            numero(numero) {votos_nominais = 0; votos_legenda = 0;}

/* Partido::Partido(std::string &sigla, int &numero) : */
/*             sigla(sigla), */
/*             numero(numero) {votos_nominais = 0; votos_legenda = 0;}   //CRIEI ESSA PARADA AGORA */

int Partido::get_numero() const {
    return numero;
}

const std::string &Partido::get_sigla() const {
    return sigla;
}

void Partido::add_candidato(Candidato &c) {
    /* candidatos[c.get_numero_candidato()] = c; */    
    candidatos.insert(std::pair<int, Candidato>(c.get_numero_candidato(), c));
}

Candidato &Partido::get_candidato(int numero_candidato) {
    if(candidatos.find(numero_candidato) == candidatos.end()) 
        throw std::invalid_argument("Candidato não encontrado"); 
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
    Candidato mais_votado = candidatos.begin()->second;
    int key = -1;

    for(const std::pair<int, Candidato> x : candidatos){
        Candidato c = x.second;
        if(c.get_quantidade_votos() > mais_votado.get_quantidade_votos()) {
            mais_votado = c;
            key = x.first;
        }
    }

    // foi o jeito que eu pensei de conseguir retornar uma referencia (ง︡'-'︠)ง

    return candidatos.at(key);
}

const Candidato &Partido::get_candidato_menos_votado() const {
    /* Candidato menos_votado; */
    // warning supression
    return candidatos.begin()->second;
    // TODO:
}

void Partido::print_partido() const {
    std::cout << sigla << "\n" << numero << std::endl;
    
    for(const std::pair<int, Candidato> x : candidatos){
        Candidato c = x.second;
        c.print_candidato();
        std::cout << std::endl;
    }
}

static bool comparador_votos(const Partido& p1, const Partido& p2){
        return p1.get_votos_totais() > p2.get_votos_totais();
}