#include <stdio.h>
#include <stdlib.h>
#include "open.h"
  

void open_texto(char arq[20]){    
    FILE *f;
    f = fopen(arq, "r");
    
    if (f == NULL){
        printf("Arquivo indisponivel \n");
        exit(0);
    }
  
    char c = fgetc(f);
    
    while(c != EOF){
        if(c == '\n'){
            printf("\n");
        }
        printf ("%c", c);
        c = fgetc(f);
    }
  
    fclose(f);
}

void convert_texto(char arq[20], char fil[20]){
    FILE *f;
    f = fopen(arq, "r");
    
    if (f == NULL){
        printf("Arquivo indisponivel \n");
        exit(0);
    }

    int x = 0;
    int c = fgetc(f);

    while(c != EOF){
        x++;
        c = fgetc(f);
    }
    
    char vet[x];
    int y = x;
    x = 0;

    while(c != EOF){
        vet[x] = fgetc(f);
        x++;
    }

    fclose(f);

    FILE *f2;
    f2 = fopen(fil, "wb");

    fwrite(vet, sizeof(char), y, f2);
    fclose(f2);
}