#if !defined(_UTILS_H_)
#define _UTILS_H_

#include <iostream>
#include "federacao.h"
#include <unordered_set>

std::string iso_8859_1_to_utf8(std::string &str);

void check_arguments(int argc, char **argv, int expected_argc, const std::string &usage);

Cargo update_cargo(const std::string &cmp, const std::string &federal, const std::string &estadual, const std::string &error_msg);

std::vector<Federacao> cria_federacoes(std::map<int, Partido> &partidos);

void print_candidatos(const std::vector<Candidato>& candidatos, const std::vector<Federacao>& federacoes, const std::map<int, Partido>& partidos);

std::vector<std::pair<int, Partido>> ordena_partidos_por_total_votos(const std::map<int, Partido>& partidos);

std::vector<std::pair<int, Partido>> ordena_partidos_por_mais_votado(const std::map<int, Partido>& partidos);

#endif
