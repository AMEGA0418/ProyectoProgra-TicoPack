#include "CentroDistribucion.h"
#include "Validador.h"

CentroDistribucion::CentroDistribucion(const string& codigo,
	const string& nombre) {
	this->codigo = codigo;
	this->nombre = nombre;
	this->provincia = "";
	this->direccion = "";
	this->telefono = "";
}

CentroDistribucion::CentroDistribucion(const string& codigo,
	const string& nombre, const string& provincia,
	const string& direccion, const string& telefono) {
	this->codigo = codigo;
	this->nombre = nombre;
	this->provincia = provincia;
	this->direccion = direccion;
	this->telefono = telefono;
}

string CentroDistribucion::getCodigo() const { return codigo; }
string CentroDistribucion::getNombre() const { return nombre; }
string CentroDistribucion::getProvincia() const { return provincia; }
string CentroDistribucion::getDireccion() const { return direccion; }
string CentroDistribucion::getTelefono() const { return telefono; }

bool CentroDistribucion::agregarBodega(Bodega* bodega) {
	if (bodega == nullptr || !Validador::textoValido(bodega->getCodigo()) ||
		!Validador::textoValido(bodega->getNombre()) ||
		!TipoBodega::esValido(bodega->getTipo()) ||
		!Bodega::esDistribucionValida(bodega->getFilas(), bodega->getColumnas()) ||
		buscarBodega(bodega->getCodigo()) != nullptr) {
		return false;
	}
	bodegas.insertarFinal(bodega);
	return true;
}

bool CentroDistribucion::agregarCliente(Cliente* cliente) {
	if (cliente == nullptr ||
		!Validador::textoValido(cliente->getIdentificacion()) ||
		!Validador::textoValido(cliente->getNombre()) ||
		buscarCliente(cliente->getIdentificacion()) != nullptr) {
		return false;
	}
	clientes.insertarFinal(cliente);
	return true;
}

bool CentroDistribucion::agregarColaborador(Colaborador* colaborador) {
	if (colaborador == nullptr ||
		!Validador::textoValido(colaborador->getIdentificacion()) ||
		!Validador::textoValido(colaborador->getNombreCompleto()) ||
		buscarColaborador(colaborador->getIdentificacion()) != nullptr) {
		return false;
	}
	colaboradores.insertarFinal(colaborador);
	return true;
}

bool CentroDistribucion::agregarPaquete(Paquete* paquete) {
	if (paquete == nullptr || paquete->getPropietario() == nullptr ||
		!Paquete::datosValidos(paquete->getCodigo(),
			paquete->getDescripcion(), paquete->getPeso()) ||
		!Categoria::esValida(paquete->getCategoria()) ||
		buscarCliente(paquete->getPropietario()->getIdentificacion()) !=
		paquete->getPropietario() ||
		buscarPaquete(paquete->getCodigo()) != nullptr) {
		return false;
	}

	if (paquete->getCodigoCentro().empty()) {
		paquete->asignarCentro(codigo);
	}
	else if (paquete->getCodigoCentro() != codigo) {
		return false;
	}

	paquetes.insertarFinal(paquete);
	return true;
}

bool CentroDistribucion::agregarSolicitud(SolicitudEnvio* solicitud) {
	if (solicitud == nullptr ||
		!Validador::textoValido(solicitud->getCodigo()) ||
		!Validador::textoValido(solicitud->getDestino()) ||
		!solicitud->getFechaSolicitud().esValida() ||
		solicitud->getCosto() < 0 ||
		buscarSolicitud(solicitud->getCodigo()) != nullptr ||
		solicitud->getOrigen() != codigo ||
		solicitud->getCliente() == nullptr || solicitud->getPaquete() == nullptr ||
		solicitud->getResponsable() == nullptr ||
		buscarCliente(solicitud->getCliente()->getIdentificacion()) !=
		solicitud->getCliente() ||
		buscarPaquete(solicitud->getPaquete()->getCodigo()) !=
		solicitud->getPaquete() ||
		buscarColaborador(solicitud->getResponsable()->getIdentificacion()) !=
		solicitud->getResponsable() ||
		solicitud->getCliente() != solicitud->getPaquete()->getPropietario() ||
		solicitud->getPaquete()->getEstado() != EstadoPaquete::ALMACENADO) {
		return false;
	}

	// Un paquete con despacho ya no admite nuevas solicitudes.
	if (despachoDePaqueteInterno(solicitud->getPaquete()) != nullptr) return false;

	for (Nodo<SolicitudEnvio>* nodo = solicitudes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getPaquete() == solicitud->getPaquete() &&
			nodo->getDato()->getEstado() == EstadoSolicitud::PENDIENTE) return false;
	}
	solicitudes.insertarFinal(solicitud);
	return true;
}

