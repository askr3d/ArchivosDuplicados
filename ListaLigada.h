#include "Archivo.h"
#include <fstream>
#include <sys/stat.h>

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
            for (size_t i = 0; i < posicion; i++)
            {
                nodoAuxiliar = nodoAuxiliar->siguiente;
            }
            return nodoAuxiliar;
        }

        void mostrarArchivos(){
            Archivo *nodoAuxiliar = new Archivo();
            for(int i=0; i < cantidadArchivos; i++){
                cout<<i<<endl;
                nodoAuxiliar = this->buscarArchivoPorPosicion(i);
                cout<<endl
                    <<"Peso: "<<nodoAuxiliar->peso
                    <<endl
                    <<"Nombre del archivos: "<<nodoAuxiliar->nombre
                    <<endl;
                nodoAuxiliar = nodoAuxiliar->siguiente;
            }
        }

        void eliminarPorPosicion(int posicion){
            if(posicion<this->cantidadArchivos && posicion>=0){
                if(posicion==0){
                    this->Head = this->Head->siguiente;
                }else{
                    Archivo *nodoAuxiliar = this->Head;
                    Archivo *nodoObjetivo;
                    //Obtendra un nodo anterior al nodo objetivo
                    for(int i=1; i< posicion; i++){
                        nodoAuxiliar = nodoAuxiliar->siguiente;
                    }
                    //Obtenemos el nodoObjetivo
                    nodoObjetivo = nodoAuxiliar->siguiente;
                    //El nodoObjetivo->siguiente pasa a tomar el lugar del nodo objetivo
                    nodoAuxiliar->siguiente = nodoObjetivo->siguiente;
                    delete(nodoObjetivo);
                }
                this->cantidadArchivos--;
            }else{
                cout<<endl<<"Posicion invalida: "<<posicion<<endl;
            }
        }

        void ordenamiento(){

            //verifica subcarpeta, false: crea subcarpeta
            string carpeta = "duplicados";
            if(!fileExists(carpeta)){
                mkdir("./duplicados");
            }
            
            //metodo burbuja
            int i, j;
            Archivo temp = Archivo();
            Archivo *obj1, *obj2;
            for(i = 0; i < cantidadArchivos - 1; i++){
                for(j = i +1; j < cantidadArchivos; j++){
                    obj1 = buscarArchivoPorPosicion(i);
                    obj2 = buscarArchivoPorPosicion(j);
                    
                    if(esIgualPesoArchivos(obj1->peso, obj2->peso) || compararArchivos(obj1->nombre, obj2->nombre)){
                        cout<<"obj1->nombe: "<<obj1->nombre<<"obj2->nombre: "<<obj2->nombre<<endl;
                        if(obj2->nombre!="ListaLigada.h" && obj2->nombre!="main.cpp" && obj2->nombre!="main.exe" && obj2->nombre!="Archivo.h" && obj2->nombre!="README.md"){
                            moverArchivo(obj2->nombre);
                            eliminarPorPosicion(j);
                            j=0;
                        }else{
                            moverArchivo(obj1->nombre);
                            eliminarPorPosicion(i);
                        }
                        i=0;
                    }else if(obj1->peso > obj2->peso){
                        temp.peso = obj1->peso;
                        temp.nombre = obj1->nombre;

                        obj1->peso = obj2->peso;
                        obj1->nombre = obj2->nombre;

                        obj2->peso = temp.peso;
                        obj2->nombre = temp.nombre;
                    }
                }
            }
            
        }

        void moverArchivo(string &nombreArchivo){
            string auxLinea;
            fstream fileOrginal(nombreArchivo);
            string nuevoArchivo = "./duplicados/" + nombreArchivo;
            ofstream fileNuevo(nuevoArchivo);

            if(!fileOrginal.fail() && !fileNuevo.fail()){
                while(getline(fileOrginal, auxLinea)){
                    fileNuevo << auxLinea;
                }
                fileOrginal.close();
                fileNuevo.close();
                remove(nombreArchivo.c_str());
            }

        }

        bool fileExists(string const &nombre){
            ifstream f(nombre.c_str());
            return f.good();
        }

        bool esIgualPesoArchivos(long obj1, long obj2){
            if(obj1 == obj2){
                return 1;
            }
            return 0;
        }

        bool compararArchivos(string &archivo1, string &archivo2){
            ifstream f1(archivo1);
            ifstream f2(archivo2);

            if(f1.fail() && f2.fail()){
                cout<<endl<<"Error al abrir los archivos a comparar"<<endl;
                return false;
            }

            char caracter;
            char caracter2;
            string file1_contenido, file2_contenido;
            
            while(f1.get(caracter)){
                if(caracter != 32 && caracter != '\n'){
                    file1_contenido += caracter;
                }
            }
            while(f2.get(caracter2)){
                if(caracter2 != 32 && caracter2 != '\n'){
                    file2_contenido += caracter2;
                }
            }

            return file1_contenido==file2_contenido;
        }
};