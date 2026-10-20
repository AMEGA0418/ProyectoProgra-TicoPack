#pragma once
#ifndef LISTACLIENTE_H
#define LISTACLIENTE_H

#include <string>

using namespace std;

//CLASE PADRE: CLIENTE

class Cliente {
protected:
    string identificacion;
    string nombre;
    string telefono;
    string correo;

public:
    Cliente(string identificacion, string nombre,
        string telefono, string correo);

    virtual ~Cliente();

    string getIdentificacion() const;
    string getNombre() const;
    string getTelefono() const;
    string getCorreo() const;

    void setIdentificacion(string nuevaIdentificacion);
    void setNombre(string nuevoNombre);
    void setTelefono(string nuevoTelefono);
    void setCorreo(string nuevoCorreo);

    virtual void mostrarDatos() const;
};


//NODO DE LA LISTA

class NodoCliente {
public:
    Cliente* dato;
    NodoCliente* siguiente;

    NodoCliente(Cliente* dato);
};


//LISTA ENLAZADA DE CLIENTES

class ListaCliente {
private:
    NodoCliente* primero;

public:
    ListaCliente();
    ~ListaCliente();

    bool estaVacia();
    void insertarFinal(Cliente* nuevoCliente);
    Cliente* buscar(string identificacion);
    void mostrar();
};

#endif