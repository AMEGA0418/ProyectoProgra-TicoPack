#include "Reportes.h"

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
    cout << "Reporte de ocupacion de bodegas" << endl;
    for (Nodo<Bodega>* nodo = centro.getBodegas().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Bodega* bodega = nodo->getDato();
        cout << bodega->getCodigo() << " - " << bodega->getNombre()
            << ": " << bodega->porcentajeOcupacion() << "% ocupado, "
            << bodega->celdasLibres() << " celdas libres" << endl;
    }
}

void Reportes::historialCliente(const CentroDistribucion& centro,
    Cliente* cliente) {
    if (cliente == nullptr) return;

    cout << "Historial de " << cliente->getNombre() << endl;
    for (Nodo<SolicitudEnvio>* nodo = centro.getSolicitudes().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        SolicitudEnvio* solicitud = nodo->getDato();
        if (solicitud->getCliente() == cliente) {
            cout << "Solicitud " << solicitud->getCodigo()
                << ", paquete " << solicitud->getPaquete()->getCodigo()
                << ", fecha " << solicitud->getFechaSolicitud().toString()
                << ", estado " << EstadoSolicitud::toString(solicitud->getEstado())
                << endl;
        }
    }
    for (Nodo<Despacho>* nodo = centro.getDespachos().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Despacho* despacho = nodo->getDato();
        if (despacho->getSolicitud() != nullptr &&
            despacho->getSolicitud()->getCliente() == cliente) {
            cout << "Despacho " << despacho->getCodigo()
                << ", fecha " << despacho->getFechaCreacion().toString()
                << ", estado " << EstadoDespacho::toString(despacho->getEstado())
                << endl;
        }
    }
}

void Reportes::clientesPorEnvios(const CentroDistribucion& centro) {
    int cantidad = centro.getClientes().getTamano();
    if (cantidad == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente** orden = new Cliente * [cantidad];
    int indice = 0;
    for (Nodo<Cliente>* nodo = centro.getClientes().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        orden[indice++] = nodo->getDato();
    }

    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            int actual = 0;
            int siguiente = 0;
            for (Nodo<Despacho>* d = centro.getDespachos().getPrimero();
                d != nullptr; d = d->getSiguiente()) {
                if (d->getDato()->getEstado() == EstadoDespacho::FINALIZADO &&
                    d->getDato()->getSolicitud() != nullptr) {
                    Cliente* cliente = d->getDato()->getSolicitud()->getCliente();
                    if (cliente == orden[j]) actual++;
                    if (cliente == orden[j + 1]) siguiente++;
                }
            }
            if (actual < siguiente) {
                Cliente* temporal = orden[j];
                orden[j] = orden[j + 1];
                orden[j + 1] = temporal;
            }
        }
    }

    for (int i = 0; i < cantidad; i++) {
        int finalizados = 0;
        for (Nodo<Despacho>* d = centro.getDespachos().getPrimero();
            d != nullptr; d = d->getSiguiente()) {
            if (d->getDato()->getEstado() == EstadoDespacho::FINALIZADO &&
                d->getDato()->getSolicitud() != nullptr &&
                d->getDato()->getSolicitud()->getCliente() == orden[i]) {
                finalizados++;
            }
        }
        cout << orden[i]->getNombre() << ": " << finalizados
            << " despachos finalizados" << endl;
    }
    delete[] orden;
}

void Reportes::bitacoraPaquete(Paquete* paquete) {
    if (paquete == nullptr) return;
    paquete->mostrarBitacora();
}

void Reportes::despachoDePaquete(const CentroDistribucion& centro,
    Paquete* paquete) {
    if (paquete == nullptr) return;
    for (Nodo<Despacho>* nodo = centro.getDespachos().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        if (nodo->getDato()->contienePaquete(paquete)) {
            cout << "Despacho: " << nodo->getDato()->getCodigo() << endl;
            cout << "Fecha: " << nodo->getDato()->getFechaCreacion().toString() << endl;
            cout << "Estado: " << EstadoDespacho::toString(
                nodo->getDato()->getEstado()) << endl;
            return;
        }
    }
    cout << "El paquete no tiene despacho asociado." << endl;
}

void Reportes::despachosPorColaborador(const CentroDistribucion& centro,
    Colaborador* colaborador) {
    if (colaborador == nullptr) return;
    for (Nodo<Despacho>* nodo = centro.getDespachos().getPrimero();
        nodo != nullptr; nodo = nodo->getSiguiente()) {
        Despacho* despacho = nodo->getDato();
        if (despacho->getResponsable() == colaborador) {
            cout << "Despacho: " << despacho->getCodigo()
                << ", fecha " << despacho->getFechaCreacion().toString()
                << ", estado " << EstadoDespacho::toString(despacho->getEstado())
                << endl;
        }
    }
}
