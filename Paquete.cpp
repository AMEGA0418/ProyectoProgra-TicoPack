#include "Paquete.h"
#include "Bodega.h"
#include "Cliente.h"
#include "Colaborador.h"
#include <iostream>

using namespace std;

// true si el caracter es un espacio en blanco (espacio, tab, salto de linea, etc.)
static bool esEspacio(char c) {
    return c == ' ' || c == '\t' || c == '\n' ||
        c == '\r' || c == '\f' || c == '\v';
}

// true si el texto esta vacio o solo tiene espacios
static bool textoVacio(const string& s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (!esEspacio(s[i])) return false;
    }
    return true;
}

bool Paquete::datosValidos(const string& codigo, const string& descripcion,
    double peso) {
    return !textoVacio(codigo) && !textoVacio(descripcion) && peso > 0;
}

Paquete::Paquete(const string& codigo, const string& descripcion, double peso,
    Categoria categoria, Cliente* propietario, CentroDistribucion* centro) {
    this->codigo = codigo;
    this->descripcion = descripcion;
    this->peso = peso;
    this->categoria = categoria;
    this->propietario = propietario;
    this->centro = centro;
    estado = EstadoPaquete::RECIBIDO;
    bodega = nullptr;
    fila = -1;
    columna = -1;
}

string Paquete::getCodigo() const { return codigo; }
string Paquete::getDescripcion() const { return descripcion; }
double Paquete::getPeso() const { return peso; }
Categoria Paquete::getCategoria() const { return categoria; }
EstadoPaquete Paquete::getEstado() const { return estado; }
Cliente* Paquete::getPropietario() const { return propietario; }
CentroDistribucion* Paquete::getCentro() const { return centro; }
Bodega* Paquete::getBodega() const { return bodega; }
int Paquete::getFila() const { return fila; }
int Paquete::getColumna() const { return columna; }

bool Paquete::tieneUbicacion() const {
    return bodega != nullptr;
}

const ListaEnlazada<RegistroBitacora>& Paquete::getBitacora() const {
    return bitacora;
}

bool Paquete::esTransicionValida(EstadoPaquete nuevo) const {
    return transicionPaqueteEnTabla(estado, nuevo);
}

EstadoPaquete Paquete::getEstadoPreIncidencia() const {
    if (estado != EstadoPaquete::INCIDENCIA) {
        return estado;
    }

    // El ultimo registro es el que llevo el paquete a INCIDENCIA.
    EstadoPaquete anterior = estado;
    for (Nodo<RegistroBitacora>* n = bitacora.getPrimero(); n != nullptr;
        n = n->getSiguiente()) {
        anterior = n->getDato()->getEstadoAnterior();
    }
    return anterior;
}

void Paquete::registrarBitacora(EstadoPaquete anterior, EstadoPaquete nuevo,
    Colaborador* responsable, const Fecha& fecha) {
    bitacora.insertarFinal(new RegistroBitacora(anterior, nuevo, fecha, responsable));
}

bool Paquete::aplicarTransicion(EstadoPaquete nuevo, Colaborador* responsable,
    const Fecha& fecha) {
    if (responsable == nullptr || !fecha.esValida()) return false;
    if (!esTransicionValida(nuevo)) return false;

    EstadoPaquete anterior = estado;
    registrarBitacora(anterior, nuevo, responsable, fecha);
    estado = nuevo;
    return true;
}

void Paquete::asignarUbicacion(Bodega* nuevaBodega, int nuevaFila, int nuevaColumna) {
    bodega = nuevaBodega;
    fila = nuevaFila;
    columna = nuevaColumna;
}

void Paquete::liberarUbicacion() {
    bodega = nullptr;
    fila = -1;
    columna = -1;
}

bool Paquete::cambiarEstado(EstadoPaquete nuevo, Colaborador* responsable,
    const Fecha& fecha) {
    bool permitido = false;

    if (nuevo == EstadoPaquete::INCIDENCIA) {
        permitido = (estado == EstadoPaquete::RECIBIDO ||
            estado == EstadoPaquete::ALMACENADO ||
            estado == EstadoPaquete::EN_TRANSITO);
    }
    else if (estado == EstadoPaquete::INCIDENCIA &&
        nuevo == EstadoPaquete::ALMACENADO) {
        permitido = tieneUbicacion();
    }

    if (!permitido) return false;
    return aplicarTransicion(nuevo, responsable, fecha);
}

void Paquete::mostrar() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Peso: " << peso << " kg" << endl;
    cout << "Categoria: " << categoriaToString(categoria) << endl;
    cout << "Estado: " << estadoPaqueteToString(estado) << endl;

    if (propietario != nullptr) {
        cout << "Propietario: " << propietario->getNombre()
            << " (" << propietario->getIdentificacion() << ")" << endl;
    }

    if (tieneUbicacion()) {
        Celda* celda = bodega->consultarCelda(fila, columna);
        cout << "Ubicacion: bodega " << bodega->getCodigo();
        if (celda != nullptr) {
            cout << ", celda " << celda->getIdentificador();
        }
        cout << endl;
    }
    else {
        cout << "Ubicacion: sin ubicacion asignada" << endl;
    }
}

void Paquete::mostrarBitacora() const {
    cout << "Bitacora del paquete " << codigo << ":" << endl;

    if (bitacora.estaVacia()) {
        cout << "  (sin cambios de estado registrados)" << endl;
        return;
    }

    int numero = 1;
    for (Nodo<RegistroBitacora>* n = bitacora.getPrimero(); n != nullptr;
        n = n->getSiguiente()) {
        cout << "  " << numero << ". ";
        n->getDato()->mostrar();
        numero++;
    }
}