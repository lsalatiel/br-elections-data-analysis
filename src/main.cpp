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

    Cargo cargo = initialize_cargo(argv[1], "--federal", "--estadual", "Invalid cargo. Usage: --federal or --estadual");

    const std::string &candidatos_file_path = argv[2];
    const std::string &votacao_file_path = argv[3];

    std::tm data_eleicao = initialize_date(argv[4]);

    std::map<int, Partido> partidos = processa_candidatos(cargo, candidatos_file_path);
    processa_votos(partidos, cargo, votacao_file_path);
    std::vector federacoes = cria_federacoes(partidos);

    /* std::locale brasilLocale("pt_BR.UTF-8");  */
    /* std::cout.imbue(brasilLocale);  */
    
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

    // quarto relatorio...
    print_candidatos_eleitos_majoritaria(candidatos_mais_votados, candidatos_mais_votados_em_vagas, candidatos_eleitos, partidos, federacoes);

    // quinto relatorio...
    print_candidatos_eleitos_proporcional(candidatos_mais_votados, candidatos_mais_votados_em_vagas, candidatos_eleitos, partidos, federacoes);

    // sexto relatorio...
    print_partidos_com_votos(partidos);

    // sétimo relatorio...
    std::cout << "\nPrimeiro e último colocados de cada partido:" << std::endl;
    print_primeiro_ultimo_colocados(partidos);

    // oitavo relatorio...
    print_eleitos_por_faixa_etaria(candidatos_eleitos, data_eleicao);

    // nono relatorio...
    print_eleitos_por_genero(candidatos_eleitos);
    std::cout << std::endl;

    // decimo relatorio...
    print_total_votos(partidos);
    std::cout << std::endl;

    /* std::cout.imbue(std::locale("C")); */
    
    return 0;
}
