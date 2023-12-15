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

void print_candidatos_eleitos_ordenados(std::vector<Candidato> &candidatos_eleitos, std::map<int, Partido> &partidos, Cargo cargo, const std::vector<Federacao>& federacoes) {
    std::cout << "Número de vagas: " << candidatos_eleitos.size() << "\n" << std::endl;
    std::string text = cargo == Cargo::FEDERAL ? "Deputados federais eleitos:" : "Deputados estaduais eleitos:";
    std::cout<< text << std::endl;
    print_candidatos(candidatos_eleitos, federacoes, partidos);
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

void print_candidatos_mais_votados(std::vector<Candidato> &candidatos_mais_votados_em_vagas, std::vector<Candidato> &candidatos_eleitos, std::map<int, Partido> &partidos, const std::vector<Federacao> &federacoes) {
    std::cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;
    print_candidatos(candidatos_mais_votados_em_vagas, federacoes, partidos);
}

std::vector<Candidato> __get_intersection(std::vector<Candidato> v1, std::vector<Candidato> v2){
    // i love cppreference <3
    std::vector<Candidato> v3;

    std::sort(v1.begin(), v1.end(), [](const Candidato &c1, const Candidato &c2) {
        return c1.get_quantidade_votos() > c2.get_quantidade_votos();
    });
    std::sort(v2.begin(), v2.end(), [](const Candidato &c1, const Candidato &c2) {
        return c1.get_quantidade_votos() > c2.get_quantidade_votos();
    });

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3), [](const Candidato &c1, const Candidato &c2) {
                              return c1.get_quantidade_votos() > c2.get_quantidade_votos();
                          });
    return v3;
}

void print_candidatos_eleitos_majoritaria(std::vector<Candidato> &candidatos_mais_votados, std::vector<Candidato> &candidatos_mais_votados_em_vagas, std::vector<Candidato> &candidatos_eleitos,
        std::map<int, Partido> &partidos, std::vector<Federacao> &federacoes) {
    std::cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << std::endl;
    std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

    std::vector<Candidato> intersection = __get_intersection(candidatos_eleitos, candidatos_mais_votados_em_vagas);

    std::vector<Candidato> candidatos_eleitos_majoritaria;
    std::set_difference(
            candidatos_mais_votados_em_vagas.begin(), candidatos_mais_votados_em_vagas.end(),
            intersection.begin(), intersection.end(),
            std::back_inserter(candidatos_eleitos_majoritaria), [](const Candidato &c1, const Candidato &c2) {
                return c1.get_quantidade_votos() > c2.get_quantidade_votos();
            }
            );

    // TODO: FALTA DAR SORT E MUDAR A FUNCAO LAMBDA AI DE CIMA PRA FUNCAO DE ORDENAR CORRETA

    for(auto &c : candidatos_eleitos_majoritaria) {
        int i = 0;
        for(auto &c2 : candidatos_mais_votados) {
            i++;
            if(c2.get_numero_candidato() == c.get_numero_candidato()) break;
        }
        std::cout << i << " - ";
        for(auto &f : federacoes) {
            if(f.get_numero() == c.get_numero_federacao()) {
                std::cout << "*";
                break;
            }
        }

        int numero_partido = c.get_numero_partido();
        auto it = partidos.find(numero_partido);
        const Partido &p = it->second;
        std::cout << c.get_nome_na_urna() << " (" << p.get_sigla() << ", " << c.get_quantidade_votos() << " votos)" << std::endl;
    }
}

void print_candidatos_eleitos_proporcional(std::vector<Candidato> &candidatos_mais_votados, std::vector<Candidato> &candidatos_mais_votados_em_vagas, std::vector<Candidato> &candidatos_eleitos,
        std::map<int, Partido> &partidos, std::vector<Federacao> &federacoes) {
    std::vector<Candidato> intersection = __get_intersection(candidatos_eleitos, candidatos_mais_votados_em_vagas);

    std::vector<Candidato> candidatos_eleitos_proporcional;
    std::set_difference(
            candidatos_eleitos.begin(), candidatos_eleitos.end(),
            intersection.begin(), intersection.end(),
            std::back_inserter(candidatos_eleitos_proporcional), [](const Candidato &c1, const Candidato &c2) {
                return c1.get_quantidade_votos() > c2.get_quantidade_votos();
            }
            );

    std::sort(candidatos_eleitos_proporcional.begin(), candidatos_eleitos_proporcional.end(), [](const Candidato &c1, const Candidato &c2) {
        return c1.get_quantidade_votos() > c2.get_quantidade_votos();
    });

    // TODO: FALTA MUDAR A FUNCAO LAMBDA AI DE CIMA PRA FUNCAO DE ORDENAR CORRETA
    
    std::cout << "\nEleitos, que se beneficiaram do sistema proporcional:" << std::endl;
    std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

    for(auto &c : candidatos_eleitos_proporcional) {
        int i = 0;
        for(auto &c2 : candidatos_mais_votados) {
            i++;
            if(c2.get_numero_candidato() == c.get_numero_candidato()) break;
        }
        std::cout << i << " - ";
        for(auto &f : federacoes) {
            if(f.get_numero() == c.get_numero_federacao()) {
                std::cout << "*";
                break;
            }
        }
        
        int numero_partido = c.get_numero_partido();
        auto it = partidos.find(numero_partido);
        const Partido &p = it->second;
        std::cout << c.get_nome_na_urna() << " (" << p.get_sigla() << ", " << c.get_quantidade_votos() << " votos)" << std::endl;
    }
}

