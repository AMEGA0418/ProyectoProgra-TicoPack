#pragma once
#include "Categoria.h"

// Tarifas por kilogramo compartidas por toda la aplicacion. Se declaran
// como atributos static para no repetir los montos dentro de cada calculo.
class Tarifas {
public:
	static const double TARIFA_GENERAL;
	static const double TARIFA_FRAGIL;
	static const double TARIFA_TECNOLOGIA;
	static const double TARIFA_DOCUMENTOS;

	// Devuelve la tarifa por kilogramo de la categoria indicada.
	// Si la categoria no es valida devuelve 0.
	static double tarifaPorCategoria(int categoria);

	// costo = peso * tarifa por kilogramo de la categoria.
	static double calcular(double peso, int categoria);
};
