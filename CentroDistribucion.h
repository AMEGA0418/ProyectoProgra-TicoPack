#pragma once
#ifndef CENTRODISTRIBUCION_H
#define CENTRODISTRIBUCION_H

#include <string>
#include "ListaEnlazada.h"
#include "Cliente.h"
#include "Colaborador.h"
#include "Bodega.h"
#include "Paquete.h"
#include "SolicitudEnvio.h"
#include "Despacho.h"

class CentroDistribucion {
private:
    std::string codigo;
    std::string nombre;
    std::string provincia;
    std::string direccion;
    std::string telefono;

    ListaEnlazada<Cliente> clientes;
    ListaEnlazada<Colaborador> colaboradores;
    ListaEnlazada<Paquete> paquetes;
    ListaEnlazada<SolicitudEnvio> solicitudes;
    ListaEnlazada<Bodega> bodegas;
    ListaEnlazada<Despacho> despachos;

    static int contadorDespachos;      // para generar codigos DSP-001, ...
    std::string generarCodigoDespacho();

public:
    CentroDistribucion(std::string cod, std::string nom, std::string prov,
        std::string dir, std::string tel);

    std::string getCodigo() const { return codigo; }
    std::string getNombre() const { return nombre; }
    std::string getProvincia() const { return provincia; }
    std::string getDireccion() const { return direccion; }
    std::string getTelefono() const { return telefono; }

    // Acceso a las listas (lo necesita Reportes y SistemaTicoPack)
    ListaEnlazada<Cliente>& getClientes() { return clientes; }
    ListaEnlazada<Colaborador>& getColaboradores() { return colaboradores; }
    ListaEnlazada<Paquete>& getPaquetes() { return paquetes; }
    ListaEnlazada<SolicitudEnvio>& getSolicitudes() { return solicitudes; }
    ListaEnlazada<Bodega>& getBodegas() { return bodegas; }
    ListaEnlazada<Despacho>& getDespachos() { return despachos; }

    bool registrarCliente(Cliente* c);
    Cliente* buscarCliente(std::string id);
    bool eliminarCliente(std::string id);

    bool registrarColaborador(Colaborador* c);
    Colaborador* buscarColaborador(std::string id);
    bool eliminarColaborador(std::string id);

    bool registrarBodega(Bodega* b);
    Bodega* buscarBodega(std::string cod);
    bool eliminarBodega(std::string cod);

    bool registrarPaquete(Paquete* p);
    Paquete* buscarPaquete(std::string cod);
    bool eliminarPaquete(std::string cod);

    SolicitudEnvio* buscarSolicitud(std::string cod);
    Despacho* buscarDespacho(std::string cod);

    bool crearSolicitud(SolicitudEnvio* s);
    bool aprobarSolicitud(std::string cod, Colaborador* c);
    bool finalizarDespacho(std::string cod);

    Bodega* recomendarBodega(Paquete* p);
    bool almacenarPaquete(Paquete* p, Bodega* b, int f, int c, Colaborador* r);
    bool reubicarPaquete(Paquete* p, Bodega* b, int f, int c, Colaborador* r);

    void clientesPorEnvios();
};

#endif