bool CentroDistribucion::agregarDespacho(Despacho* despacho) {
	if (despacho == nullptr || !Validador::textoValido(despacho->getCodigo()) ||
		despacho->getEstado() != EstadoDespacho::EN_PROCESO ||
		buscarDespacho(despacho->getCodigo()) != nullptr ||
		despacho->getSolicitud() == nullptr ||
		buscarSolicitud(despacho->getSolicitud()->getCodigo()) !=
		despacho->getSolicitud() ||
		despacho->getSolicitud()->getEstado() != EstadoSolicitud::APROBADA ||
		despacho->getPaquetes().getTamano() != 1) {
		return false;
	}

	for (Nodo<Paquete>* paquete = despacho->getPaquetes().getPrimero();
		paquete != nullptr; paquete = paquete->getSiguiente()) {
		Paquete* actual = paquete->getDato();
		if (actual == nullptr ||
			actual != despacho->getSolicitud()->getPaquete() ||
			buscarPaquete(actual->getCodigo()) != actual ||
			actual->getEstado() != EstadoPaquete::EN_TRANSITO) {
			return false;
		}
		for (Nodo<Despacho>* existente = despachos.getPrimero();
			existente != nullptr; existente = existente->getSiguiente()) {
			if (existente->getDato()->contienePaquete(actual)) return false;
		}
	}
	despachos.insertarFinal(despacho);
	return true;
}

bool CentroDistribucion::eliminarBodega(const string& codigoBuscado) {
	Bodega* bodega = buscarBodega(codigoBuscado);
	if (bodega == nullptr || bodega->celdasOcupadas() != 0) return false;

	// Verificacion adicional: ningun paquete debe referenciar la bodega.
	for (Nodo<Paquete>* nodo = paquetes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCodigoBodega() == codigoBuscado) return false;
	}
	return bodegas.eliminar(bodega);
}

bool CentroDistribucion::eliminarCliente(const string& identificacion) {
	Cliente* cliente = buscarCliente(identificacion);
	if (cliente == nullptr) return false;

	for (Nodo<Paquete>* nodo = paquetes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getPropietario() == cliente) return false;
	}
	for (Nodo<SolicitudEnvio>* nodo = solicitudes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCliente() == cliente) return false;
	}
	for (Nodo<Despacho>* nodo = despachos.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCliente() == cliente) return false;
	}
	return clientes.eliminar(cliente);
}

bool CentroDistribucion::eliminarColaborador(const string& identificacion) {
	Colaborador* colaborador = buscarColaborador(identificacion);
	if (colaborador == nullptr) return false;

	for (Nodo<SolicitudEnvio>* nodo = solicitudes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getResponsable() == colaborador) return false;
	}
	for (Nodo<Despacho>* nodo = despachos.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getResponsable() == colaborador) return false;
	}
	for (Nodo<Paquete>* nodo = paquetes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		for (Nodo<RegistroBitacora>* registro =
			nodo->getDato()->getBitacora().getPrimero(); registro != nullptr;
			registro = registro->getSiguiente()) {
			if (registro->getDato()->getResponsable() == colaborador) return false;
		}
	}
	return colaboradores.eliminar(colaborador);
}

