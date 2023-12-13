#if !defined (_CANDIDATE_H_)
#define _CANDIDATE_H_

#include <iostream>
#include <chrono>

class Candidato {
    public:
        enum class Genero { MASCULINO, FEMININO };
        enum class TipoDestinoVoto { NOMINAL, LEGENDA };
        enum class SituacaoCandidato { DEFERIDO, INDEFERIDO };
        enum class SituacaoTurno { ELEITO, NAO_ELEITO };

    private:
        std::string nome;
        std::string nome_urna;
        SituacaoCandidato codigo_situacao_candidato; // 2 ou 16 = candidato deferido
        int numero;
        int numero_partido;
        int numero_federacao;
        SituacaoTurno codigo_situacao_turno; // 2 ou 3 = eleito
        Genero genero;
        /* std::chrono::year_month_day data_nascimento; */
        TipoDestinoVoto nome_tipo_dest_votos; // nominal ou legenda
        int total_votos;

    public:
        Candidato();
        Candidato(std::string nome, std::string nome_urna, Candidato::SituacaoCandidato codigo_situacao_candidato, int numero, int numero_partido, int numero_federacao,
                Candidato::SituacaoTurno codigo_situacao_turno, Candidato::Genero genero, Candidato::TipoDestinoVoto nome_tipo_dest_votos, int total_votos);

        int get_numero_federacao();

        int get_numero_candidato();

        int get_quantidade_votos();

        Candidato::TipoDestinoVoto get_nome_tipo_dest_votos();

        bool is_candidatura_deferida();

        bool is_eleito();

        /* LocalDate getDataNascimento(); */

        std::string get_nome_na_urna();

        std::string get_nome();

        Candidato::Genero get_genero();

        Candidato::SituacaoCandidato get_codigo_situacao_candidato();

        void add_quantidade_votos(int quantidadeVotos);

        int get_numero_partido();
};

#endif
