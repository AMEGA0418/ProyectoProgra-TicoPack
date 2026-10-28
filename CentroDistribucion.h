#pragma once
#include <string>
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
	ListaEnlazada<Bodega> bodegas;
	ListaEnlazada<Cliente> clientes;
	ListaEnlazada<Colaborador> colaboradores;
	ListaEnlazada<Paquete> paquetes;
	ListaEnlazada<SolicitudEnvio> solicitudes;
	ListaEnlazada<Despacho> despachos;

public:
	CentroDistribucion(const string& codigo, const string& nombre);

	string getCodigo() const;
	string getNombre() const;

	bool agregarBodega(Bodega* bodega);
	bool agregarCliente(Cliente* cliente);
	bool agregarColaborador(Colaborador* colaborador);
	bool agregarPaquete(Paquete* paquete);
	bool agregarSolicitud(SolicitudEnvio* solicitud);
	bool agregarDespacho(Despacho* despacho);

	Bodega* buscarBodega(const string& codigo) const;
	Cliente* buscarCliente(const string& identificacion) const;
	Paquete* buscarPaquete(const string& codigo) const;
	SolicitudEnvio* buscarSolicitud(const string& codigo) const;
	Despacho* buscarDespacho(const string& codigo) const;

	const ListaEnlazada<Bodega>& getBodegas() const;
	const ListaEnlazada<Cliente>& getClientes() const;
	const ListaEnlazada<Colaborador>& getColaboradores() const;
	const ListaEnlazada<Paquete>& getPaquetes() const;
	const ListaEnlazada<SolicitudEnvio>& getSolicitudes() const;
	const ListaEnlazada<Despacho>& getDespachos() const;

	bool almacenarPaquete(Paquete* paquete, Bodega* bodega,
		Colaborador* responsable, const Fecha& fecha);
	bool aprobarSolicitud(SolicitudEnvio* solicitud);
	bool finalizarDespacho(Despacho* despacho, const Fecha& fecha,
		Colaborador* responsable);
	void mostrar() const;
};
