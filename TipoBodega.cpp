#include "TipoBodega.h"

const int TipoBodega::GENERAL = 1;
const int TipoBodega::FRAGIL = 2;
const int TipoBodega::TECNOLOGIA = 3;
const int TipoBodega::DOCUMENTOS = 4;

bool TipoBodega::esValido(int tipo) {
    return tipo >= GENERAL && tipo <= DOCUMENTOS;
}

string TipoBodega::toString(int tipo) {
    if (tipo == GENERAL) return "General";
    if (tipo == FRAGIL) return "Fragil";
    if (tipo == TECNOLOGIA) return "Tecnologia";
    if (tipo == DOCUMENTOS) return "Documentos";
    return "Desconocido";
}

bool TipoBodega::esCompatible(int tipo, int categoria) {
    if (tipo == GENERAL) return categoria == Categoria::GENERAL;
    if (tipo == FRAGIL) return categoria == Categoria::FRAGIL;
    if (tipo == TECNOLOGIA) return categoria == Categoria::TECNOLOGIA;
    if (tipo == DOCUMENTOS) return categoria == Categoria::DOCUMENTOS;
    return false;
}
