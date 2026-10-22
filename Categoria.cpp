#include "Categoria.h"

const int Categoria::GENERAL = 1;
const int Categoria::FRAGIL = 2;
const int Categoria::TECNOLOGIA = 3;
const int Categoria::DOCUMENTOS = 4;

bool Categoria::esValida(int categoria) {
    return categoria >= GENERAL && categoria <= DOCUMENTOS;
}

string Categoria::toString(int categoria) {
    if (categoria == GENERAL) return "General";
    if (categoria == FRAGIL) return "Fragil";
    if (categoria == TECNOLOGIA) return "Tecnologia";
    if (categoria == DOCUMENTOS) return "Documentos";
    return "Desconocida";
}