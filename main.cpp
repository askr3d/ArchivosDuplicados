#include "ListaLigada.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
using namespace std;

void error(const char *s);

void procesoArchivo(char *archivo);


ListaLigada lista = ListaLigada();

int main(){


    //Directorio actual
    DIR *dir;
    //Obtendra los datos de cada archivo
    struct dirent *ent;

    //Empieza a leer el directorio actual
    dir = opendir (".");
    //Se verifica que no haya errores
    if(dir == NULL){
        error("No puedo abrir el directorio");
    }

    //Comienza la lectura de los archivos
    while ((ent = readdir (dir)) != NULL)
    {
        //Verifica que no sea "." o ".." como lo hace ls
        if((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0)){
            procesoArchivo(ent->d_name);
        }
    }
    closedir(dir);

    
    cout<<lista.cantidadArchivos<<endl;
    lista.mostrarArchivos();
    


    return EXIT_SUCCESS;
}

void error(const char *s){
    perror (s);
    exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo){
    FILE *fich;
    long ftam;

    fich = fopen(archivo, "r");
    if(fich){
        fseek(fich, 0L, SEEK_END);
        ftam = ftell(fich);
        fclose(fich);
        
        Archivo file = Archivo(ftam, archivo);
        lista.insertarAlInicio(file);
    // }else{
    //     cout<<endl
    //         <<archivo<<" (sin info)"<<endl;
    // }


}