#include "include/federacao.h"

Federacao::Federacao(int numero) :
            numero(numero) {}

int Federacao::get_numero() const {
    return numero;
}

void Federacao::add_partido(Partido &partido) {
    partidos.push_back(partido);
}
