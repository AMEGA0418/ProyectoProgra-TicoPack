#pragma once
#include <string>
#include <iostream>
#include "Fecha.h"
#include "EstadoSolicitud.h"
#include "Cliente.h"
#include "Paquete.h"
#include "Colaborador.h"

using namespace std;

class SolicitudEnvio {
private:
	string codigo;
	Cliente* cliente;
	Paquete* paquete;
	Colaborador* responsable;
	string origen;
	string destino;
	int distancia;
	Fecha fechaSolicitud;
	int estado;
	double costo;

	// La aprobacion solo puede ejecutarse desde la operacion del centro,
	// que valida todas las reglas del negocio.
	friend class CentroDistribucion;
	bool aprobar();

public:
	SolicitudEnvio(const string& codigo, Cliente* cliente, Paquete* paquete,
		const string& origen, const string& destino, int distancia,
		const Fecha& fechaSolicitud, double costo);
	SolicitudEnvio(const string& codigo, Cliente* cliente, Paquete* paquete,
		Colaborador* responsable, const string& origen, const string& destino,
		int distancia, const Fecha& fechaSolicitud, double costo);

	string getCodigo() const;
	Cliente* getCliente() const;
	Paquete* getPaquete() const;
	Colaborador* getResponsable() const;
	string getOrigen() const;
	string getDestino() const;
	int getDistancia() const;
	Fecha getFechaSolicitud() const;
	int getEstado() const;
	double getCosto() const;

	bool cambiarEstado(int nuevoEstado);
	bool esFinal() const;
	void mostrar() const;
};
