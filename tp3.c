#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ABECEDARIO 256


typedef struct NodoHuffman {
    char caracter;
    int frecuencia;
    struct NodoHuffman *izquierda, *derecha;
} NodoHuffman;

// Estructura para representar un nodo de la cola de prioridad
typedef struct {
    NodoHuffman *nodo;
} ElementoColaPrioridad;

// Cola de prioridad para construir el árbol de Huffman
typedef struct {
    ElementoColaPrioridad *elementos;
    int capacidad;
    int tamano;
} ColaPrioridad;







NodoHuffman *nuevoNodo(char caracter, int frecuencia);
float logaritmo(int,float);
void lee_archivo (char*, unsigned short[], unsigned int*);
void completaPunteroAbecedario(unsigned char[],unsigned short []);
void creaArchivoBinario(char*, unsigned char[]);

int main(int argc, char *argv[]) {
   
   char* extension_txt  = ".txt";
   char *nombre_archivo = NULL;
   unsigned short abecedario[MAX_ABECEDARIO]={0};
   unsigned int totalLetras=0;
   unsigned char punteroAbecedario[MAX_ABECEDARIO]={0};
   unsigned char* tablaHuffman;

   for (int i = 1; i < argc; i++) {
      char *param = argv[i];
      if (strstr(param, extension_txt) != NULL)  //.bin
      nombre_archivo = param;
   }
    lee_archivo(nombre_archivo, abecedario, &totalLetras);

    for (int i = 0 ; i<MAX_ABECEDARIO;i++){
        printf("%d ",abecedario[i]);
    }

    completaPunteroAbecedario(punteroAbecedario,abecedario);

    for (int i = 0 ; i<MAX_ABECEDARIO;i++){
        printf("%d ",punteroAbecedario[i]);
    }
    
    tablaHuffman=creaTablaHuffman();

    creaArchivoBinario(nombre_archivo,punteroAbecedario);


}

unsigned char* creaTablaHuffman(){

}

void creaArchivoBinario(char *nombre_archivo, unsigned char punteroAbecedario[]){
    
    FILE* archivoBin= fopen("compressed.bin","wb");
    FILE* archivoTxt= fopen(nombre_archivo,"rt");
    char letra;

    if (archivoBin==NULL){
        printf("Ocurrió un problema al crear el archivo");
        exit(-2);
    }
    for (int i =0; i<MAX_ABECEDARIO;i++){
        fwrite(punteroAbecedario, sizeof(char), 1, archivoBin);
    }

    while (fscanf(archivoTxt, "%c", &letra)!=EOF) {
        fwrite()
    }


    fclose(archivoBin);
}

void completaPunteroAbecedario(unsigned char punteroAbecedario[],unsigned short abecedario[]){

    int aux[MAX_ABECEDARIO];
    int posicionMayor;
    int valorMayor=-1;

    for (int i = 0 ; i<MAX_ABECEDARIO; i++){
        aux[i]=abecedario[i];
    } 

    for(int i=0;i <MAX_ABECEDARIO;i++){ //recorro el puntero almacenando la direccion de cada letra de mayor a menor en ocurrencias
        for (int j=0;j<MAX_ABECEDARIO;j++){
            if (aux[j]>valorMayor){
                valorMayor=aux[j];
                posicionMayor=j;
            }
        }
    punteroAbecedario[i]=posicionMayor;
    aux[posicionMayor]=-1;
    valorMayor=-1;
    }

}


void lee_archivo (char *nombre_archivo, unsigned short abecedario[],unsigned int *totalLetras) {
    
    unsigned char letra;
    nombre_archivo="tp3_sample0.txt";
    FILE* archivo = fopen(nombre_archivo,"rt");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        exit (-1);
    }
    while (fscanf(archivo, "%c", &letra)!=EOF) {
        abecedario[letra]++;
        *totalLetras++;
    }
    fclose(archivo); 
}

float logaritmo (int base, float num) {
      return log10(num) / log10(base);
   }

NodoHuffman *nuevoNodo(char caracter, int frecuencia) {
    NodoHuffman *nodo = (NodoHuffman *)malloc(sizeof(NodoHuffman));
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izquierda = nodo->derecha = NULL;
    return nodo;
}
