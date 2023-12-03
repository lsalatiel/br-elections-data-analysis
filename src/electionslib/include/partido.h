#if !defined (_PARTIDO_H_)
#define _PARTIDO_H_

#include <iostream>

class Partido {
    std::string sigla;
    std::string numero;
    int numero_federacao;
    int votos_nominais;
    int votos_legenda;
    // map <std::string, Candidato>

    public:
        Partido();
        Partido(std::string sigla, std::string numero);
};

#endif
