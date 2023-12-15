#include <iostream>
#include <sstream>
#include "electionslib/include/candidatos_deserializer.h"
#include "electionslib/include/partido.h"
#include "electionslib/include/votos_deserializer.h"
#include "electionslib/include/candidato.h"
#include "electionslib/include/utils.h"
#include "electionslib/include/estatisticas.h"

int main(int argc, char** argv) {
    check_arguments(argc, argv, 5, "<cargo> <candidatos.csv> <votacao.csv> <data_eleicao>");

    Cargo cargo = update_cargo(argv[1], "--federal", "--estadual", "Invalid cargo. Usage: --federal or --estadual");

    const std::string &candidatos_file_path = argv[2];
    const std::string &votacao_file_path = argv[3];

    std::tm data_eleicao = {};
    std::istringstream iss(argv[4]);
    char delimiter;
    iss >> data_eleicao.tm_mday >> delimiter >> data_eleicao.tm_mon >> delimiter >> data_eleicao.tm_year;
    data_eleicao.tm_mon -= 1;
    data_eleicao.tm_year -= 1900;

    std::map<int, Partido> partidos = processa_candidatos(cargo, candidatos_file_path);
    processa_votos(partidos, cargo, votacao_file_path);
    std::vector federacoes = cria_federacoes(partidos);

    /*
    Espírito Santo:
    Total de votos válidos:    2.084.430
    Total de votos nominais:   2.008.658 (96,36%)
    Total de votos de legenda: 75.772 (3,64%)
    */
    
    /* std::locale brasilLocale("pt_BR.UTF-8"); */
    /* std::cout.imbue(brasilLocale); */
    
    // primeiro e segundo relatorio...
    std::vector<Candidato> candidatos_eleitos = get_candidatos_eleitos_ordenados(partidos);
    std::cout << "Número de vagas: " << candidatos_eleitos.size() << "\n" << std::endl;
    std::string text = cargo == Cargo::FEDERAL ? "Deputados federais eleitos:" : "Deputados estaduais eleitos:";
    std::cout<< text << std::endl;
    print_candidatos(candidatos_eleitos, federacoes, partidos);


    // terceiro relatorio...
    std::cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;
    std::vector<Candidato> candidatos_mais_votados = get_candidatos_mais_votados(partidos);
    std::vector<Candidato> candidatos_mais_votados_em_vagas(
        candidatos_mais_votados.begin(), 
        candidatos_mais_votados.begin() + std::min(candidatos_eleitos.size(), candidatos_mais_votados.size())
    );
    print_candidatos(candidatos_mais_votados_em_vagas, federacoes, partidos);

    // sexto relatorio...
    std::cout << "\nVotação dos partidos e número de candidatos eleitos:" << std::endl;
    print_partidos_com_votos(partidos);

    // sétimo relatorio...
    std::cout << "\nPrimeiro e último colocados de cada partido:" << std::endl;
    //print_primeiro_ultimo_colocados(partidos);
    //funcao ordena_partidos_por_total_votos em util.cpp
    //funcao get_candidato_mais_votado em partido.cpp
    //RESOLVER ESSAS DUAS para então o sétimo relatório funcionar!
    

    // oitavo relatorio...
    std::cout << "\nEleitos, por faixa etária (na data da eleição):" << std::endl;
    print_eleitos_por_faixa_etaria(candidatos_eleitos, data_eleicao);

    // nono relatorio...
    std::cout << "\nEleitos, por gênero:" << std::endl;
    print_eleitos_por_genero(candidatos_eleitos);
    std::cout << std::endl;

    // decimo relatorio...
    print_total_votos(partidos);
    std::cout << std::endl;
    
    return 0;
}
