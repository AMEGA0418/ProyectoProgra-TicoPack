#pragma once
#include "CentroDistribucion.h"

class Reportes {
public:
    static void resumenCentro(const CentroDistribucion& centro);
    static void estadoPaquetes(const CentroDistribucion& centro);
    static void ocupacionBodegas(const CentroDistribucion& centro);
};

