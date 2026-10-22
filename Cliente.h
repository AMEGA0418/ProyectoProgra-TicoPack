#pragma once
#include <string>

using namespace std;

// Clase abstracta: solo se pueden crear PersonaFisica o Empresa.
class Cliente {
protected:
    string identificacion;
    string nombre;
    string telefono;
    string correo;

public:
    Cliente(const string& identificacion, const string& nombre,
        const string& telefono, const string& correo);

    virtual ~Cliente();

    string getIdentificacion() const;
    string getNombre() const;
    string getTelefono() const;
    string getCorreo() const;

    // No hay setIdentificacion: la identificacion es la clave de unicidad
    // dentro del centro y no debe cambiar despues de registrarse.
    void setNombre(const string& nuevoNombre);
    void setTelefono(const string& nuevoTelefono);
    void setCorreo(const string& nuevoCorreo);

    // Polimorfismo: cada tipo de cliente calcula su costo final.
    virtual double calcularCostoFinal(double costoBase) const = 0;
    virtual string getTipo() const = 0;

    virtual void mostrar() const;
};