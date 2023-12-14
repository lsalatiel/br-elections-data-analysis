#if !defined(_CANDIDATOS_DESERIALIZER_H_)
#define _CANDIDATOS_DESERIALIZER_H_

#include <iostream>

#include "candidato.h"
#include "partido.h"
#include "federacao.h"

enum class Cargo { FEDERAL = 6, ESTADUAL = 7 };

std::map<int, Partido> processa_candidatos(Cargo cargo, const std::string &file_path);

#endif