bool CentroDistribucion::eliminarPaquete(const string& codigoBuscado) {
	Paquete* paquete = buscarPaquete(codigoBuscado);
	if (paquete == nullptr || paquete->getEstado() != EstadoPaquete::RECIBIDO ||
		paquete->tieneUbicacion()) return false;

	for (Nodo<SolicitudEnvio>* nodo = solicitudes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getPaquete() == paquete) return false;
	}
	for (Nodo<Despacho>* nodo = despachos.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->contienePaquete(paquete)) return false;
	}
	return paquetes.eliminar(paquete);
}

bool CentroDistribucion::tieneDependencias() const {
	return !bodegas.estaVacia() || !clientes.estaVacia() ||
		!colaboradores.estaVacia() || !paquetes.estaVacia() ||
		!solicitudes.estaVacia() || !despachos.estaVacia();
}

Bodega* CentroDistribucion::recomendarBodega(int categoria) const {
	Bodega* mejor = nullptr;
	for (Nodo<Bodega>* nodo = bodegas.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		Bodega* bodega = nodo->getDato();
		if (!bodega->esCompatible(categoria) || bodega->celdasLibres() <= 0) {
			continue;
		}
		if (mejor == nullptr ||
			bodega->porcentajeDisponible() > mejor->porcentajeDisponible()) {
			mejor = bodega;
		}
	}
	return mejor;
}

Despacho* CentroDistribucion::despachoDePaqueteInterno(const Paquete* paquete) const {
	if (paquete == nullptr) return nullptr;
	for (Nodo<Despacho>* nodo = despachos.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->contienePaquete(paquete)) {
			return nodo->getDato();
		}
	}
	return nullptr;
}

Despacho* CentroDistribucion::buscarDespachoDePaquete(const Paquete* paquete) const {
	return despachoDePaqueteInterno(paquete);
}

void CentroDistribucion::liberarUbicacionPaquete(Paquete* paquete) {
	if (paquete == nullptr || !paquete->tieneUbicacion()) return;

	Bodega* bodega = buscarBodega(paquete->getCodigoBodega());
	if (bodega != nullptr) {
		bodega->liberarCelda(paquete->getFila(), paquete->getColumna());
	}
	paquete->liberarUbicacion();
}

bool CentroDistribucion::reubicarPaquete(Paquete* paquete, Bodega* destino,
	int nuevaFila, int nuevaColumna) {
	if (paquete == nullptr || destino == nullptr ||
		buscarPaquete(paquete->getCodigo()) != paquete ||
		paquete->getCodigoCentro() != codigo ||
		paquete->getEstado() != EstadoPaquete::ALMACENADO ||
		!paquete->tieneUbicacion() ||
		buscarBodega(destino->getCodigo()) != destino ||
		!destino->esCompatible(paquete->getCategoria())) {
		return false;
	}

	Celda* nuevaCelda = destino->consultarCelda(nuevaFila, nuevaColumna);
	if (nuevaCelda == nullptr || !nuevaCelda->estaLibre()) return false;

	Bodega* origen = buscarBodega(paquete->getCodigoBodega());
	if (origen == nullptr) return false;

	Celda* celdaActual = origen->consultarCelda(paquete->getFila(),
		paquete->getColumna());
	if (celdaActual == nullptr || celdaActual->getPaquete() != paquete) {
		return false;
	}

	// No se libera la celda original hasta confirmar el destino.
	if (!destino->asignarPaquete(nuevaFila, nuevaColumna, paquete)) return false;
	if (!origen->liberarCelda(paquete->getFila(), paquete->getColumna())) {
		destino->liberarCelda(nuevaFila, nuevaColumna);
		return false;
	}

	paquete->asignarUbicacion(destino->getCodigo(), nuevaFila, nuevaColumna);
	return true;
}

Bodega* CentroDistribucion::buscarBodega(const string& codigoBuscado) const {
	for (Nodo<Bodega>* nodo = bodegas.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCodigo() == codigoBuscado) return nodo->getDato();
	}
	return nullptr;
}

