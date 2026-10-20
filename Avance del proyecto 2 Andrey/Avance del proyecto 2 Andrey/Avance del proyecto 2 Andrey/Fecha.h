#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    // Constructor
    Fecha(int dia, int mes, int anio);

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Setters
    void setDia(int nuevoDia);
    void setMes(int nuevoMes);
    void setAnio(int nuevoAnio);

    // Mostrar la fecha
    void mostrarFecha() const;

    // Validar la fecha
    bool esValida() const;
};

#endif

