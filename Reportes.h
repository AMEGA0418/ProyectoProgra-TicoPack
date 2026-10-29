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
    static void historialCliente(const CentroDistribucion& centro,
        Cliente* cliente);
    static void clientesPorEnvios(const CentroDistribucion& centro);
    static void bitacoraPaquete(Paquete* paquete);
    static void despachoDePaquete(const CentroDistribucion& centro,
        Paquete* paquete);
    static void despachosPorColaborador(const CentroDistribucion& centro,
        Colaborador* colaborador);
};