Colaborador* CentroDistribucion::buscarColaborador(const string& identificacion) const {
	for (Nodo<Colaborador>* nodo = colaboradores.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getIdentificacion() == identificacion) return nodo->getDato();
	}
	return nullptr;
}

Cliente* CentroDistribucion::buscarCliente(const string& identificacion) const {
	for (Nodo<Cliente>* nodo = clientes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getIdentificacion() == identificacion) return nodo->getDato();
	}
	return nullptr;
}

Paquete* CentroDistribucion::buscarPaquete(const string& codigoBuscado) const {
	for (Nodo<Paquete>* nodo = paquetes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCodigo() == codigoBuscado) return nodo->getDato();
	}
	return nullptr;
}

SolicitudEnvio* CentroDistribucion::buscarSolicitud(const string& codigoBuscado) const {
	for (Nodo<SolicitudEnvio>* nodo = solicitudes.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCodigo() == codigoBuscado) return nodo->getDato();
	}
	return nullptr;
}

Despacho* CentroDistribucion::buscarDespacho(const string& codigoBuscado) const {
	for (Nodo<Despacho>* nodo = despachos.getPrimero(); nodo != nullptr;
		nodo = nodo->getSiguiente()) {
		if (nodo->getDato()->getCodigo() == codigoBuscado) return nodo->getDato();
	}
	return nullptr;
}

const ListaEnlazada<Bodega>& CentroDistribucion::getBodegas() const { return bodegas; }
const ListaEnlazada<Cliente>& CentroDistribucion::getClientes() const { return clientes; }
const ListaEnlazada<Colaborador>& CentroDistribucion::getColaboradores() const { return colaboradores; }
const ListaEnlazada<Paquete>& CentroDistribucion::getPaquetes() const { return paquetes; }
const ListaEnlazada<SolicitudEnvio>& CentroDistribucion::getSolicitudes() const { return solicitudes; }
const ListaEnlazada<Despacho>& CentroDistribucion::getDespachos() const { return despachos; }

bool CentroDistribucion::almacenarPaquete(Paquete* paquete, Bodega* bodega,
	Colaborador* responsable, const Fecha& fecha) {
	if (bodega == nullptr) return false;
	Celda* celda = bodega->primeraCeldaLibre();
	if (celda == nullptr) return false;
	return almacenarPaquete(paquete, bodega, celda->getFila(),
		celda->getColumna(), responsable, fecha);
}

bool CentroDistribucion::almacenarPaquete(Paquete* paquete, Bodega* bodega,
	int fila, int columna, Colaborador* responsable, const Fecha& fecha) {
	if (paquete == nullptr || bodega == nullptr || responsable == nullptr ||
		!fecha.esValida() ||
		buscarPaquete(paquete->getCodigo()) != paquete ||
		paquete->getCodigoCentro() != codigo ||
		buscarBodega(bodega->getCodigo()) != bodega ||
		buscarColaborador(responsable->getIdentificacion()) != responsable ||
		!bodega->esCompatible(paquete->getCategoria())) {
		return false;
	}

	bool puedeAlmacenarse = (paquete->getEstado() == EstadoPaquete::RECIBIDO);
	if (paquete->getEstado() == EstadoPaquete::INCIDENCIA &&
		!paquete->tieneUbicacion() &&
		paquete->getEstadoPreIncidencia() == EstadoPaquete::RECIBIDO) {
		puedeAlmacenarse = true;
	}
	if (!puedeAlmacenarse) return false;

	Celda* celda = bodega->consultarCelda(fila, columna);
	if (celda == nullptr || !celda->estaLibre()) return false;

	if (!bodega->asignarPaquete(fila, columna, paquete)) return false;
	if (!paquete->aplicarTransicion(EstadoPaquete::ALMACENADO, responsable,
		fecha)) {
		bodega->liberarCelda(fila, columna);
		return false;
	}

	paquete->asignarUbicacion(bodega->getCodigo(), fila, columna);
	return true;
}

