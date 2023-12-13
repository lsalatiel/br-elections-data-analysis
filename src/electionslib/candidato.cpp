#include "include/candidato.h"

Candidato::Candidato(std::string nome, std::string nome_urna, Candidato::SituacaoCandidato codigo_situacao_candidato, int numero, int numero_partido, int numero_federacao,
        Candidato::SituacaoTurno codigo_situacao_turno, Candidato::Genero genero, Candidato::TipoDestinoVoto nome_tipo_dest_votos, int total_votos) :
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

int Candidato::get_numero_federacao() {
    return numero_federacao;
}

int Candidato::get_numero_candidato() {
    return numero;
}

int Candidato::get_quantidade_votos() {
    return total_votos;
}

Candidato::TipoDestinoVoto Candidato::get_nome_tipo_dest_votos() {
    return nome_tipo_dest_votos;
}

/* LocalDate getDataNascimento(); */

std::string Candidato::get_nome_na_urna() {
    return nome_urna;
}

std::string Candidato::get_nome() {
    return nome;
}

Candidato::Genero Candidato::get_genero() {
    return genero;
}

Candidato::SituacaoCandidato Candidato::get_codigo_situacao_candidato() {
    return codigo_situacao_candidato;
}

int Candidato::get_numero_partido() {
    return numero_partido;
}

bool Candidato::is_candidatura_deferida() {
    return codigo_situacao_candidato == Candidato::SituacaoCandidato::DEFERIDO;
}

bool Candidato::is_eleito() {
    return codigo_situacao_turno == Candidato::SituacaoTurno::ELEITO;
}

void Candidato::add_quantidade_votos(int quantidadeVotos) {
    total_votos += quantidadeVotos;
}

