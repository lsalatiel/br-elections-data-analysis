#if !defined(_ESTATISTICAS_H_)
#define _ESTATISTICAS_H_

#include <iostream>
#include <map>
#include "partido.h"
#include "candidato.h"
#include "federacao.h"

std::vector<Candidato> get_candidatos_eleitos_ordenados(std::map<int, Partido> &partidos);

std::vector<Candidato> get_candidatos_mais_votados(std::map<int, Partido> &partidos);

void print_partidos_com_votos(std::map<int, Partido> &partidos);

void print_primeiro_ultimo_colocados(std::map<int, Partido> &partidos);

void print_eleitos_por_faixa_etaria(std::vector<Candidato> candidatos_eleitos, std::tm date);

void print_eleitos_por_genero(std::vector<Candidato> candidatos_eleitos);

void print_total_votos(std::map<int, Partido> &partidos);

#endif
