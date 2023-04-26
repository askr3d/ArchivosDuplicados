#include "Archivo.h"

class ListaLigada{
    private:
        Archivo *Head;
    public: 
        int cantidadArchivos;

        ListaLigada(){
            this->Head = nullptr;
            this->cantidadArchivos=0;
        }

        void insertarAlInicio(Archivo data){
            Archivo *nuevoNodo = new Archivo(data.peso, data.nombre);
            nuevoNodo->siguiente = this->Head;
            
            this->Head = nuevoNodo;
            cantidadArchivos++;
        }

        void borrarAlFinal(){
            Archivo *nodoAuxiliar = this->Head;
            if(cantidadArchivos==1){
                delete(this->Head);
                this->Head = nullptr;
            }else{
                while(nodoAuxiliar->siguiente->siguiente != nullptr){
                    nodoAuxiliar = nodoAuxiliar->siguiente;
                }
                delete(nodoAuxiliar->siguiente);
                nodoAuxiliar->siguiente = nullptr;
            }
            cantidadArchivos--;
        }

        Archivo *buscarArchivoPorPosicion(int posicion){
            Archivo *nodoAuxiliar = this->Head;
            for (size_t i = 0; i < cantidadArchivos; i++)
            {
                nodoAuxiliar = nodoAuxiliar->siguiente;
            }
            return nodoAuxiliar;
        }

        void mostrarArchivos(){
            Archivo *nodoAuxiliar = this->Head;
            while(nodoAuxiliar != nullptr){
                cout<<endl
                    <<"Peso: "<<nodoAuxiliar->peso
                    <<endl
                    <<"Nombre del archivos: "<<nodoAuxiliar->nombre
                    <<endl;
                nodoAuxiliar = nodoAuxiliar->siguiente;
            }
        }
};