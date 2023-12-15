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

// void print_primeiro_ultimo_colocados(std::map<int, Partido> &partidos) {
//     std::vector<std::pair<int, Partido>> vector_partidos = ordena_partidos_por_mais_votado(partidos);

//     int i = 1;
//     for (const auto& [key, value] : vector_partidos) {
//         std::vector candidatos = value.get_candidato_vector(); 
//         std::sort(candidatos.begin(), candidatos.end(), [](const Candidato &c1, const Candidato &c2) {
//             return c1.get_quantidade_votos() > c2.get_quantidade_votos();
//         });

//         if(candidatos.empty()) continue;

//         Candidato primeiro_colocado = candidatos.front();
//         Candidato ultimo_colocado;
        
//         int j = 0;
//         int size = candidatos.size();
//         do {
//             if(++j == size) {
//                 ultimo_colocado = primeiro_colocado;
//                 break;
//             }
//             ultimo_colocado = candidatos[size - j];
//         } while(!ultimo_colocado.is_candidatura_deferida());

//         std::cout << i << " - ";
//         std::cout << value.get_sigla() << " - " << value.get_numero() << ", " << primeiro_colocado.get_nome_na_urna() << " (" << primeiro_colocado.get_numero_candidato() << ", ";

//         if(primeiro_colocado.get_quantidade_votos() > 1)
//             std::cout << primeiro_colocado.get_quantidade_votos() << " votos) / " << ultimo_colocado.get_nome_na_urna() << " (" << ultimo_colocado.get_numero_candidato() << ", ";
//         else
//             std::cout << primeiro_colocado.get_quantidade_votos() << " voto) / " << ultimo_colocado.get_nome_na_urna() << " (" << ultimo_colocado.get_numero_candidato() << ", ";

//         if(ultimo_colocado.get_quantidade_votos() > 1)
//             std::cout << ultimo_colocado.get_quantidade_votos() << " votos)" << std::endl;
//         else
//             std::cout << ultimo_colocado.get_quantidade_votos() << " voto)" << std::endl;

//         i++;
//     }


void print_eleitos_por_faixa_etaria(std::vector<Candidato> candidatos_eleitos, std::tm date) {
    int menor30 = 0, menor40 = 0, menor50 = 0,  menor60 = 0, maior60 = 0;
    for(Candidato c : candidatos_eleitos) {
        std::tm data_nascimento = c.get_data_nascimento();
        std::time_t time_diff = std::difftime(std::mktime(&date), std::mktime(&data_nascimento));
        int idade = static_cast<int>(time_diff) / (60 * 60 * 24 * 365);

        if(idade < 30)
            menor30++;
        else if(idade < 40)
            menor40++;
        else if(idade < 50)
            menor50++;
        else if(idade < 60)
            menor60++;
        else
            maior60++;
    }

    std::cout << "      Idade < 30: " << menor30 << " (" << std::fixed << std::setprecision(2) << menor30 * 100.0 / candidatos_eleitos.size() << "%)" << std::endl; 
    std::cout << "30 <= Idade < 40: " << menor40 << " (" << std::fixed << std::setprecision(2) << menor40 * 100.0 / candidatos_eleitos.size() << "%)" << std::endl; 
    std::cout << "40 <= Idade < 50: " << menor50 << " (" << std::fixed << std::setprecision(2) <<  menor50 * 100.0 / candidatos_eleitos.size() << "%)" << std::endl;
    std::cout << "50 <= Idade < 60: " << menor60 << " (" << std::fixed << std::setprecision(2) <<  menor60 * 100.0 / candidatos_eleitos.size() << "%)" << std::endl; 
    std::cout << "60 <= Idade     : " << maior60 << " (" << std::fixed << std::setprecision(2) <<  maior60 * 100.0 / candidatos_eleitos.size() << "%)" << std::endl;
}

 void print_eleitos_por_genero(std::vector<Candidato> candidatos_eleitos) {
    int qtd_masculino = 0, qtd_feminino = 0;
    for(Candidato c : candidatos_eleitos) {
        if(c.get_genero() == Candidato::Genero::MASCULINO)
            qtd_masculino++;
        else
            qtd_feminino++;
    }

    std::cout << "Feminino:  " << qtd_feminino << " (" << std::fixed << std::setprecision(2) << qtd_feminino * 100.0 / candidatos_eleitos.size() << "%)" << std::endl;
    std::cout << "Masculino: " << qtd_masculino << " (" << std::fixed << std::setprecision(2) << qtd_masculino * 100.0 / candidatos_eleitos.size() << "%)" << std::endl;
}

