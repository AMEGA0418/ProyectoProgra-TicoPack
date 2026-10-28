#pragma once
#include "Categoria.h"

class Tarifas {
public:
	static double costoBase(double peso, int distancia);
	static double costoPorCategoria(double costo, int categoria);
	static double calcular(double peso, int categoria, int distancia);
};
