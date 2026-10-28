#include "Reportes.h"
#include "EstadoPaquete.h"
#include <iostream>

using namespace std;

void Reportes::resumenCentro(const CentroDistribucion& centro) {
    cout << "Reporte del centro de distribucion" << endl;
    cout << "Codigo: " << centro.getCodigo() << endl;
    cout << "Nombre: " << centro.getNombre() << endl;
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
