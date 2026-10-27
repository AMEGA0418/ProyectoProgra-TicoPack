#include "CentroDistribucion.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int CentroDistribucion::contadorDespachos = 0;

CentroDistribucion::CentroDistribucion(string cod, string nom, string prov,
    string dir, string tel)
    : codigo(cod), nombre(nom), provincia(prov), direccion(dir), telefono(tel) {}

string CentroDistribucion::generarCodigoDespacho() {
    ostringstream ss;
    ss << "DSP-" << setw(3) << setfill('0') << ++contadorDespachos;
    return ss.str();
}

// ---------------- Clientes ----------------
Cliente* CentroDistribucion::buscarCliente(string id) {
    Nodo<Cliente>* n = clientes.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getIdentificacion() == id) return n->getDato();
        n = n->getSiguiente();
    }
    return nullptr;
}

bool CentroDistribucion::registrarCliente(Cliente* c) {
    if (c == nullptr || buscarCliente(c->getIdentificacion()) != nullptr) return false;
    clientes.insertarFinal(c);
    return true;
}
bool CentroDistribucion::eliminarCliente(string id) {
    Cliente* c = buscarCliente(id);
    if (c == nullptr) return false;
    // No se elimina si tiene paquetes registrados en este centro
    Nodo<Paquete>* n = paquetes.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getPropietario() == c) return false;
        n = n->getSiguiente();
    }
    return clientes.eliminar(c);
}

// ---------------- Colaboradores ----------------
Colaborador* CentroDistribucion::buscarColaborador(string id) {
    Nodo<Colaborador>* n = colaboradores.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getIdentificacion() == id) return n->getDato();
        n = n->getSiguiente();
    }
    return nullptr;
}

bool CentroDistribucion::registrarColaborador(Colaborador* c) {
    if (c == nullptr || buscarColaborador(c->getIdentificacion()) != nullptr) return false;
    colaboradores.insertarFinal(c);
    return true;
}

bool CentroDistribucion::eliminarColaborador(string id) {
    Colaborador* c = buscarColaborador(id);
    if (c == nullptr) return false;
    return colaboradores.eliminar(c);
}
// ---------------- Bodegas ----------------
Bodega* CentroDistribucion::buscarBodega(string cod) {
    Nodo<Bodega>* n = bodegas.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getCodigo() == cod) return n->getDato();
        n = n->getSiguiente();
    }
    return nullptr;
}

bool CentroDistribucion::registrarBodega(Bodega* b) {
    if (b == nullptr || buscarBodega(b->getCodigo()) != nullptr) return false;
    bodegas.insertarFinal(b);
    return true;
}

bool CentroDistribucion::eliminarBodega(string cod) {
    Bodega* b = buscarBodega(cod);
    if (b == nullptr) return false;
    if (b->celdasOcupadas() > 0) return false; // solo si esta vacia
    return bodegas.eliminar(b);
}

// ---------------- Paquetes ----------------
Paquete* CentroDistribucion::buscarPaquete(string cod) {
    Nodo<Paquete>* n = paquetes.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getCodigo() == cod) return n->getDato();
        n = n->getSiguiente();
    }
    return nullptr;
}

bool CentroDistribucion::registrarPaquete(Paquete* p) {
    if (p == nullptr || buscarPaquete(p->getCodigo()) != nullptr) return false;
    paquetes.insertarFinal(p);
    return true;
}
bool CentroDistribucion::eliminarPaquete(string cod) {
    Paquete* p = buscarPaquete(cod);
    if (p == nullptr) return false;
    if (p->tieneUbicacion()) return false; // primero debe liberarse la celda
    // No se elimina si esta en una solicitud pendiente/aprobada
    Nodo<SolicitudEnvio>* n = solicitudes.getPrimero();
    while (n != nullptr) {
        SolicitudEnvio* s = n->getDato();
        if (s->getPaquete() == p && (s->getEstado() == PENDIENTE || s->getEstado() == APROBADA))
            return false;
        n = n->getSiguiente();
    }
    return paquetes.eliminar(p);
}

// ---------------- Solicitudes y despachos ----------------
SolicitudEnvio* CentroDistribucion::buscarSolicitud(string cod) {
    Nodo<SolicitudEnvio>* n = solicitudes.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getCodigo() == cod) return n->getDato();
        n = n->getSiguiente();
    }
    return nullptr;
}
Despacho* CentroDistribucion::buscarDespacho(string cod) {
    Nodo<Despacho>* n = despachos.getPrimero();
    while (n != nullptr) {
        if (n->getDato()->getCodigo() == cod) return n->getDato();
        n = n->getSiguiente();
    }
    return nullptr;
}

bool CentroDistribucion::crearSolicitud(SolicitudEnvio* s) {
    if (s == nullptr || buscarSolicitud(s->getCodigo()) != nullptr) return false;
    Paquete* p = s->getPaquete();
    // El paquete y el cliente deben pertenecer a este centro
    if (p == nullptr || buscarPaquete(p->getCodigo()) != p) return false;
    if (s->getCliente() == nullptr || buscarCliente(s->getCliente()->getIdentificacion()) == nullptr)
        return false;
    // El paquete debe estar almacenado y ser del cliente
    if (p->getEstado() != ALMACENADO) return false;
    if (p->getPropietario() != s->getCliente()) return false;
    // No puede haber otra solicitud activa para el mismo paquete
    Nodo<SolicitudEnvio>* n = solicitudes.getPrimero();
    while (n != nullptr) {
        SolicitudEnvio* o = n->getDato();
        if (o->getPaquete() == p && (o->getEstado() == PENDIENTE || o->getEstado() == APROBADA))
            return false;
        n = n->getSiguiente();
    }
    solicitudes.insertarFinal(s);
    return true;
}

