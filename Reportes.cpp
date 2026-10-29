#include "Reportes.h"

// Texto con 2 decimales, ej. 33.33%
static string textoPorcentaje(double valor) {
    long v = (long)(valor * 100 + 0.5);
    long decimales = v % 100;
    return to_string(v / 100) + "." + (decimales < 10 ? "0" : "") +
        to_string(decimales) + "%";
}

void Reportes::resumenCentro(const CentroDistribucion& centro) {
    cout << "Reporte del centro de distribucion" << endl;
    cout << "Codigo: " << centro.getCodigo() << endl;
    cout << "Nombre: " << centro.getNombre() << endl;
    cout << "Provincia: " << centro.getProvincia() << endl;
    cout << "Direccion: " << centro.getDireccion() << endl;
    cout << "Telefono: " << centro.getTelefono() << endl;
    cout << "Bodegas: " << centro.getBodegas().getTamano() << endl;
    cout << "Clientes: " << centro.getClientes().getTamano() << endl;
    cout << "Colaboradores: " << centro.getColaboradores().getTamano() << endl;
    cout << "Paquetes: " << centro.getPaquetes().getTamano() << endl;
    cout << "Solicitudes: " << centro.getSolicitudes().getTamano() << endl;
    cout << "Despachos: " << centro.getDespachos().getTamano() << endl;
}

void Reportes::estadoPaquetes(const CentroDistribucion& centro) {
    int recibidos = 0;
    int almacenados = 0;
    int enTransito = 0;
    int entregados = 0;
    int incidencias = 0;

    for (Nodo<Paquete>* nodo = centro.getPaquetes().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        int estado = nodo->getDato()->getEstado();
        if (estado == EstadoPaquete::RECIBIDO) recibidos++;
        else if (estado == EstadoPaquete::ALMACENADO) almacenados++;
        else if (estado == EstadoPaquete::EN_TRANSITO) enTransito++;
        else if (estado == EstadoPaquete::ENTREGADO) entregados++;
        else if (estado == EstadoPaquete::INCIDENCIA) incidencias++;
    }

    cout << "Reporte de estados de paquetes" << endl;
    cout << "Recibidos: " << recibidos << endl;
    cout << "Almacenados: " << almacenados << endl;
    cout << "En transito: " << enTransito << endl;
    cout << "Entregados: " << entregados << endl;
    cout << "Con incidencia: " << incidencias << endl;
}

void Reportes::ocupacionBodegas(const CentroDistribucion& centro) {
    cout << "Reporte de ocupacion de bodegas del centro "
        << centro.getCodigo() << " - " << centro.getNombre() << endl;

    if (centro.getBodegas().estaVacia()) {
        cout << "El centro no tiene bodegas registradas." << endl;
        return;
    }

    for (Nodo<Bodega>* nodo = centro.getBodegas().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Bodega* bodega = nodo->getDato();
        cout << "Bodega " << bodega->getCodigo() << " - "
            << bodega->getNombre() << " ("
            << TipoBodega::toString(bodega->getTipo()) << ")" << endl;
        cout << "  Total de celdas: " << bodega->totalCeldas() << endl;
        cout << "  Celdas ocupadas: " << bodega->celdasOcupadas() << endl;
        cout << "  Celdas disponibles: " << bodega->celdasLibres() << endl;
        cout << "  Porcentaje de ocupacion: "
            << textoPorcentaje(bodega->porcentajeOcupacion()) << endl;
        cout << "-----------------------------------" << endl;
    }
}

void Reportes::historialCliente(const CentroDistribucion& centro,
    Cliente* cliente) {
    if (cliente == nullptr) return;

    cout << "Historial del cliente " << cliente->getNombre()
        << " (" << cliente->getIdentificacion() << ")" << endl;
    cout << "Centro: " << centro.getCodigo() << " - "
        << centro.getNombre() << endl;

    bool encontrado = false;

    cout << "\nSolicitudes de envio:" << endl;
    for (Nodo<SolicitudEnvio>* nodo = centro.getSolicitudes().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        SolicitudEnvio* solicitud = nodo->getDato();
        if (solicitud->getCliente() == cliente) {
            encontrado = true;
            cout << "  Codigo: " << solicitud->getCodigo()
                << " | Paquete: "
                << (solicitud->getPaquete() == nullptr ? "(sin paquete)" :
                    solicitud->getPaquete()->getCodigo())
                << " | Fecha: " << solicitud->getFechaSolicitud().toString()
                << " " << solicitud->getFechaSolicitud().horaToString()
                << " | Estado: "
                << EstadoSolicitud::toString(solicitud->getEstado()) << endl;
        }
    }

    cout << "\nDespachos:" << endl;
    for (Nodo<Despacho>* nodo = centro.getDespachos().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Despacho* despacho = nodo->getDato();
        if (despacho->getCliente() == cliente) {
            encontrado = true;
            Paquete* paquete = despacho->getPaquete();
            cout << "  Codigo: " << despacho->getCodigo()
                << " | Paquete: "
                << (paquete == nullptr ? "(sin paquete)" : paquete->getCodigo())
                << " | Fecha: " << despacho->getFechaCreacion().toString()
                << " " << despacho->getFechaCreacion().horaToString()
                << " | Estado: "
                << EstadoDespacho::toString(despacho->getEstado()) << endl;
        }
    }

    if (!encontrado) {
        cout << "\nEl cliente no tiene solicitudes ni despachos registrados."
            << endl;
    }
}

