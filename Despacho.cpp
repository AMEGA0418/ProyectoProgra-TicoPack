#include "Despacho.h"

Despacho::Despacho(const string& codigo, Colaborador* responsable,
	const Fecha& fechaCreacion) : fechaCreacion(fechaCreacion),
	fechaFinalizacion(0, 0, 0) {
	this->codigo = codigo;
	this->solicitud = nullptr;
	this->cliente = nullptr;
	this->centroOrigen = "";
	this->destino = "";
	this->responsable = responsable;
	estado = EstadoDespacho::EN_PROCESO;
}

Despacho::Despacho(const string& codigo, SolicitudEnvio* solicitud,
	Colaborador* responsable, const Fecha& fechaCreacion) :
	fechaCreacion(fechaCreacion), fechaFinalizacion(0, 0, 0) {
	this->codigo = codigo;
	this->solicitud = solicitud;
	this->cliente = solicitud == nullptr ? nullptr : solicitud->getCliente();
	this->centroOrigen = solicitud == nullptr ? string("") : solicitud->getOrigen();
	this->destino = solicitud == nullptr ? string("") : solicitud->getDestino();
	this->responsable = responsable;
	estado = EstadoDespacho::EN_PROCESO;
}

Despacho::~Despacho() {
	// Los paquetes pertenecen a CentroDistribucion, no al despacho.
	paquetes.liberarNodosSinEliminarDatos();
}

string Despacho::getCodigo() const { return codigo; }
SolicitudEnvio* Despacho::getSolicitud() const { return solicitud; }
Colaborador* Despacho::getResponsable() const { return responsable; }
Fecha Despacho::getFechaCreacion() const { return fechaCreacion; }
Fecha Despacho::getFechaFinalizacion() const { return fechaFinalizacion; }
int Despacho::getEstado() const { return estado; }
const ListaEnlazada<Paquete>& Despacho::getPaquetes() const { return paquetes; }

Cliente* Despacho::getCliente() const {
	return cliente;
}

Paquete* Despacho::getPaquete() const {
	Nodo<Paquete>* primero = paquetes.getPrimero();
	return primero == nullptr ? nullptr : primero->getDato();
}

string Despacho::getCentroOrigen() const {
	return centroOrigen;
}

string Despacho::getDestino() const {
	return destino;
}

bool Despacho::agregarPaquete(Paquete* paquete) {
	if (paquete == nullptr || estado == EstadoDespacho::FINALIZADO) return false;
	if (!paquetes.estaVacia()) return false; // un despacho maneja un paquete
	if (contienePaquete(paquete)) return false;
	paquetes.insertarFinal(paquete);
	return true;
}

bool Despacho::contienePaquete(const Paquete* paquete) const {
	for (Nodo<Paquete>* nodo = paquetes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato() == paquete) return true;
	}
	return false;
}

bool Despacho::finalizar(const Fecha& fecha) {
	if (estado != EstadoDespacho::EN_PROCESO || !fecha.esValida()) return false;
	estado = EstadoDespacho::FINALIZADO;
	fechaFinalizacion = fecha;
	return true;
}

void Despacho::mostrar() const {
	cout << "Despacho: " << codigo << endl;
	cout << "Estado: " << EstadoDespacho::toString(estado) << endl;

	if (solicitud != nullptr) {
		cout << "Solicitud: " << solicitud->getCodigo()
			<< " (" << EstadoSolicitud::toString(solicitud->getEstado()) << ")"
			<< endl;
	}
	cout << "Centro de origen: " << centroOrigen << endl;
	cout << "Destino: " << destino << endl;
	if (cliente != nullptr) {
		cout << "Cliente: " << cliente->getNombre()
			<< " (" << cliente->getIdentificacion() << ")" << endl;
	}

	Paquete* paquete = getPaquete();
	cout << "Paquete: " << (paquete == nullptr ? "(sin paquete)" : paquete->getCodigo())
		<< endl;

	if (responsable != nullptr) {
		cout << "Responsable: " << responsable->getNombreCompleto()
			<< " (" << responsable->getIdentificacion() << ")" << endl;
	}

	cout << "Fecha de despacho: " << fechaCreacion.toString()
		<< " " << fechaCreacion.horaToString() << endl;

	if (estado == EstadoDespacho::FINALIZADO) {
		cout << "Fecha de finalizacion: " << fechaFinalizacion.toString()
			<< " " << fechaFinalizacion.horaToString() << endl;
	}
}
