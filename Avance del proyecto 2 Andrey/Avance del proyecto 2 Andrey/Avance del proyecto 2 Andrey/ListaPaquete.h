#pragma once
#ifndef LISTAPAQUETE_H
#define LISTAPAQUETE_H

#include <string>
#include "Categoria.h"
#include "EstadoPaquete.h"

using namespace std;

class Cliente;
class Centro;
class Bodega;

class Paquete {
private:
    string codigo;
    string descripcion;
    float peso;
    Categoria categoria;
    EstadoPaquete estado;
    Cliente* cliente;
    Centro* centro;
    Bodega* bodega;
    int fila;
    int columna;

public:
    Paquete(string codigo, string descripcion, float peso,
        Categoria categoria, Cliente* cliente, Centro* centro);

    string getCodigo() const;
    string getDescripcion() const;
    float getPeso() const;
    Categoria getCategoria() const;
    EstadoPaquete getEstado() const;
    Cliente* getCliente() const;
    Bodega* getBodega() const;
    int getFila() const;
    int getColumna() const;

    void setEstado(EstadoPaquete nuevoEstado);
    void setUbicacion(Bodega* bodega, int fila, int columna);
    void mostrarDatos() const;
};

class NodoPaquete {
public:
    Paquete* dato;
    NodoPaquete* siguiente;

    NodoPaquete(Paquete* dato);
};

class ListaPaquete {
private:
    NodoPaquete* primero;

public:
    ListaPaquete();
    ~ListaPaquete();

    bool estaVacia();
    void insertarFinal(Paquete* paquete);
    Paquete* buscar(string codigo);
    void mostrar();
    bool eliminar(string codigo);
};

#endif
