#pragma once

// Nodo generico de una lista enlazada simple.
// El nodo NO es dueno del dato: quien libera el objeto es ListaEnlazada<T>.
template <typename T>
class Nodo {
private:
    T* dato;
    Nodo<T>* siguiente;

public:
    Nodo(T* d) : dato(d), siguiente(nullptr) {}

    T* getDato() const { return dato; }
    Nodo<T>* getSiguiente() const { return siguiente; }
    void setSiguiente(Nodo<T>* s) { siguiente = s; }
};