#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "open.h"

int main(int argc, char **argv)
{
    if(argc < 3){
            printf("Esta faltando parametros!\n");
            return -1;
    }

    printf("%d ", argc);
    
    if(!strcmp(argv[1], "-open")){
        open_texto(argv[2]);
        printf("\nAberto com sucesso");
        return 0;
    }else
    if(!strcmp(argv[1], "-convert")){
        convert_texto(argv[2], argv[3]);
        printf("\nConvertido com sucesso");
        return 0;
    }else
    if(!strcmp(argv[1], "-segment")){
        printf("\nSegmentado com sucesso");
        return 0;
    }else
    if(!strcmp(argv[1], "-cc")){
        printf("\nCC com sucesso");
        return 0;
    }else
    if(!strcmp(argv[1], "-lab")){
        printf("\nLAB com sucesso");
        return 0;
    }else{
        printf("\nComando nao existe");
    }
}
        