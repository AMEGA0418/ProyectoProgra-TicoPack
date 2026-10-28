#pragma once
#include <string>
#include "Fecha.h"
#include "EstadoDespacho.h"
#include "ListaEnlazada.h"
#include "Paquete.h"

using namespace std;

class Colaborador;

class Despacho {
private:
	string codigo;
	Colaborador* responsable;
	Fecha fechaCreacion;
	Fecha fechaFinalizacion;
	int estado;
	ListaEnlazada<Paquete> paquetes;

public:
	Despacho(const string& codigo, Colaborador* responsable,
		const Fecha& fechaCreacion);

	string getCodigo() const;
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
