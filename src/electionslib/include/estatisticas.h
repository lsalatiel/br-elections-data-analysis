#if !defined(_ESTATISTICAS_H_)
#define _ESTATISTICAS_H_

#include <iostream>
#include <map>
#include "partido.h"
#include "candidato.h"
#include "federacao.h"

std::vector<Candidato> get_candidatos_eleitos_ordenados(std::map<int, Partido> &partidos);

void print_candidatos_eleitos_ordenados(std::vector<Candidato> &candidatos_ordenados, std::map<int, Partido> &partidos, Cargo cargo, const std::vector<Federacao>& federacoes);

std::vector<Candidato> get_candidatos_mais_votados(std::map<int, Partido> &partidos);

void print_candidatos_mais_votados(std::vector<Candidato> &candidatos_mais_votados_em_vagas, std::vector<Candidato> &candidatos_eleitos, std::map<int, Partido> &partidos, const std::vector<Federacao> &federacoes);

void print_partidos_com_votos(std::map<int, Partido> &partidos);

void print_primeiro_ultimo_colocados(std::map<int, Partido> &partidos);

void print_eleitos_por_faixa_etaria(std::vector<Candidato> candidatos_eleitos, std::tm date);

void print_eleitos_por_genero(std::vector<Candidato> candidatos_eleitos);

void print_total_votos(std::map<int, Partido> &partidos);

void print_candidatos(const std::vector<Candidato>& candidatos, const std::vector<Federacao>& federacoes, const std::map<int, Partido>& partidos);

std::vector<Partido> ordena_partidos_por_total_votos(const std::map<int, Partido>& partidos);

std::vector<Partido> ordena_partidos_por_mais_votado(const std::map<int, Partido>& partidos);

void print_candidatos_eleitos_majoritaria(std::vector<Candidato> &candidatos_mais_votados, std::vector<Candidato> &candidatos_mais_votados_em_vagas, std::vector<Candidato> &candidatos_eleitos,
        std::map<int, Partido> &partidos, std::vector<Federacao> &federacoes);

void print_candidatos_eleitos_proporcional(std::vector<Candidato> &candidatos_mais_votados, std::vector<Candidato> &candidatos_mais_votados_em_vagas, std::vector<Candidato> &candidatos_eleitos,
        std::map<int, Partido> &partidos, std::vector<Federacao> &federacoes);

#endif
