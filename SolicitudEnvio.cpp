#include "SolicitudEnvio.h"

SolicitudEnvio::SolicitudEnvio(const string& codigo, Cliente* cliente,Paquete* paquete, const string& origen, 
const string& destino,int distancia, const Fecha& fechaSolicitud, double costo): fechaSolicitud(fechaSolicitud){

	this->codigo = codigo;
	this->cliente = cliente;
	this->paquete = paquete;
	this->responsable = nullptr;
	this->origen = origen;
	this->destino = destino;
	this->distancia = distancia;
	this->estado = EstadoSolicitud::PENDIENTE;
	this->costo = costo;
}

SolicitudEnvio::SolicitudEnvio(const string& codigo, Cliente* cliente,
	Paquete* paquete, Colaborador* responsable, const string& origen,
	const string& destino, int distancia, const Fecha& fechaSolicitud,
	double costo) : fechaSolicitud(fechaSolicitud) {
	this->codigo = codigo;
	this->cliente = cliente;
	this->paquete = paquete;
	this->responsable = responsable;
	this->origen = origen;
	this->destino = destino;
	this->distancia = distancia;
	this->estado = EstadoSolicitud::PENDIENTE;
	this->costo = costo;
}

string SolicitudEnvio::getCodigo() const { return codigo; }
Cliente* SolicitudEnvio::getCliente() const { return cliente; }
Paquete* SolicitudEnvio::getPaquete() const { return paquete; }
Colaborador* SolicitudEnvio::getResponsable() const { return responsable; }
string SolicitudEnvio::getOrigen() const { return origen; }
string SolicitudEnvio::getDestino() const { return destino; }
int SolicitudEnvio::getDistancia() const { return distancia; }
Fecha SolicitudEnvio::getFechaSolicitud() const { return fechaSolicitud; }
int SolicitudEnvio::getEstado() const { return estado; }
double SolicitudEnvio::getCosto() const { return costo; }

bool SolicitudEnvio::cambiarEstado(int nuevoEstado) {
	if (!EstadoSolicitud::esValido(nuevoEstado) || esFinal()) return false;
	if (nuevoEstado == EstadoSolicitud::PENDIENTE) return false;
	// La aprobacion requiere las validaciones de CentroDistribucion.
	if (nuevoEstado == EstadoSolicitud::APROBADA) return false;
	estado = nuevoEstado;
	return true;
}

bool SolicitudEnvio::aprobar() {
	if (estado != EstadoSolicitud::PENDIENTE) return false;
	estado = EstadoSolicitud::APROBADA;
	return true;
}

bool SolicitudEnvio::esFinal() const {
	return EstadoSolicitud::esFinal(estado);
}

void SolicitudEnvio::mostrar() const {
	cout << "Solicitud: " << codigo << endl;
	if (cliente != nullptr) {
		cout << "Cliente: " << cliente->getNombre()
			<< " (" << cliente->getIdentificacion() << ")" << endl;
	}
	if (paquete != nullptr) {
		cout << "Paquete: " << paquete->getCodigo() << endl;
	}
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Fecha de solicitud: " << fechaSolicitud.toString()
		<< " " << fechaSolicitud.horaToString() << endl;
	cout << "Estado: " << EstadoSolicitud::toString(estado) << endl;
	if (responsable != nullptr) {
		cout << "Responsable: " << responsable->getNombreCompleto() << endl;
	}
	cout << "Costo estimado: " << costo << endl;
}