bool CentroDistribucion::reportarIncidencia(Paquete* paquete,
	Colaborador* responsable, const Fecha& fecha) {
	if (paquete == nullptr || responsable == nullptr || !fecha.esValida() ||
		buscarPaquete(paquete->getCodigo()) != paquete ||
		paquete->getCodigoCentro() != codigo ||
		buscarColaborador(responsable->getIdentificacion()) != responsable) {
		return false;
	}

	int estado = paquete->getEstado();
	if (estado == EstadoPaquete::INCIDENCIA ||
		estado == EstadoPaquete::ENTREGADO) {
		return false;
	}

	// Si el paquete ya esta en transito debe existir un despacho En proceso.
	if (estado == EstadoPaquete::EN_TRANSITO) {
		Despacho* despacho = buscarDespachoDePaquete(paquete);
		if (despacho == nullptr ||
			despacho->getEstado() != EstadoDespacho::EN_PROCESO) {
			return false;
		}
	}
	else if (estado == EstadoPaquete::ALMACENADO) {
		// La celda debe seguir conteniendo al paquete durante la incidencia.
		if (!paquete->tieneUbicacion()) return false;
		Bodega* bodega = buscarBodega(paquete->getCodigoBodega());
		if (bodega == nullptr) return false;
		Celda* celda = bodega->consultarCelda(paquete->getFila(),
			paquete->getColumna());
		if (celda == nullptr || celda->getPaquete() != paquete) return false;
	}

	return paquete->cambiarEstado(EstadoPaquete::INCIDENCIA, responsable, fecha);
}

bool CentroDistribucion::resolverIncidencia(Paquete* paquete,
	Colaborador* responsable, const Fecha& fecha) {
	if (paquete == nullptr || responsable == nullptr || !fecha.esValida() ||
		buscarPaquete(paquete->getCodigo()) != paquete ||
		paquete->getCodigoCentro() != codigo ||
		buscarColaborador(responsable->getIdentificacion()) != responsable ||
		paquete->getEstado() != EstadoPaquete::INCIDENCIA) {
		return false;
	}

	int estadoPrevio = paquete->getEstadoPreIncidencia();

	if (estadoPrevio == EstadoPaquete::ALMACENADO) {
		if (!paquete->tieneUbicacion()) return false;
		Bodega* bodega = buscarBodega(paquete->getCodigoBodega());
		if (bodega == nullptr) return false;
		Celda* celda = bodega->consultarCelda(paquete->getFila(),
			paquete->getColumna());
		if (celda == nullptr || celda->getPaquete() != paquete) return false;
		return paquete->cambiarEstado(EstadoPaquete::ALMACENADO, responsable,
			fecha);
	}

	if (estadoPrevio == EstadoPaquete::EN_TRANSITO) {
		Despacho* despacho = buscarDespachoDePaquete(paquete);
		if (despacho == nullptr ||
			despacho->getEstado() != EstadoDespacho::EN_PROCESO) {
			return false;
		}
		return paquete->cambiarEstado(EstadoPaquete::EN_TRANSITO, responsable,
			fecha);
	}

	// Si la incidencia ocurrio en Recibido, debe almacenarse con la operacion
	// normal para pasar a Almacenado.
	return false;
}

