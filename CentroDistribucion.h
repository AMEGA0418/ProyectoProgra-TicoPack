#pragma once
#include <string>
#include <iostream>
#include "ListaEnlazada.h"
#include "Fecha.h"
#include "Bodega.h"
#include "Cliente.h"
#include "Colaborador.h"
#include "Paquete.h"
#include "SolicitudEnvio.h"
#include "Despacho.h"


using namespace std;

class CentroDistribucion {
private:
	string codigo;
	string nombre;
	string provincia;
	string direccion;
	string telefono;
	ListaEnlazada<Bodega> bodegas;
	ListaEnlazada<Cliente> clientes;
	ListaEnlazada<Colaborador> colaboradores;
	ListaEnlazada<Paquete> paquetes;
	ListaEnlazada<SolicitudEnvio> solicitudes;
	ListaEnlazada<Despacho> despachos;

	// Busca el despacho (si existe) asociado a un paquete.
	Despacho* despachoDePaqueteInterno(const Paquete* paquete) const;
	// Libera la celda de la matriz (si existe) y limpia la ubicacion.
	void liberarUbicacionPaquete(Paquete* paquete);

public:
	CentroDistribucion(const string& codigo, const string& nombre);
	CentroDistribucion(const string& codigo, const string& nombre,
		const string& provincia, const string& direccion,
		const string& telefono);

	string getCodigo() const;
	string getNombre() const;
	string getProvincia() const;
	string getDireccion() const;
	string getTelefono() const;

	bool agregarBodega(Bodega* bodega);
	bool agregarCliente(Cliente* cliente);
	bool agregarColaborador(Colaborador* colaborador);
	bool agregarPaquete(Paquete* paquete);
	bool agregarSolicitud(SolicitudEnvio* solicitud);
	bool agregarDespacho(Despacho* despacho);
	bool eliminarBodega(const string& codigo);
	bool eliminarCliente(const string& identificacion);
	bool eliminarColaborador(const string& identificacion);
	bool eliminarPaquete(const string& codigo);

	Bodega* buscarBodega(const string& codigo) const;
	Cliente* buscarCliente(const string& identificacion) const;
	Colaborador* buscarColaborador(const string& identificacion) const;
	Paquete* buscarPaquete(const string& codigo) const;
	SolicitudEnvio* buscarSolicitud(const string& codigo) const;
	Despacho* buscarDespacho(const string& codigo) const;
	Despacho* buscarDespachoDePaquete(const Paquete* paquete) const;

	const ListaEnlazada<Bodega>& getBodegas() const;
	const ListaEnlazada<Cliente>& getClientes() const;
	const ListaEnlazada<Colaborador>& getColaboradores() const;
	const ListaEnlazada<Paquete>& getPaquetes() const;
	const ListaEnlazada<SolicitudEnvio>& getSolicitudes() const;
	const ListaEnlazada<Despacho>& getDespachos() const;

	// Bodega compatible con la categoria que tiene el mayor porcentaje de
	// espacio disponible y al menos una celda libre. nullptr si no existe.
	Bodega* recomendarBodega(int categoria) const;

	// Almacenamiento: usa la primera celda libre de la bodega indicada.
	bool almacenarPaquete(Paquete* paquete, Bodega* bodega,
		Colaborador* responsable, const Fecha& fecha);
	// Almacenamiento en una celda especifica.
	bool almacenarPaquete(Paquete* paquete, Bodega* bodega, int fila,
		int columna, Colaborador* responsable, const Fecha& fecha);

	bool reubicarPaquete(Paquete* paquete, Bodega* destino,
		int fila, int columna);

	bool aprobarSolicitud(SolicitudEnvio* solicitud,
		Colaborador* responsable, const Fecha& fecha);
	bool finalizarDespacho(Despacho* despacho, const Fecha& fecha,
		Colaborador* responsable);

	// Incidencias: se reportan desde Recibido, Almacenado o En transito.
	bool reportarIncidencia(Paquete* paquete, Colaborador* responsable,
		const Fecha& fecha);
	// Resuelve una incidencia devolviendo el paquete a Almacenado (si conserva
	// celda) o a En transito (si el despacho sigue En proceso). Si la
	// incidencia ocurrio en Recibido, debe usarse el almacenamiento normal.
	bool resolverIncidencia(Paquete* paquete, Colaborador* responsable,
		const Fecha& fecha);

	bool tieneDependencias() const;
	void mostrar() const;
};
