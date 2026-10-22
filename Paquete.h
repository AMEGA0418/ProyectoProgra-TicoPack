#pragma once
#include <string>
#include "Fecha.h"
#include "Categoria.h"
#include "EstadoPaquete.h"
#include "ListaEnlazada.h"
#include "RegistroBitacora.h"

using namespace std;

class Cliente;
class Colaborador;
class Bodega;
class CentroDistribucion;

class Paquete {
private:
    string codigo;
    string descripcion;
    double peso;
    int categoria;      // valor de Categoria (1 a 4)
    int estado;         // valor de EstadoPaquete
    Cliente* propietario;
    CentroDistribucion* centro;
    Bodega* bodega;      // nullptr si no tiene ubicacion
    int fila;            // -1 si no tiene ubicacion
    int columna;         // -1 si no tiene ubicacion
    ListaEnlazada<RegistroBitacora> bitacora;

    // --- Operaciones que solo puede ejecutar CentroDistribucion ---
    // (almacenar, reubicar, aprobar solicitud, finalizar despacho, resolver
    // incidencias de despacho). Asi el menu no puede saltarse las reglas.
    friend class CentroDistribucion;

    // Aplica un cambio de estado permitido por la tabla y lo registra en la
    // bitacora. NO valida las reglas propias de cada operacion (celda,
    // despacho, etc.): eso lo hace CentroDistribucion antes de llamarla.
    bool aplicarTransicion(int nuevo, Colaborador* responsable,
        const Fecha& fecha);
    void asignarUbicacion(Bodega* bodega, int fila, int columna);
    void liberarUbicacion();

    void registrarBitacora(int anterior, int nuevo,
        Colaborador* responsable, const Fecha& fecha);

public:
    // Validaciones del enunciado: codigo y descripcion no vacios, peso > 0.
    static bool datosValidos(const string& codigo, const string& descripcion,
        double peso);

    // Estado inicial RECIBIDO, sin bodega ni celda.
    Paquete(const string& codigo, const string& descripcion, double peso,
        int categoria, Cliente* propietario, CentroDistribucion* centro);

    string getCodigo() const;
    string getDescripcion() const;
    double getPeso() const;
    int getCategoria() const;
    int getEstado() const;
    Cliente* getPropietario() const;
    CentroDistribucion* getCentro() const;
    Bodega* getBodega() const;
    int getFila() const;
    int getColumna() const;
    bool tieneUbicacion() const;
    const ListaEnlazada<RegistroBitacora>& getBitacora() const;

    // true si la tabla de transiciones del enunciado permite actual -> nuevo.
    bool esTransicionValida(int nuevo) const;

    // Si el paquete esta en INCIDENCIA, devuelve el estado en que estaba
    // antes (leido de la bitacora). Si no, devuelve el estado actual.
    int getEstadoPreIncidencia() const;

    // Cambio de estado "general" del menu. Solo permite:
    //  - pasar a INCIDENCIA desde Recibido, Almacenado o En transito
    //  - resolver una incidencia volviendo a Almacenado SI conserva su celda
    // Todo lo demas (almacenar, aprobar, finalizar, resolver incidencias de
    // despacho) se hace por su operacion en CentroDistribucion.
    bool cambiarEstado(int nuevo, Colaborador* responsable,
        const Fecha& fecha);

    void mostrar() const;
    void mostrarBitacora() const;   // del mas antiguo al mas reciente
};