#include <iostream>
using namespace std;

class Archivo{

    public: 
        Archivo *siguiente;
        long peso;
        string nombre;

        Archivo(long peso=0, string nombre=""){
            this->peso = peso;
            this->nombre = nombre;
            this->siguiente = nullptr;
        }

        
};