#include "include/estatisticas.h"
#include <bits/stdc++.h>
#include "include/utils.h"

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
    std::vector<std::pair<int, Partido>> vector_partidos = ordena_partidos_por_total_votos(partidos);

    int i = 1;
    for(const auto& [key, value] : vector_partidos) { 
        int qtd_eleitos = 0, qtd_votos_nominais = 0, qtd_votos_legenda = 0;

        std::cout << i << " - ";
        std::cout << value.get_sigla() << " - " << value.get_numero() << ", ";
        qtd_votos_legenda = value.get_votos_legenda();
        qtd_votos_nominais = value.get_votos_nominais();

        for(auto& c : value.get_candidato_vector()) {
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

void print_primeiro_ultimo_colocados(std::map<int, Partido> &partidos) {
    std::vector<std::pair<int, Partido>> vector_partidos = ordena_partidos_por_mais_votado(partidos);

    int i = 1;
    for (const auto& [key, value] : vector_partidos) {
        std::vector candidatos = value.get_candidato_vector(); 
        std::sort(candidatos.begin(), candidatos.end(), [](const Candidato &c1, const Candidato &c2) {
            return c1.get_quantidade_votos() > c2.get_quantidade_votos();
        });

        if(candidatos.empty()) continue;

        Candidato primeiro_colocado = candidatos.front();
        Candidato ultimo_colocado;
        
        int j = 0;
        int size = candidatos.size();
        do {
            if(++j == size) {
                ultimo_colocado = primeiro_colocado;
                break;
            }
            ultimo_colocado = candidatos[size - j];
        } while(!ultimo_colocado.is_candidatura_deferida());

        std::cout << i << " - ";
        std::cout << value.get_sigla() << " - " << value.get_numero() << ", " << primeiro_colocado.get_nome_na_urna() << " (" << primeiro_colocado.get_numero_candidato() << ", ";

        if(primeiro_colocado.get_quantidade_votos() > 1)
            std::cout << primeiro_colocado.get_quantidade_votos() << " votos) / " << ultimo_colocado.get_nome_na_urna() << " (" << ultimo_colocado.get_numero_candidato() << ", ";
        else
            std::cout << primeiro_colocado.get_quantidade_votos() << " voto) / " << ultimo_colocado.get_nome_na_urna() << " (" << ultimo_colocado.get_numero_candidato() << ", ";

        if(ultimo_colocado.get_quantidade_votos() > 1)
            std::cout << ultimo_colocado.get_quantidade_votos() << " votos)" << std::endl;
        else
            std::cout << ultimo_colocado.get_quantidade_votos() << " voto)" << std::endl;

        i++;
    }
}
