#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_ABECEDARIO 256
#define MAX_CODIGO 256


typedef struct NodoHuffman {
    char caracter;
    float frecuencia;
    struct NodoHuffman *izq, *der;
} NodoHuffman;

typedef struct {
    char codigo[MAX_CODIGO];
    char letra;
} datosTablaHuffman ;


typedef NodoHuffman* ArbolHuffman;

void ordenaArrayNodos(ArbolHuffman[]);
NodoHuffman *nuevoNodo(char caracter, float frecuencia);
float logaritmo(int,float);
void lee_archivo (char*, unsigned short[], unsigned int*);
void completaPunteroAbecedario(unsigned char[],unsigned short []);
void creaArchivoBinario(char*, unsigned char[]);
void creaArrayNodos(ArbolHuffman[], unsigned short[]);
void creaArbolHuffmanFinal(ArbolHuffman arrayNodos[]);
void muestraArbol(ArbolHuffman arbol);
void swap(ArbolHuffman *a, ArbolHuffman *b);
void creaTablaHuffman(ArbolHuffman nodo, char* codigo, int longitudCodigo,datosTablaHuffman tablaHuffman[], int* indice);
void ordenaTablaHuffman( datosTablaHuffman tablaHuffman[], int tamano);
void intercambiar(datosTablaHuffman* a, datosTablaHuffman* b);


int main(int argc, char *argv[]) {
   
   char* extension_txt  = ".txt";
   char *nombre_archivo = NULL;
   unsigned short abecedario[MAX_ABECEDARIO]={0};
   unsigned int totalLetrasDiferentes=0;
   unsigned char punteroAbecedario[MAX_ABECEDARIO]={0};

   
   for (int i = 1; i < argc; i++) {
      char *param = argv[i];
      if (strstr(param, extension_txt) != NULL)  //.bin
      nombre_archivo = param;
   }
    lee_archivo(nombre_archivo, abecedario, &totalLetrasDiferentes);

    ArbolHuffman arrayNodos[totalLetrasDiferentes];

    /*completaPunteroAbecedario(punteroAbecedario,abecedario);

    for (int i = 0 ; i<MAX_ABECEDARIO;i++){
        printf("%d ",punteroAbecedario[i]);
    }*/

    creaArrayNodos(arrayNodos, abecedario);
/*
    for (int i=0;i< totalLetrasDiferentes;i++){
        printf(" %c, %f\n", arrayNodos[i]->caracter, arrayNodos[i]->frecuencia);
    }
*/
    creaArbolHuffmanFinal(arrayNodos);
   // muestraArbol(arrayNodos[0]);

    datosTablaHuffman tablaHuffman[totalLetrasDiferentes];
 
    char codigo[MAX_CODIGO];
    int indice = 0;
    creaTablaHuffman(arrayNodos[0], codigo, 0, tablaHuffman, &indice);


    // ordenaTablaHuffman(tablaHuffman, totalLetrasDiferentes);

    for (int i = 0 ; i< totalLetrasDiferentes ; i++){

        printf ("%c, %s \n", tablaHuffman[i].letra, tablaHuffman[i].codigo);

    }

   // creaArchivoBinario(nombre_archivo,punteroAbecedario);

return 0;
}


void ordenaTablaHuffman( datosTablaHuffman tablaHuffman[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = 0; j < tamano - i - 1; j++) {
            // Compara las longitudes de los códigos y realiza el intercambio si es necesario
            if (strlen(tablaHuffman[j].codigo) > strlen(tablaHuffman[j + 1].codigo)) {
                intercambiar(&tablaHuffman[j], &tablaHuffman[j + 1]);
            }
        }
    }
}

void intercambiar(datosTablaHuffman* a, datosTablaHuffman* b) {
    datosTablaHuffman temp = *a;
    *a = *b;
    *b = temp;
}

void muestraArbol(ArbolHuffman arbol){

    if(arbol!=NULL){
        
            
        muestraArbol(arbol->izq);
        if(arbol->caracter!=-1){
            printf("%c %f\n", arbol->caracter, arbol->frecuencia);
        }
        muestraArbol(arbol->der);

        
    }

}

void creaArbolHuffmanFinal(ArbolHuffman arrayNodos[]){

    int longitud=0;

    ArbolHuffman nodo;
    while(arrayNodos[longitud+1]!=NULL){
        longitud++;
    }


    while(longitud>0){

        nodo=nuevoNodo(-1,arrayNodos[longitud]->frecuencia+arrayNodos[longitud-1]->frecuencia);
        nodo->der=arrayNodos[longitud];
        nodo->izq =arrayNodos[longitud-1];
        arrayNodos[longitud-1]=nodo;
        arrayNodos[longitud]=NULL;
        ordenaArrayNodos(arrayNodos);
        longitud--;
    }

}

void creaTablaHuffman(ArbolHuffman nodo, char codigo[], int longitudCodigo,datosTablaHuffman tablaHuffman[], int* indice) {
    if (nodo == NULL) {
        return;
    }

    // Si el nodo es una hoja, almacenar la información en la tabla
    if (nodo->izq == NULL && nodo->der == NULL) {
        tablaHuffman[*indice].letra = nodo->caracter;
        strncpy(tablaHuffman[*indice].codigo, codigo, longitudCodigo);
        (*indice)++;
    }

    // Recorrer el subárbol izquierdo con un "0" añadido al código
    codigo[longitudCodigo] = '0';
    creaTablaHuffman(nodo->izq, codigo, longitudCodigo + 1, tablaHuffman, indice);

    // Recorrer el subárbol derecho con un "1" añadido al código
    codigo[longitudCodigo] = '1';
    creaTablaHuffman(nodo->der, codigo, longitudCodigo + 1, tablaHuffman, indice);
}


void creaArchivoBinario(char *nombre_archivo, unsigned char punteroAbecedario[]){
    /*
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
    */
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
        if(abecedario[letra]++==0){
            (*totalLetrasDiferentes)++;
        }
    }
    fclose(archivo); 
}

float logaritmo (int base, float num) {
      return log10(num) / log10(base);
   }

NodoHuffman *nuevoNodo(char caracter, float frecuencia) {
    NodoHuffman *nodo = (NodoHuffman *)malloc(sizeof(NodoHuffman));
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izq = nodo->der = NULL;
    return nodo;
}

void ordenaArrayNodos(ArbolHuffman arrayNodos[]){

    int longitud = 0;

    while (arrayNodos[longitud]!=NULL){
        longitud++;
    }

    for (int i = 0; i < longitud-1; i++) {
        for (int j = 0; j < longitud-i-1; j++) {
            if (arrayNodos[j]->frecuencia < arrayNodos[j+1]->frecuencia) {
                swap(&arrayNodos[j], &arrayNodos[j+1]);
            }
        }
    }
}

void creaArrayNodos(ArbolHuffman arrayNodos[], unsigned short abecedario[]){

    int totalLetras=0;
    int tamanoArray =0;

    for (int i = 0; i < MAX_ABECEDARIO; i++){
        totalLetras+=abecedario[i];
    }

    for (int i = 0; i<MAX_ABECEDARIO;i++){
        if (abecedario[i] !=0){
            arrayNodos[tamanoArray++]=nuevoNodo(i,abecedario[i]/(float)totalLetras);
        }
    }
    if (tamanoArray!=MAX_ABECEDARIO){
        arrayNodos[tamanoArray]=NULL;
    }
    ordenaArrayNodos(arrayNodos);
}

void swap(ArbolHuffman *a, ArbolHuffman *b) {
    ArbolHuffman* temp = *a;
    *a = *b;
    *b = temp;
}