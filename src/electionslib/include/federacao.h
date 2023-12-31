#if !defined (_FEDERACAO_H_)
#define _FEDERACAO_H_

#include <iostream>
#include "partido.h"

class Federacao {
    int numero;
    std::vector<Partido> partidos;

    public:
        Federacao() {};
        Federacao(int numero);

        int get_numero() const;

        void add_partido(Partido &partido);
};

#endif
