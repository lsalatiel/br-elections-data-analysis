#if !defined(_CANDIDATOS_DESERIALIZER_H_)
#define _CANDIDATOS_DESERIALIZER_H_

#include <iostream>

#include "candidato.h"
#include "partido.h"
#include "federacao.h"

std::map<int, Partido> processa_candidatos(Cargo cargo, const std::string &file_path);

#endif
