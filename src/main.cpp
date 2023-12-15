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

    /* std::locale brasilLocale("pt_BR.UTF-8"); */
    /* std::cout.imbue(brasilLocale); */
    
    // primeiro e segundo relatorio...
    std::vector<Candidato> candidatos_eleitos = get_candidatos_eleitos_ordenados(partidos);
    print_candidatos_eleitos_ordenados(candidatos_eleitos, partidos, cargo, federacoes);
    std::cout << std::endl;

    // terceiro relatorio...
    std::vector<Candidato> candidatos_mais_votados = get_candidatos_mais_votados(partidos);
    std::vector<Candidato> candidatos_mais_votados_em_vagas(
        candidatos_mais_votados.begin(), 
        candidatos_mais_votados.begin() + std::min(candidatos_eleitos.size(), candidatos_mais_votados.size())
    );
    print_candidatos_mais_votados(candidatos_mais_votados_em_vagas, candidatos_eleitos, partidos, federacoes);
    std::cout << std::endl;

    /* System.out.println("\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:"); */
    /* System.out.println("(com sua posição no ranking de mais votados)"); */
    /* Estatisticas.printCandidatosEleitosMajoritaria(candidatosEleitos, candidatosMaisVotados, candidatosMaisVotadosEmVagas, federacoes, partidos); */
    print_candidatos_eleitos_majoritaria(candidatos_mais_votados, candidatos_mais_votados_em_vagas, candidatos_eleitos, partidos, federacoes);

    // quinto relatorio...
    /* System.out.println("\nEleitos, que se beneficiaram do sistema proporcional:"); */
    /* System.out.println("(com sua posição no ranking de mais votados)"); */
    /* Estatisticas.printCandidatosEleitosProporcional(candidatosEleitos, candidatosMaisVotados, candidatosMaisVotadosEmVagas, federacoes, partidos); */
    print_candidatos_eleitos_proporcional(candidatos_mais_votados, candidatos_mais_votados_em_vagas, candidatos_eleitos, partidos, federacoes);

    // sexto relatorio...
    print_partidos_com_votos(partidos);

    // sétimo relatorio...
    std::cout << "\nPrimeiro e último colocados de cada partido:" << std::endl;
    //print_primeiro_ultimo_colocados(partidos);
    //funcao ordena_partidos_por_total_votos em util.cpp
    //funcao get_candidato_mais_votado em partido.cpp
    //RESOLVER ESSAS DUAS para então o sétimo relatório funcionar!
    

    // oitavo relatorio...
    print_eleitos_por_faixa_etaria(candidatos_eleitos, data_eleicao);

    // nono relatorio...
    print_eleitos_por_genero(candidatos_eleitos);

    // decimo relatorio...
    print_total_votos(partidos);
    std::cout << std::endl;
    
    return 0;
}

/*
   Espírito Santo:
   Total de votos válidos:    2.084.430
   Total de votos nominais:   2.008.658 (96,36%)
   Total de votos de legenda: 75.772 (3,64%)
   */
