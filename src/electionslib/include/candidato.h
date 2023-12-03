#if !defined (_CANDIDATE_H_)
#define _CANDIDATE_H_

#include <iostream>

const bool MASCULINO = true;
const bool FEMININO = false;

class Candidato {
    std::string nome;
    std::string nome_urna;
    int codigo_situacao_candidato; // 2 ou 16 = candidato deferido
    int numero;
    int numero_partido;
    int numero_federacao;
    int codigo_situacao_turno; // 2 ou 3 = eleito
    bool genero;
    std::string nome_tipo_dest_votos; // nominal ou legenda
    int total_votos;

    public:
        Candidato();
        Candidato(std::string nome, std::string nome_urna, int codigo_situacao_candidato, int numero, int numero_partido, int numero_federacao, int codigo_situacao_turno, bool genero, std::string nome_tipo_dest_votos, int total_votos);
};

#endif
