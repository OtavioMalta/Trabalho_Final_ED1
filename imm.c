#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad/TMain.h"
#include "tad/Matriz.h"

int main(int argc, char *argv[])
{
    int ret;
    if (argc < 2)
    {
        printf("Error, missing parameter!\n");
        return 0;
    }
    if(strcmp(argv[1], "-open")==0){
        int res,row,col;
        res = tam_file(argv[2], &row,&col);
        if(res!=SUCCESS){printf("[ERRO %d]", res);exit(0);}
        
        mtz *mat = mtz_create(row,col);
        res = open_file(argv[2], &mat);
        if(res!=SUCCESS){printf("[ERRO %d]",res);exit(0);}

        mtz_print(mat);
        mtz_free(mat);
    }else if(strcmp(argv[1], "-convert")==0){
        if (argc != 4){
            printf("[ERRO] Confira a quantidade de argumentos!");
            exit(0);
        }
        int res = convert(argv[2], argv[3]);
        if(res!=SUCCESS){
            printf("[ERRO %d]", res);
        } else{
            printf("\nConvertido com sucesso!");
        }
        return 0;
    }else if(strcmp(argv[1], "-segment")==0){
        if (argc != 5){
            printf("[ERRO] Confira a quantidade de argumentos!");
            exit(0);
        }
        int thr = atoi(argv[2]);
        int res = segment(thr,argv[3],argv[4]);
        if(res!=SUCCESS){
            printf("[ERRO %d]", res);
        } else{
            printf("\nSegmentado com sucesso");
        }
        return 0;
    }else if(strcmp(argv[1], "-tam")==0){
        int r,c;
        int res = tam_file(argv[2], &r,&c);
        if(res!=SUCCESS){
            printf("[ERRO %d]", res);
        } else{
            printf("\nLinha:%d Coluna:%d", r,c);
        }
        return 0;
    }else if(strcmp(argv[1], "-type")==0){
        int i = type_of(argv[2]);
        if(i == 10){
            printf("Arquivo .txt");
        }else if(i == 20){
            printf("Arquivo .imm");
        }else{
            printf("[ERRO] Tipo incompativel!");
        }
    }
    else if(strcmp(argv[1], "-cc")==0){
        if (argc != 4){
            printf("[ERRO] Confira a quantidade de argumentos!");
            exit(0);
        }
        int res = componentConnected(argv[2], argv[3]);
        if(res!=SUCCESS){
            printf("[ERRO %d]", res);
        } else{
            printf("\nCC com sucesso!");
        }
        return 0;
    }else if(strcmp(argv[1], "-lab")==0){
        printf("\nLAB com sucesso");
        return 0;
    }else{
        printf("\nEste comando nao existe");
    }
}


        