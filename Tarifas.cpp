#include "Tarifas.h"

const double Tarifas::TARIFA_GENERAL = 1500.0;
const double Tarifas::TARIFA_FRAGIL = 2000.0;
const double Tarifas::TARIFA_TECNOLOGIA = 2500.0;
const double Tarifas::TARIFA_DOCUMENTOS = 1000.0;

double Tarifas::tarifaPorCategoria(int categoria) {
	if (categoria == Categoria::GENERAL) return TARIFA_GENERAL;
	if (categoria == Categoria::FRAGIL) return TARIFA_FRAGIL;
	if (categoria == Categoria::TECNOLOGIA) return TARIFA_TECNOLOGIA;
	if (categoria == Categoria::DOCUMENTOS) return TARIFA_DOCUMENTOS;
	return 0;
}

double Tarifas::calcular(double peso, int categoria) {
	if (peso <= 0 || !Categoria::esValida(categoria)) return 0;
	return peso * tarifaPorCategoria(categoria);
}
