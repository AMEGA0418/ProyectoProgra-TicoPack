#pragma once
#include "Nodo.h"

// Lista enlazada simple generica y dinamica.
// La lista es DUENA de los objetos que guarda: al eliminar un elemento
// (o al destruirse la lista) se libera tambien el objeto con delete.
// Por eso solo se deben insertar objetos creados con new.
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    int tamano;

public:
    ListaEnlazada() : primero(nullptr), ultimo(nullptr), tamano(0) {}

    ~ListaEnlazada() {
        Nodo<T>* actual = primero;
        while (actual != nullptr) {
            Nodo<T>* temporal = actual;
            actual = actual->getSiguiente();
            delete temporal->getDato();
            delete temporal;
        }
    }

    // Elimina solo los nodos y conserva los objetos apuntados.
    // Se utiliza para listas que mantienen referencias no propietarias.
    void liberarNodosSinEliminarDatos() {
        Nodo<T>* actual = primero;
        while (actual != nullptr) {
            Nodo<T>* temporal = actual;
            actual = actual->getSiguiente();
            delete temporal;
        }
        primero = nullptr;
        ultimo = nullptr;
        tamano = 0;
    }

    // Evita copias accidentales (provocarian doble delete).
    ListaEnlazada(const ListaEnlazada&) = delete;
    ListaEnlazada& operator=(const ListaEnlazada&) = delete;

    // Inserta al final en O(1). Ignora punteros nulos.
    void insertarFinal(T* d) {
        if (d == nullptr) return;

        Nodo<T>* nuevo = new Nodo<T>(d);

        if (primero == nullptr) {
            primero = nuevo;
            ultimo = nuevo;
        }
        else {
            ultimo->setSiguiente(nuevo);
            ultimo = nuevo;
        }
        tamano++;
    }

    // Elimina el nodo que contiene a d y libera tambien el objeto d.
    // Devuelve false si d no esta en la lista.
    bool eliminar(T* d) {
        Nodo<T>* actual = primero;
        Nodo<T>* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->getDato() == d) {
                if (anterior == nullptr) {
                    primero = actual->getSiguiente();
                }
                else {
                    anterior->setSiguiente(actual->getSiguiente());
                }

                if (actual == ultimo) {
                    ultimo = anterior;
                }

                delete actual->getDato();
                delete actual;
                tamano--;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    Nodo<T>* getPrimero() const { return primero; }
    int getTamano() const { return tamano; }
    bool estaVacia() const { return primero == nullptr; }
};