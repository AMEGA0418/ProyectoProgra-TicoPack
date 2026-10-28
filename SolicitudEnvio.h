#pragma once
#include <string>
#include "Fecha.h"
#include "EstadoSolicitud.h"

using namespace std;

class Cliente;
class Paquete;

class SolicitudEnvio {
private:
	string codigo;
	Cliente* cliente;
	Paquete* paquete;
	string origen;
	string destino;
	int distancia;
	Fecha fechaSolicitud;
	int estado;
	double costo;

public:
	SolicitudEnvio(const string& codigo, Cliente* cliente, Paquete* paquete,
		const string& origen, const string& destino, int distancia,
		const Fecha& fechaSolicitud, double costo);

	string getCodigo() const;
	Cliente* getCliente() const;
	Paquete* getPaquete() const;
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
