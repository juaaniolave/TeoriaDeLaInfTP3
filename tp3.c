#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ABECEDARIO 256
float logaritmo(int,float);
void lee_archivo (char*);

int main(int argc, char *argv[]) {
   
   char* extension_txt  = ".txt";
   char *nombre_archivo = NULL;

   for (int i = 1; i < argc; i++) {
      char *param = argv[i];
      if (strstr(param, extension_txt) != NULL)  //.bin
      nombre_archivo = param;
   }
    lee_archivo(nombre_archivo);
}


void lee_archivo (char *nombre_archivo) {
    
    int abecedario[MAX_ABECEDARIO]={0};
    char letra;
    double totalLetras=0;
    nombre_archivo="tp3_sample0.txt";
    FILE* archivo = fopen(nombre_archivo,"rt");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        exit (-1);
    }

    while (fscanf(archivo, "%c", &letra)!=EOF) {
        abecedario[letra]++;
        totalLetras++;
    }

    for (int i =0 ; i< MAX_ABECEDARIO ; i++){
        printf ("%c: %d\n ",i,abecedario[i] );
    }

    fclose(archivo);
    


}

   float logaritmo (int base, float num) {
      return log10(num) / log10(base);
   }

