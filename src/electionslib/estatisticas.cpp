#include "include/estatisticas.h"
#include <bits/stdc++.h>

std::vector<Candidato> get_candidatos_eleitos_ordenados(std::map<int, Partido> &partidos) {
    std::vector<Candidato> candidatos_eleitos;

    for(auto &[key, value] : partidos) {
        for(auto &c : value.get_candidato_vector()) {
            if(c.is_eleito()) {
                candidatos_eleitos.push_back(c);
            }
        }
    }
    std::sort(candidatos_eleitos.begin(), candidatos_eleitos.end(), [](const Candidato &c1, const Candidato &c2) {
        return c1.get_quantidade_votos() > c2.get_quantidade_votos();
    });

    return candidatos_eleitos;
}
