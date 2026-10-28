#pragma once
#include <string>
#include "Fecha.h"

using namespace std;

class Validador {
public:
    static bool textoValido(const string& texto);
    static bool numeroPositivo(double numero);
    static bool enteroNoNegativo(int numero);
    static bool fechaValida(const Fecha& fecha);
    static bool correoValido(const string& correo);
};

