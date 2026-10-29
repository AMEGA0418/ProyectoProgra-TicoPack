#pragma once
#include <string>
#include <iostream>
#include "Fecha.h"
#include "EstadoDespacho.h"
#include "ListaEnlazada.h"
#include "Paquete.h"
#include "Colaborador.h"
#include "SolicitudEnvio.h"

using namespace std;

class Despacho {
private:
	string codigo;
	SolicitudEnvio* solicitud;
	Colaborador* responsable;
	Fecha fechaCreacion;
	Fecha fechaFinalizacion;
	int estado;
	ListaEnlazada<Paquete> paquetes;

public:
	Despacho(const string& codigo, Colaborador* responsable,
		const Fecha& fechaCreacion);
	Despacho(const string& codigo, SolicitudEnvio* solicitud,
		Colaborador* responsable, const Fecha& fechaCreacion);
	~Despacho();

	string getCodigo() const;
	SolicitudEnvio* getSolicitud() const;
	Colaborador* getResponsable() const;
	Fecha getFechaCreacion() const;
	Fecha getFechaFinalizacion() const;
	int getEstado() const;
	const ListaEnlazada<Paquete>& getPaquetes() const;

	bool agregarPaquete(Paquete* paquete);
	bool contienePaquete(Paquete* paquete) const;
	bool finalizar(const Fecha& fecha);
	void mostrar() const;
};
