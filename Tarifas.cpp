#include "Tarifas.h"

 double Tarifas::costoBase(double peso, int distancia) {
	if (peso <= 0 || distancia < 0) return 0;
	return peso * 100 + distancia * 10;
}

double Tarifas::costoPorCategoria(double costo, int categoria) {
	if (costo < 0 || !Categoria::esValida(categoria)) return 0;

	if (categoria == Categoria::FRAGIL) return costo * 1.25;
	if (categoria == Categoria::TECNOLOGIA) return costo * 1.15;
	if (categoria == Categoria::DOCUMENTOS) return costo * 0.90;
	return costo;
}

double Tarifas::calcular(double peso, int categoria, int distancia) {
	return costoPorCategoria(costoBase(peso, distancia), categoria);
}
