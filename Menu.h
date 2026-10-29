#pragma once
#include "SistemaTicoPack.h"
#include "Reportes.h"
#include "PersonaFisica.h"
#include "Empresa.h"
#include "Tarifas.h"
#include "Validador.h"
#include <iostream>

using namespace std;

class Menu {
private:
    SistemaTicoPack* sistema;

    string leerTexto(const string& mensaje) const;
    int leerEntero(const string& mensaje) const;
    double leerDecimal(const string& mensaje) const;
    Fecha leerFecha(const string& mensaje) const;
    CentroDistribucion* seleccionarCentro() const;
    Colaborador* seleccionarColaborador(CentroDistribucion* centro) const;

    void limpiarPantalla() const;
    void confirmarAccion(const string& mensaje) const;
    void pausar() const;

    void menuCentros();
    void menuClientes();
    void menuColaboradores();
    void menuBodegas();
    void menuPaquetes();
    void menuSolicitudes();
    void menuDespachos();
    void menuReportes();
    void menuBusquedasGlobales();

public:
    explicit Menu(SistemaTicoPack* sistema);

    void mostrarTitulo() const;
    void mostrarOpciones() const;
    void ejecutar();
};