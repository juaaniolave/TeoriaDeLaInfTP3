#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_ABECEDARIO 256
#define MAX_CODIGO 32
#define MAX_STRING 1024*1024


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
void creaArchivoBinario(char*, unsigned short[], datosTablaHuffman[]);
void creaArrayNodos(ArbolHuffman[], unsigned short[]);
void creaArbolHuffmanFinal(ArbolHuffman arrayNodos[]);
void muestraArbol(ArbolHuffman arbol);
void swap(ArbolHuffman *a, ArbolHuffman *b);
void creaTablaHuffman(ArbolHuffman nodo, char* codigo, int longitudCodigo,datosTablaHuffman tablaHuffman[], int* indice);
void ordenaTablaHuffman( datosTablaHuffman tablaHuffman[], int tamano);
void intercambiar(datosTablaHuffman* a, datosTablaHuffman* b);
void creaArchivoTexto(char *nombre_archivo,char *nombre_archivo_comprimido);


int main(int argc, char *argv[]) {
   
   char* extension_txt  = ".txt";
   char *nombre_archivo = NULL;
   char *nombre_archivo_comprimido = NULL;
   unsigned short abecedario[MAX_ABECEDARIO]={0};
   unsigned int totalLetrasDiferentes=0;

   
   for (int i = 1; i < argc; i++) {
      char *param = argv[i];
      if (strstr(param, extension_txt) != NULL)  //.bin
      nombre_archivo = param;
    }

    nombre_archivo="tp3_sample0.txt";
    nombre_archivo_comprimido="compressed.bin";

    lee_archivo(nombre_archivo, abecedario, &totalLetrasDiferentes);

    ArbolHuffman arrayNodos[totalLetrasDiferentes];

    creaArrayNodos(arrayNodos, abecedario);

    creaArbolHuffmanFinal(arrayNodos);

    datosTablaHuffman tablaHuffman[totalLetrasDiferentes];


    for (int i = 0 ; i< totalLetrasDiferentes; i++){ // inicializa todo en null
        for (int j = 0; j < MAX_CODIGO ; j++)
        tablaHuffman[i].codigo[j] = '\0'; 
    }
 
    char codigo[MAX_CODIGO];
    int indice = 0;
    creaTablaHuffman(arrayNodos[0], codigo, 0, tablaHuffman, &indice);

    ordenaTablaHuffman(tablaHuffman, totalLetrasDiferentes);

    for (int i = 0 ; i< totalLetrasDiferentes ; i++){

        printf ("%d, %c, %s \n", i, tablaHuffman[i].letra, tablaHuffman[i].codigo);

    }


   creaArchivoBinario(nombre_archivo,abecedario,tablaHuffman);

   creaArchivoTexto(nombre_archivo, nombre_archivo_comprimido);

   //creaArchivoTexto();

return 0;
}


void creaArchivoTexto(char *nombre_archivo,char *nombre_archivo_comprimido){

    FILE* archivoBin= fopen(nombre_archivo_comprimido,"rb");
    FILE* archivoTxt= fopen("archivo_nuevo.txt","wt");
    char textoCodificado[MAX_STRING];
    char letra;
    int k=0, contador=0;
    char byte=0;
    unsigned int totalLetrasDiferentes=0;
    unsigned short abecedario[MAX_ABECEDARIO]={0};

    for (int i =0; i<MAX_ABECEDARIO;i++){
        fread(&abecedario[i], sizeof(short), 1, archivoBin);
        if (abecedario[i]!=0){
            totalLetrasDiferentes++;
        }
    }

    for (int i =0; i<MAX_ABECEDARIO;i++){
        printf("%d ",abecedario[i]);
    }

    // todo el bloque de funciones de abajo son las del main para crear la tablahuffman apartir del abecedario, deberia haber hecho una funcion
    //aparte con todo eso pero lleva doble y triple puntero asique :D
    //---------------------------------------------------------------------------------------------
    ArbolHuffman arrayNodos[totalLetrasDiferentes];
    creaArrayNodos(arrayNodos, abecedario);
    creaArbolHuffmanFinal(arrayNodos);
    datosTablaHuffman tablaHuffman[totalLetrasDiferentes];
    for (int i = 0 ; i< totalLetrasDiferentes; i++){ // inicializa todo en null
        for (int j = 0; j < MAX_CODIGO ; j++)
        tablaHuffman[i].codigo[j] = '\0'; 
    }
    char codigo[MAX_CODIGO];
    int indice = 0;
    creaTablaHuffman(arrayNodos[0], codigo, 0, tablaHuffman, &indice);
    ordenaTablaHuffman(tablaHuffman, totalLetrasDiferentes);
    for (int i = 0 ; i< totalLetrasDiferentes ; i++){
        printf ("%d, %c, %s \n", i, tablaHuffman[i].letra, tablaHuffman[i].codigo);
    }
    //---------------------------------------------------------------------------------------------
    int u=0;
    while (fread(&byte, sizeof(char), 1, archivoBin)){
        for (int j = 0; j < 8; j++){
            if ((byte&0b10000000)== 0b10000000){
                textoCodificado[k++]='1';
            }
            else
                textoCodificado[k++]='0';
        byte<<=1;
        }
    }
        

    int m=0;
    char buffer[32]={'\0'};

    for (int j = 0; j < MAX_STRING; j++){
        buffer[m++]=textoCodificado[j];
        for (int h = 0; h < totalLetrasDiferentes; h++){
            if(!strcmp(buffer,tablaHuffman[h].codigo)){
                printf("%c",tablaHuffman[h].letra);
                char bufferTexto[2]={tablaHuffman[h].letra,'\0'};
                fprintf(archivoTxt,&bufferTexto);
                
                for (int f=0;f<32;f++){
                    buffer[f]='\0';
                }
                m=0;
            }
        }

    }

    fclose(archivoBin);
    fclose(archivoTxt);
}



void creaArchivoBinario(char *nombre_archivo, unsigned short abecedario[], datosTablaHuffman tablaHuffman[] ){

    FILE* archivoBin= fopen("compressed.bin","wb");
    FILE* archivoTxt= fopen(nombre_archivo,"rt");
    char letra;
    int k=0,j=0,contador=0;
    char byte=0;

    if (archivoBin==NULL){
        printf("Ocurrió un problema al crear el archivo");
        exit(-2);
    }
    for (int i =0; i<MAX_ABECEDARIO;i++){
        fwrite(&abecedario[i], sizeof(short), 1, archivoBin);
    }

    while (fscanf(archivoTxt, "%c", &letra)!=EOF) {

        while (tablaHuffman[k].letra!=letra){
            k++;
        }
        j=0;

        while (tablaHuffman[k].codigo[j]!='\0'){
            
            byte<<=1;
            contador++;
            
            if (tablaHuffman[k].codigo[j++]=='1'){
                byte|=1;
            }

            if (contador==8){
                fwrite(&byte, sizeof(byte), 1, archivoBin);
                byte=0;
                contador=0;
            }
        }
        k=0;   
    }

    fwrite(&byte, sizeof(byte), 1, archivoBin);
    fclose(archivoBin);
    fclose(archivoTxt);
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
        codigo[longitudCodigo]='\0';
       // printf("%c, %s\n", nodo->caracter, codigo);
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