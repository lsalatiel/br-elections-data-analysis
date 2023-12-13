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
    std::map<int, Candidato &> candidatos;

    public:
        Partido();
        Partido(std::string sigla, int numero);

        int get_numero();

        std::string get_sigla();

        Candidato &get_candidato(int numeroCandidato);

        void add_candidato(Candidato &c);

        std::vector<Candidato> get_candidato_vector();

        int get_votos_legenda();

        int get_votos_nominais();

        int get_votos_totais();

        void add_votos_legenda(int votosLegenda);

        void add_votos_nominais(int qtdVotos);

        Candidato &get_candidato_mais_votado();

        Candidato &get_candidato_menos_votado();
};

#endif
