#pragma once
#include <string>
#include "Categoria.h"

// Los valores numericos coinciden con la tabla del enunciado.
enum class TipoBodega {
    GENERAL = 1,
    FRAGIL = 2,
    TECNOLOGIA = 3,
    DOCUMENTOS = 4
};

inline std::string tipoBodegaToString(TipoBodega t) {
    switch (t) {
    case TipoBodega::GENERAL:    return "General";
    case TipoBodega::FRAGIL:     return "Fragil";
    case TipoBodega::TECNOLOGIA: return "Tecnologia";
    case TipoBodega::DOCUMENTOS: return "Documentos";
    }
    return "Desconocido";
}

// Codigo de tipo (1 a 4) -> TipoBodega. Devuelve false si el codigo no es valido.
inline bool tipoBodegaDesdeInt(int codigo, TipoBodega& resultado) {
    if (codigo < 1 || codigo > 4) return false;
    resultado = static_cast<TipoBodega>(codigo);
    return true;
}

// Compatibilidad directa: General-General, Fragil-Fragil, etc.
inline bool tipoBodegaEsCompatible(TipoBodega tipo, Categoria categoria) {
    switch (tipo) {
    case TipoBodega::GENERAL:    return categoria == Categoria::GENERAL;
    case TipoBodega::FRAGIL:     return categoria == Categoria::FRAGIL;
    case TipoBodega::TECNOLOGIA: return categoria == Categoria::TECNOLOGIA;
    case TipoBodega::DOCUMENTOS: return categoria == Categoria::DOCUMENTOS;
    }
    return false;
}