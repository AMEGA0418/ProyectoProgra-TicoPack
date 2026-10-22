#pragma once
#include <string>

enum class Categoria {
    GENERAL,
    FRAGIL,
    TECNOLOGIA,
    DOCUMENTOS
};

inline std::string categoriaToString(Categoria c) {
    switch (c) {
    case Categoria::GENERAL:    return "General";
    case Categoria::FRAGIL:     return "Fragil";
    case Categoria::TECNOLOGIA: return "Tecnologia";
    case Categoria::DOCUMENTOS: return "Documentos";
    }
    return "Desconocida";
}

// Para los menus: 1=General, 2=Fragil, 3=Tecnologia, 4=Documentos.
// Devuelve false (sin modificar 'resultado') si la opcion no es valida.
inline bool categoriaDesdeInt(int opcion, Categoria& resultado) {
    switch (opcion) {
    case 1: resultado = Categoria::GENERAL;    return true;
    case 2: resultado = Categoria::FRAGIL;     return true;
    case 3: resultado = Categoria::TECNOLOGIA; return true;
    case 4: resultado = Categoria::DOCUMENTOS; return true;
    }
    return false;
}