#if !defined(_VOTOS_DESERIALIZER_H_)
#define _VOTOS_DESERIALIZER_H_

#include <iostream>

#include "candidato.h"
#include "partido.h"
#include "federacao.h"

void processa_votos(std::map<int, Partido> &partidos, Cargo cargo, std::string filePath);

#endif
