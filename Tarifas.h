#ifndef TARIFAS_H
#define TARIFAS_H
#include "Enumeraciones.h"

// Tarifa por kilogramo segun la categoria del paquete dadas en el proyecto2 .
class Tarifas {
private:

    static const double TARIFAS_KG[4]; // GENERAL, FRAGIL, TECNOLOGIA, DOCUMENTOS

public:

    static double obtenerTarifa(Categoria c);
};

#endif