bool CentroDistribucion::aprobarSolicitud(string cod, Colaborador* c) {
    SolicitudEnvio* s = buscarSolicitud(cod);
    if (s == nullptr || c == nullptr) return false;
    if (s->getEstado() != PENDIENTE) return false;
    Paquete* p = s->getPaquete();
    if (!p->esTransicionValida(EN_TRANSITO)) return false;

    // Todo validado: ahora se modifica el estado
    s->aprobar();
    s->setResponsable(c);

    if (p->tieneUbicacion()) {
        Bodega* b = p->getBodega();
        b->liberarCelda(p->getFila(), p->getColumna());
        p->liberarUbicacion();
    }
    p->cambiarEstado(EN_TRANSITO, c);

    Despacho* d = new Despacho(generarCodigoDespacho(), s);
    despachos.insertarFinal(d);
    return true;
}

bool CentroDistribucion::finalizarDespacho(string cod) {
    Despacho* d = buscarDespacho(cod);
    if (d == nullptr) return false;
    return d->finalizar();
}
// ---------------- Almacenamiento ----------------
Bodega* CentroDistribucion::recomendarBodega(Paquete* p) {
    if (p == nullptr) return nullptr;
    Bodega* mejor = nullptr;
    Nodo<Bodega>* n = bodegas.getPrimero();
    while (n != nullptr) {
        Bodega* b = n->getDato();
        if (b->esCompatible(p->getCategoria()) && b->celdasLibres() > 0) {
            if (mejor == nullptr || b->celdasLibres() > mejor->celdasLibres())
                mejor = b; // la bodega compatible con mas espacio libre
        }
        n = n->getSiguiente();
    }
    return mejor;
}

bool CentroDistribucion::almacenarPaquete(Paquete* p, Bodega* b, int f, int c, Colaborador* r) {
    if (p == nullptr || b == nullptr || r == nullptr) return false;
    if (buscarPaquete(p->getCodigo()) != p || buscarBodega(b->getCodigo()) != b) return false;
    if (p->tieneUbicacion()) return false;
    if (!p->esTransicionValida(ALMACENADO)) return false;
    if (!b->esCompatible(p->getCategoria())) return false;
    if (!b->posicionValida(f, c)) return false;

    if (!b->asignarPaquete(f, c, p)) return false; // falla si la celda esta ocupada
    p->asignarUbicacion(b, f, c);
    if (!p->cambiarEstado(ALMACENADO, r)) {        // rollback
        p->liberarUbicacion();
        b->liberarCelda(f, c);
        return false;
    }
    return true;
}
bool CentroDistribucion::reubicarPaquete(Paquete* p, Bodega* b, int f, int c, Colaborador* r) {
    if (p == nullptr || b == nullptr || r == nullptr) return false;
    if (buscarPaquete(p->getCodigo()) != p || buscarBodega(b->getCodigo()) != b) return false;
    if (p->getEstado() != ALMACENADO || !p->tieneUbicacion()) return false;
    if (!b->esCompatible(p->getCategoria())) return false;
    if (!b->posicionValida(f, c)) return false;

    Bodega* bAnt = p->getBodega();
    int fAnt = p->getFila();
    int cAnt = p->getColumna();
    if (bAnt == b && fAnt == f && cAnt == c) return false; // misma celda

    if (!b->asignarPaquete(f, c, p)) return false;  // primero la nueva (falla si esta ocupada)
    bAnt->liberarCelda(fAnt, cAnt);                 // luego se libera la anterior
    p->asignarUbicacion(b, f, c);
    p->registrarBitacora(ALMACENADO, ALMACENADO, r); // queda registro del movimiento
    return true;
}
// ---------------- Reporte ----------------
void CentroDistribucion::clientesPorEnvios() {
    int n = clientes.getTamano();
    if (n == 0) {
        cout << "No hay clientes registrados en este centro." << endl;
        return;
    }
    Cliente** arr = new Cliente * [n];
    int* cant = new int[n];

    int i = 0;
    Nodo<Cliente>* nodo = clientes.getPrimero();
    while (nodo != nullptr && i < n) {
        arr[i] = nodo->getDato();
        cant[i] = arr[i]->contarDespachosFinalizados(this);
        i++;
        nodo = nodo->getSiguiente();
    }

    // Burbuja descendente por cantidad de envios finalizados
    for (int a = 0; a < n - 1; a++) {
        for (int b = 0; b < n - 1 - a; b++) {
            if (cant[b] < cant[b + 1]) {
                int t = cant[b]; cant[b] = cant[b + 1]; cant[b + 1] = t;
                Cliente* tc = arr[b]; arr[b] = arr[b + 1]; arr[b + 1] = tc;
            }
        }
    }
    cout << "Clientes por cantidad de envios finalizados - " << nombre << endl;
    for (int k = 0; k < n; k++) {
        cout << (k + 1) << ". " << arr[k]->getNombre()
            << " (" << arr[k]->getTipo() << ") - " << cant[k] << " envio(s)" << endl;
    }
    delete[] arr;
    delete[] cant;
}
