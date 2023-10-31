#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_ABECEDARIO 256


typedef struct NodoHuffman {
    char caracter;
    float frecuencia;
    struct NodoHuffman *izq, *der;
} NodoHuffman;


typedef NodoHuffman* ArbolHuffman;

void ordenaArrayNodos(ArbolHuffman[]);
NodoHuffman *nuevoNodo(char caracter, int frecuencia);
float logaritmo(int,float);
void lee_archivo (char*, unsigned short[], unsigned int*);
void completaPunteroAbecedario(unsigned char[],unsigned short []);
void creaArchivoBinario(char*, unsigned char[]);
void creaArrayNodos(ArbolHuffman[], int, unsigned short[]);




int main(int argc, char *argv[]) {
   
   char* extension_txt  = ".txt";
   char *nombre_archivo = NULL;
   unsigned short abecedario[MAX_ABECEDARIO]={0};
   unsigned int totalLetrasDiferentes=0;
   unsigned char punteroAbecedario[MAX_ABECEDARIO]={0};
   unsigned char* tablaHuffman;
   ArbolHuffman arrayNodos;

   for (int i = 1; i < argc; i++) {
      char *param = argv[i];
      if (strstr(param, extension_txt) != NULL)  //.bin
      nombre_archivo = param;
   }
    lee_archivo(nombre_archivo, abecedario, &totalLetrasDiferentes);

    for (int i = 0 ; i<MAX_ABECEDARIO;i++){
        printf("%d ",abecedario[i]);
    }

    /*completaPunteroAbecedario(punteroAbecedario,abecedario);

    for (int i = 0 ; i<MAX_ABECEDARIO;i++){
        printf("%d ",punteroAbecedario[i]);
    }*/

    creaArrayNodos(arrayNodos, totalLetrasDiferentes,abecedario);
    
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

/*void completaPunteroAbecedario(unsigned char punteroAbecedario[],unsigned short abecedario[]){

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

}*/


void lee_archivo (char *nombre_archivo, unsigned short abecedario[],unsigned int *totalLetrasDiferentes) {
    
    unsigned char letra;
    nombre_archivo="tp3_sample0.txt";
    FILE* archivo = fopen(nombre_archivo,"rt");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        exit (-1);
    }
    while (fscanf(archivo, "%c", &letra)!=EOF) {
        if(!abecedario[letra]++){
            *totalLetrasDiferentes++;
        }
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
    nodo->izq = nodo->der = NULL;
    return nodo;
}

void ordenaArrayNodos(ArbolHuffman arrayNodos[]){

    int longitud = sizeof(arrayNodos) / sizeof(arrayNodos[0]);

    for (int i = 0; i < longitud-1; i++) {
        for (int j = 0; j < longitud-i-1; j++) {
            if (arrayNodos[j]->frecuencia > arrayNodos[j+1]->frecuencia) {
                swap(&arrayNodos[j], &arrayNodos[j+1]);
            }
        }
    }
}

void creaArrayNodos(ArbolHuffman* arrayNodos, int totalLetrasDiferentes, unsigned short abecedario[]){

    int totalLetras=0;
    ArbolHuffman aux[totalLetrasDiferentes];
    ArbolHuffman nodo;
    int tamanoArray =0;

    for (int i = 0; i < MAX_ABECEDARIO; i++){
        totalLetras+=abecedario[i];
    }

    for (int i = 0; i<totalLetrasDiferentes;i++){
        if (abecedario[i] !=0){
            nodo=nuevoNodo(i,(float)abecedario[i]/totalLetrasDiferentes);
        }

    }


}

void swap(ArbolHuffman *a, ArbolHuffman *b) {
    ArbolHuffman temp = *a;
    *a = *b;
    *b = temp;
}