#include "Tarifas.h"

// Valores de ejemplo en colones por kg: AJUSTAR a los del enunciado.
const double Tarifas::TARIFAS_KG[4] = { 1500.0, 2000.0, 2500.0, 1000.0 };

double Tarifas::obtenerTarifa(Categoria c) {
    switch (c) {
    case GENERAL:    return TARIFAS_KG[0];
    case FRAGIL:     return TARIFAS_KG[1];
    case TECNOLOGIA: return TARIFAS_KG[2];
    case DOCUMENTOS: return TARIFAS_KG[3];
    }
    return TARIFAS_KG[0];
}
