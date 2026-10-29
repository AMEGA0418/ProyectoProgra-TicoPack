#include "Tarifas.h"

double Tarifas::costoBase(double peso, int distancia) {
	if (peso <= 0 || distancia < 0) return 0;
	// La guia define el costo base como peso por tarifa de categoria.
	// La distancia se conserva en la firma por compatibilidad con el modelo.
	return peso;
}

double Tarifas::costoPorCategoria(double costo, int categoria) {
	if (costo < 0 || !Categoria::esValida(categoria)) return 0;

	if (categoria == Categoria::GENERAL) return costo * 1500;
	if (categoria == Categoria::FRAGIL) return costo * 2000;
	if (categoria == Categoria::TECNOLOGIA) return costo * 2500;
	if (categoria == Categoria::DOCUMENTOS) return costo * 1000;
	return 0;
}

double Tarifas::calcular(double peso, int categoria, int distancia) {
	return costoPorCategoria(costoBase(peso, distancia), categoria);
}
