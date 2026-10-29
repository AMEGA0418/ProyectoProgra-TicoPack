#pragma once
#include <iostream>
#include "CentroDistribucion.h"
#include "EstadoPaquete.h"

using namespace std;

class Reportes {
public:
    static void resumenCentro(const CentroDistribucion& centro);
    static void estadoPaquetes(const CentroDistribucion& centro);
    static void ocupacionBodegas(const CentroDistribucion& centro);
};