void Reportes::clientesPorEnvios(const CentroDistribucion& centro) {
    int cantidad = centro.getClientes().getTamano();
    if (cantidad <= 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente** orden = new Cliente * [cantidad];
    int* conteos = new int[cantidad];
    int indice = 0;

    for (Nodo<Cliente>* nodo = centro.getClientes().getPrimero();
        nodo != nullptr && indice < cantidad; nodo = nodo->getSiguiente()) {
        orden[indice] = nodo->getDato();
        conteos[indice] = 0;
        indice++;
    }

    // Contar despachos Finalizados por cliente.
    for (Nodo<Despacho>* d = centro.getDespachos().getPrimero();
        d != nullptr; d = d->getSiguiente()) {
        if (d->getDato()->getEstado() != EstadoDespacho::FINALIZADO) continue;
        Cliente* cliente = d->getDato()->getCliente();
        for (int i = 0; i < cantidad; i++) {
            if (orden[i] == cliente) {
                conteos[i]++;
                break;
            }
        }
    }

    // Ordenamiento por insercion, de mayor a menor. Solo se mueve un elemento
    // cuando su conteo es estrictamente mayor, por lo que los empates
    // conservan el orden original de la lista de clientes.
    for (int i = 1; i < cantidad; i++) {
        Cliente* clienteActual = orden[i];
        int conteoActual = conteos[i];
        int j = i - 1;
        while (j >= 0 && conteos[j] < conteoActual) {
            orden[j + 1] = orden[j];
            conteos[j + 1] = conteos[j];
            j--;
        }
        orden[j + 1] = clienteActual;
        conteos[j + 1] = conteoActual;
    }

    cout << "Clientes por cantidad de despachos finalizados" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << orden[i]->getNombre() << " (" << orden[i]->getIdentificacion()
            << "): " << conteos[i] << " despachos finalizados" << endl;
    }

    delete[] conteos;
    delete[] orden;
}

void Reportes::bitacoraPaquete(Paquete* paquete) {
    if (paquete == nullptr) return;
    paquete->mostrarBitacora();
}

void Reportes::despachoDePaquete(const CentroDistribucion& centro,
    Paquete* paquete) {
    if (paquete == nullptr) return;

    cout << "Consulta de despacho del paquete " << paquete->getCodigo() << endl;

    SolicitudEnvio* solicitudAprobada = nullptr;
    for (Nodo<SolicitudEnvio>* nodo = centro.getSolicitudes().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        SolicitudEnvio* solicitud = nodo->getDato();
        if (solicitud->getPaquete() == paquete &&
            solicitud->getEstado() == EstadoSolicitud::APROBADA) {
            solicitudAprobada = solicitud;
            break;
        }
    }

    if (solicitudAprobada != nullptr) {
        cout << "Solicitud aprobada: " << solicitudAprobada->getCodigo()
            << " | Fecha: "
            << solicitudAprobada->getFechaSolicitud().toString()
            << " | Estado: "
            << EstadoSolicitud::toString(solicitudAprobada->getEstado())
            << endl;
    }
    else {
        cout << "El paquete no tiene una solicitud aprobada." << endl;
    }

    Despacho* despacho = centro.buscarDespachoDePaquete(paquete);
    if (despacho == nullptr) {
        cout << "El paquete no tiene despacho asociado." << endl;
        return;
    }

    cout << "Despacho: " << despacho->getCodigo()
        << " | Fecha: " << despacho->getFechaCreacion().toString()
        << " " << despacho->getFechaCreacion().horaToString()
        << " | Estado: " << EstadoDespacho::toString(despacho->getEstado())
        << endl;
}

void Reportes::despachosPorColaborador(const CentroDistribucion& centro,
    Colaborador* colaborador) {
    if (colaborador == nullptr) return;

    cout << "Despachos gestionados por " << colaborador->getNombreCompleto()
        << " (" << colaborador->getIdentificacion() << ")" << endl;

    bool encontrado = false;
    for (Nodo<Despacho>* nodo = centro.getDespachos().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Despacho* despacho = nodo->getDato();
        if (despacho->getResponsable() == colaborador) {
            encontrado = true;
            Paquete* paquete = despacho->getPaquete();
            cout << "  Codigo: " << despacho->getCodigo()
                << " | Paquete: "
                << (paquete == nullptr ? "(sin paquete)" : paquete->getCodigo())
                << " | Fecha: " << despacho->getFechaCreacion().toString()
                << " " << despacho->getFechaCreacion().horaToString()
                << " | Estado: "
                << EstadoDespacho::toString(despacho->getEstado()) << endl;
        }
    }

    if (!encontrado) {
        cout << "El colaborador no tiene despachos registrados." << endl;
    }
}
