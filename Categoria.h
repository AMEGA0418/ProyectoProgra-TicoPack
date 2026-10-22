#pragma once
#include <string>

using namespace std;

// Categorias de paquete. Se guardan como int usando estas constantes
// (Categoria::GENERAL, etc.), igual que los datos static vistos en clase.
// El numero coincide con la opcion del menu: 1=General, 2=Fragil,
// 3=Tecnologia, 4=Documentos.
class Categoria {
public:
    static const int GENERAL;
    static const int FRAGIL;
    static const int TECNOLOGIA;
    static const int DOCUMENTOS;

    // true si el valor es una categoria definida (1 a 4).
    static bool esValida(int categoria);

    // Texto para mostrar. Si el valor no es valido devuelve "Desconocida".
    static string toString(int categoria);
};
