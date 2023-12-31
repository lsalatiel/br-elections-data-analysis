#include "include/candidato.h"

Candidato::Candidato(const std::string &nome, const std::string &nome_urna, Candidato::SituacaoCandidato codigo_situacao_candidato, int numero, int numero_partido, int numero_federacao,
        Candidato::SituacaoTurno codigo_situacao_turno, Candidato::Genero genero, std::tm &data_nascimento, Candidato::TipoDestinoVoto nome_tipo_dest_votos) :
            nome(nome),
            nome_urna(nome_urna),
            codigo_situacao_candidato(codigo_situacao_candidato),
            numero(numero),
            numero_partido(numero_partido),
            numero_federacao(numero_federacao),
            codigo_situacao_turno(codigo_situacao_turno),
            genero(genero),
			data_nascimento(data_nascimento),
            nome_tipo_dest_votos(nome_tipo_dest_votos) {total_votos = 0;}

int Candidato::get_numero_federacao() const {
    return numero_federacao;
}

int Candidato::get_numero_candidato() const {
    return numero;
}

int Candidato::get_quantidade_votos() const {
    return total_votos;
}

Candidato::TipoDestinoVoto Candidato::get_nome_tipo_dest_votos() const {
    return nome_tipo_dest_votos;
}

const std::tm &Candidato::get_data_nascimento() const{
	return data_nascimento;
}

const std::string &Candidato::get_nome_na_urna() const {
    return nome_urna;
}

const std::string &Candidato::get_nome() const {
    return nome;
}

Candidato::Genero Candidato::get_genero() const {
    return genero;
}

Candidato::SituacaoCandidato Candidato::get_codigo_situacao_candidato() const {
    return codigo_situacao_candidato;
}

int Candidato::get_numero_partido() const {
    return numero_partido;
}

bool Candidato::is_candidatura_deferida() const {
    return codigo_situacao_candidato == Candidato::SituacaoCandidato::DEFERIDO;
}

bool Candidato::is_eleito() const {
    return codigo_situacao_turno == Candidato::SituacaoTurno::ELEITO;
}

void Candidato::add_quantidade_votos(int quantidadeVotos) {
    total_votos += quantidadeVotos;
}

