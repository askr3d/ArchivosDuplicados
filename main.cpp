#include "ListaLigada.h"
#include <iostream>
using namespace std;


int main(){

    ListaLigada lista = ListaLigada();

    Archivo conjuntoArchivos[] = {
        Archivo(123, "hola"),
        Archivo(10, "algo"),
        Archivo(20, "cool"),
        Archivo(10, "yeah")
    };

    for(Archivo archivo : conjuntoArchivos){
        lista.insertarAlInicio(archivo);
    }

    cout<<lista.cantidadArchivos<<endl;
    lista.mostrarArchivos();

    return 0;
}