bool CentroDistribucion::aprobarSolicitud(SolicitudEnvio* solicitud,
	Colaborador* responsable, const Fecha& fecha) {
	if (solicitud == nullptr || responsable == nullptr || !fecha.esValida() ||
		buscarSolicitud(solicitud->getCodigo()) != solicitud ||
		buscarColaborador(responsable->getIdentificacion()) != responsable ||
		solicitud->getEstado() != EstadoSolicitud::PENDIENTE ||
		solicitud->getOrigen() != codigo ||
		solicitud->getCliente() == nullptr || solicitud->getPaquete() == nullptr ||
		solicitud->getResponsable() == nullptr ||
		solicitud->getCliente() != solicitud->getPaquete()->getPropietario()) {
		return false;
	}

	Paquete* paquete = solicitud->getPaquete();
	if (buscarPaquete(paquete->getCodigo()) != paquete ||
		paquete->getCodigoCentro() != codigo ||
		paquete->getEstado() != EstadoPaquete::ALMACENADO ||
		!paquete->tieneUbicacion() ||
		despachoDePaqueteInterno(paquete) != nullptr) {
		return false;
	}

	// La celda actual debe existir y contener al paquete.
	Bodega* bodegaActual = buscarBodega(paquete->getCodigoBodega());
	if (bodegaActual == nullptr) return false;
	Celda* celdaActual = bodegaActual->consultarCelda(paquete->getFila(),
		paquete->getColumna());
	if (celdaActual == nullptr || celdaActual->getPaquete() != paquete) {
		return false;
	}

	string codigoDespacho = solicitud->getCodigo() + "-D";
	int consecutivo = 1;
	while (buscarDespacho(codigoDespacho) != nullptr) {
		codigoDespacho = solicitud->getCodigo() + "-D" +
			to_string(consecutivo++);
	}

	Despacho* despacho = new Despacho(codigoDespacho, solicitud, responsable,
		fecha);
	if (!despacho->agregarPaquete(paquete)) {
		delete despacho;
		return false;
	}

	if (!paquete->aplicarTransicion(EstadoPaquete::EN_TRANSITO, responsable,
		fecha)) {
		delete despacho;
		return false;
	}
	if (!solicitud->aprobar()) {
		delete despacho;
		return false;
	}
	if (!agregarDespacho(despacho)) {
		delete despacho;
		return false;
	}

	// El paquete en transito libera inmediatamente su celda.
	liberarUbicacionPaquete(paquete);
	return true;
}

bool CentroDistribucion::finalizarDespacho(Despacho* despacho,
	const Fecha& fecha, Colaborador* responsable) {
	if (despacho == nullptr || responsable == nullptr || !fecha.esValida() ||
		buscarDespacho(despacho->getCodigo()) != despacho ||
		buscarColaborador(responsable->getIdentificacion()) != responsable ||
		despacho->getEstado() != EstadoDespacho::EN_PROCESO ||
		despacho->getSolicitud() == nullptr ||
		despacho->getSolicitud()->getEstado() != EstadoSolicitud::APROBADA ||
		despacho->getSolicitud()->getPaquete() != despacho->getPaquete() ||
		despacho->getPaquetes().estaVacia()) {
		return false;
	}

	// Validar todo antes de aplicar cambios para no dejar datos a medias.
	for (Nodo<Paquete>* nodo = despacho->getPaquetes().getPrimero();
		nodo != nullptr; nodo = nodo->getSiguiente()) {
		Paquete* paquete = nodo->getDato();
		if (paquete == nullptr ||
			paquete->getCodigoCentro() != codigo ||
			buscarPaquete(paquete->getCodigo()) != paquete ||
			paquete->getEstado() != EstadoPaquete::EN_TRANSITO) {
			return false;
		}
	}

	for (Nodo<Paquete>* nodo = despacho->getPaquetes().getPrimero();
		nodo != nullptr; nodo = nodo->getSiguiente()) {
		Paquete* paquete = nodo->getDato();
		if (!paquete->aplicarTransicion(EstadoPaquete::ENTREGADO,
			responsable, fecha)) {
			return false;
		}
		liberarUbicacionPaquete(paquete);
	}

	return despacho->finalizar(fecha);
}

void CentroDistribucion::mostrar() const {
	cout << "Centro de distribucion: " << codigo << " - " << nombre << endl;
	cout << "Provincia: " << provincia << endl;
	cout << "Direccion: " << direccion << endl;
	cout << "Telefono: " << telefono << endl;
	cout << "Bodegas: " << bodegas.getTamano() << endl;
	cout << "Clientes: " << clientes.getTamano() << endl;
	cout << "Colaboradores: " << colaboradores.getTamano() << endl;
	cout << "Paquetes: " << paquetes.getTamano() << endl;
	cout << "Solicitudes: " << solicitudes.getTamano() << endl;
	cout << "Despachos: " << despachos.getTamano() << endl;
}
