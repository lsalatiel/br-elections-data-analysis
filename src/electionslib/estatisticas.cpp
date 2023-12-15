#include "include/estatisticas.h"
#include <bits/stdc++.h>

std::vector<Candidato> get_candidatos_eleitos_ordenados(std::map<int, Partido> &partidos) {
    std::vector<Candidato> candidatos_eleitos;

    for(auto &[key, value] : partidos) {
        for(auto &c : value.get_candidato_vector()) {
            if(c.is_eleito()) 
                candidatos_eleitos.push_back(c);       
        }
    }
    std::sort(candidatos_eleitos.begin(), candidatos_eleitos.end(), [](const Candidato &c1, const Candidato &c2) {
        return c1.get_quantidade_votos() > c2.get_quantidade_votos();
    }); //tem que verificar a data de nascimento?

    return candidatos_eleitos;
}

std::vector<Candidato> get_candidatos_mais_votados(std::map<int, Partido> &partidos){
    std::vector<Candidato> candidatos_mais_votados;
    for(auto &[key, value] : partidos) {
        for(auto &c : value.get_candidato_vector()) 
            candidatos_mais_votados.push_back(c); 
    }

    std::sort(candidatos_mais_votados.begin(), candidatos_mais_votados.end(), [](const Candidato &c1, const Candidato &c2) {
        return c1.get_quantidade_votos() > c2.get_quantidade_votos();
    });

    return candidatos_mais_votados;
}

void print_partidos_com_votos(std::map<int, Partido> &partidos) {
    std::vector<std::pair<int, Partido>> vector_partidos;
    for (auto& it : partidos)
        vector_partidos.push_back(it);

    sort(vector_partidos.begin(), vector_partidos.end(), [](const auto& p1, const auto& p2) {
        if(p1.second.get_votos_totais() == p2.second.get_votos_totais())
            return p1.second.get_numero() < p2.second.get_numero();
        else
            return p1.second.get_votos_totais() > p2.second.get_votos_totais();
    });

    int i = 1;
    for (const auto& [key, value] : vector_partidos) { // Use const auto&
        int qtd_eleitos = 0, qtd_votos_nominais = 0, qtd_votos_legenda = 0;

        std::cout << i << " - ";
        std::cout << value.get_sigla() << " - " << value.get_numero() << ", ";
        qtd_votos_legenda = value.get_votos_legenda();
        qtd_votos_nominais = value.get_votos_nominais();

        for (auto& c : value.get_candidato_vector()) {
            if (c.is_eleito()) qtd_eleitos++;
        }

        if(qtd_votos_legenda + qtd_votos_nominais > 1)
            std::cout << qtd_votos_legenda + qtd_votos_nominais << " votos ";
        else
            std::cout << qtd_votos_legenda + qtd_votos_nominais << " voto ";

        if(qtd_votos_nominais > 1)
            std::cout << "(" << qtd_votos_nominais << " nominais e ";
        else
            std::cout << "(" << qtd_votos_nominais << " nominal e ";

        std::cout << qtd_votos_legenda << " de legenda), ";

        if(qtd_eleitos != 1 && qtd_eleitos != 0)
            std::cout << qtd_eleitos << " candidatos eleitos\n";
        else
            std::cout << qtd_eleitos << " candidato eleito\n";

        i++;
    }
}
