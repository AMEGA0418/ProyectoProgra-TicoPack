#pragma once
#include <string>
#include <iostream>
#include "TipoBodega.h"
#include "Categoria.h"

class Celda;
class Paquete;

using namespace std;

class Bodega {
private:
    string codigo;
    string nombre;
    int tipo;           // valor de TipoBodega (1 a 4)
    int filas;
    int columnas;
    Celda*** matriz;   // matriz dinamica de punteros a Celda

public:
    // Filas y columnas deben ser enteros > 0: validarlo en el menu con esto.
    static bool esDistribucionValida(int filas, int columnas);

    // Reserva la matriz al crearse. Si filas/columnas no son validas queda
    // sin matriz (0 x 0) como resguardo; el menu debe haberlo rechazado antes.
    Bodega(const string& codigo, const string& nombre, int tipo,
        int filas, int columnas);
    ~Bodega();

    // Una bodega no se copia (doble liberacion de la matriz).
    Bodega(const Bodega&) = delete;
    Bodega& operator=(const Bodega&) = delete;

    void reservarMatriz();
    void liberarMatriz();

    string getCodigo() const;
    string getNombre() const;
    int getTipo() const;
    int getFilas() const;
    int getColumnas() const;

    bool posicionValida(int fila, int columna) const;
    Celda* consultarCelda(int fila, int columna) const;

    // Solo maneja la matriz. Mantener la ubicacion del Paquete coherente
    // es responsabilidad de CentroDistribucion.
    bool asignarPaquete(int fila, int columna, Paquete* paquete);
    bool liberarCelda(int fila, int columna);

    Celda* primeraCeldaLibre() const;
    bool esCompatible(int categoria) const;

    int totalCeldas() const;
    int celdasOcupadas() const;
    int celdasLibres() const;
    double porcentajeOcupacion() const;
    double porcentajeDisponible() const;

    void mostrarDatos() const;
    // Dibuja la matriz en consola. Con usarColor=true usa colores ANSI
    // (verde libre / rojo ocupada); solo si la consola los soporta.
    void mostrarMatriz(bool usarColor = false) const;
};