void print_partidos_com_votos(std::map<int, Partido> &partidos) {
    std::cout << "\nVotação dos partidos e número de candidatos eleitos:" << std::endl;
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
    std::cout << "\nEleitos, por faixa etária (na data da eleição):" << std::endl;
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
    std::cout << "\nEleitos, por gênero:" << std::endl;
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


void print_total_votos(std::map<int, Partido> &partidos) {
    int qtd_votos_legenda = 0, qtd_votos_nominais = 0;
    for(const std::pair<int, Partido> x : partidos){
        qtd_votos_legenda += x.second.get_votos_legenda();
        qtd_votos_nominais += x.second.get_votos_nominais();
    }

std::cout << "Total de votos válidos:    " << qtd_votos_legenda + qtd_votos_nominais << std::endl;
    std::cout << "Total de votos nominais:   " << qtd_votos_nominais << " (" << std::fixed << std::setprecision(2) << qtd_votos_nominais * 100.0 / (qtd_votos_legenda + qtd_votos_nominais) << "%)\n";
    std::cout << "Total de votos de legenda: " << qtd_votos_legenda << " (" << std::fixed << std::setprecision(2) << qtd_votos_legenda * 100.0 / (qtd_votos_legenda + qtd_votos_nominais) << "%)\n";
}

void print_candidatos(const std::vector<Candidato>& candidatos, const std::vector<Federacao>& federacoes, const std::map<int, Partido>& partidos) {
	int i = 1;
	for(const Candidato &c : candidatos) {
		std::cout << i << " - ";
		for(const Federacao &f : federacoes) {
			if(f.get_numero() == c.get_numero_federacao()) {
				std::cout << "*";
				break;
			}
		}

		std::string numero_partido = std::to_string(c.get_numero_candidato()).substr(0, 2);
		auto it = partidos.find(std::stoi(numero_partido));
		const Partido &p = it->second;

		//std::cout << c.print_candidato();
		std::cout << "" << c.get_nome_na_urna();
		std::cout << " (" << p.get_sigla() << ", " << c.get_quantidade_votos() << " votos)" << std::endl;
		i++;
	}
}

std::vector<std::pair<int, Partido>> ordena_partidos_por_total_votos(const std::map<int, Partido>& partidos){
	std::vector<std::pair<int, Partido>> vector_partidos;
    for(auto& it : partidos)
        vector_partidos.push_back(it);

    std::sort(vector_partidos.begin(), vector_partidos.end(), [](const auto& p1, const auto& p2) {
        if(p1.second.get_votos_totais() == p2.second.get_votos_totais())
            return p1.second.get_numero() < p2.second.get_numero();
        else
            return p1.second.get_votos_totais() > p2.second.get_votos_totais();
    });

	return vector_partidos;
}

// std::vector<std::pair<int, Partido>> ordena_partidos_por_mais_votado(const std::map<int, Partido>& partidos){
// 	std::vector<std::pair<int, Partido>> vector_partidos;
//     for(auto& it : partidos)
//         vector_partidos.push_back(it);

//     std::sort(vector_partidos.begin(), vector_partidos.end(), [](const auto& p1, const auto& p2) {
// 		const Candidato *c1 = p1.second.get_candidato_mais_votado();
// 		if(!c1) return 1; //TO DO     
// 		const Candidato *c2 = p2.second.get_candidato_mais_votado();
// 		if(!c2) return -1;

// 		return c1->get_quantidade_votos() > c2->get_quantidade_votos();
//     });

// 	return vector_partidos;
// }
