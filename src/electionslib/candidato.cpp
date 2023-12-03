#include "include/candidato.h"

Candidato::Candidato(std::string nome, std::string nome_urna, int codigo_situacao_candidato, int numero, int numero_partido, int numero_federacao, int codigo_situacao_turno, bool genero, std::string nome_tipo_dest_votos, int total_votos) :
            nome(nome),
            nome_urna(nome_urna),
            codigo_situacao_candidato(codigo_situacao_candidato),
            numero(numero),
            numero_partido(numero_partido),
            numero_federacao(numero_federacao),
            codigo_situacao_turno(codigo_situacao_turno),
            genero(genero),
            nome_tipo_dest_votos(nome_tipo_dest_votos),
            total_votos(total_votos) {}


