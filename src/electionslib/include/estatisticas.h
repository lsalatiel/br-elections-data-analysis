#if !defined(_ESTATISTICAS_H_)
#define _ESTATISTICAS_H_

#include <iostream>
#include <map>
#include "partido.h"
#include "candidato.h"
#include "federacao.h"

std::vector<Candidato> get_candidatos_eleitos_ordenados(std::map<int, Partido> &partidos);

#endif
