#if !defined (_PARTIDO_H_)
#define _PARTIDO_H_

#include <iostream>
#include <map>
#include <vector>
#include "candidato.h"

class Partido {
    std::string sigla;
    int numero;
    int votos_nominais;
    int votos_legenda;
    std::map<int, Candidato> candidatos;

    public:
        Partido() {};
        Partido(const std::string &sigla, int numero);

        int get_numero() const;

        const std::string &get_sigla() const;

        Candidato &get_candidato(int numeroCandidato);

        void add_candidato(Candidato &c);

        const std::vector<Candidato> get_candidato_vector() const;

        int get_votos_legenda() const;

        int get_votos_nominais() const;

        int get_votos_totais() const;

        void add_votos_legenda(int votosLegenda);

        void add_votos_nominais(int qtdVotos);

        const Candidato &get_candidato_mais_votado() const;
};

#endif
