#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TMain.h"

int open_file(char *file, mtz **mat){ 
    int aux, i, j,row, col, num;
    FILE *fl;
    if (type_of(file) == TXT){
        fl = fopen(file, "r");
        if (fl == NULL){return INVALID_NULL_POINTER;}

        aux = tam_file(file, &row, &col);
        printf("%d %d", row,col);
        if(aux!=0){return UNDEFINED_ERROR;}
        *mat = mtz_create(row, col);

        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                fscanf(fl, "%d", &num);
                mtz_set(*mat, i,j, num);
            }
        }
        fclose(fl);
        return SUCCESS;

    }else if(type_of(file) == IMM){
        fl = fopen(file, "rb");
        if (fl == NULL){return INVALID_NULL_POINTER;}
        aux = tam_file(file, &row, &col);
        if(aux!=0){return UNDEFINED_ERROR;}
        printf("%d %d", row,col);
        
        printf("sdasd %d %d", row,col);
        *mat = mtz_create(row, col);
    
        for (i = 0; i < row; i++){
            for (j = 0; j < col; j++){
                fread(&num, sizeof(int), 1, fl);
                mtz_set(*mat, i, j, num);
            }
        }
        fclose(fl);
        return SUCCESS;
    }
}

int type_of(char *file){
    char *c;
    c = strstr(file, ".");  
    if (strcmp(c, ".txt") == 0){
        return TXT;
    }
    else if (strcmp(c, ".imm") == 0){
        return IMM;
    }else{
        return INCOMPATIBLE_TYPE;
    }
}

int convert(char *c1, char *c2){
    if (type_of(c1) == TXT && type_of(c2) == IMM){
    mtz *mat;
    int aux;
    aux = open_file(c1, &mat);
    if (aux == SUCCESS){
        FILE *fl;
        int num, i, j, row, col;
        mtz_grow(mat, &row);
        mtz_gcol(mat, &col);
    
        fl = fopen(c2, "wb");
        if (fl == NULL){return INVALID_NULL_POINTER;}
        
        for (i = 0; i < row; i++){
            for (j = 0; j < col; j++){
                mtz_get(mat, i, j, &num);
                fwrite(&num, sizeof(int), 1, fl);
            }
            fprintf(fl, "\n");
        }
        fclose(fl);
        return SUCCESS;
    }return UNDEFINED_ERROR;
    }
    return INCOMPATIBLE_TYPE;
}
int segment(int thr, char *c1, char *c2){//Incompleto
    mtz *mat;
    
    int num, aux, i, j, row, col;

    aux = open_file(c1, &mat);
    if (aux != SUCCESS){return UNDEFINED_ERROR;}

    mtz_grow(mat, &row);
    mtz_gcol(mat, &col);
    
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            mtz_get(mat, i, j, &num);

            if (num < thr){
                mtz_set(mat, i, j, 0);
            }else{
                mtz_set(mat, i, j, 1);
            }
        }
    }
    set_mat(mat, c2);
    mtz_free(mat);

    return SUCCESS;
}
int set_mat(mtz *mat, char *res){ //fazer o IMM
    FILE *file;
    int num, aux, i, j, row, col;
    mtz_grow(mat, &row);
    mtz_gcol(mat, &col);

    if (type_of(res) == TXT){
        file = fopen(res, "w");
        if (file == NULL){return INVALID_NULL_POINTER;}

        for (i = 0; i < row; i++){
            for (j = 0; j < col; j++){
                mtz_get(mat, i, j, &num);
                fprintf(file, "%1d", num);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        return SUCCESS;
    }
}
int tam_file(char *file, int *l, int *c){
    FILE *fl;
    int aux, num = 0, row = 1, col = 0;
    char ch;

    if (type_of(file) == TXT){
        fl = fopen(file, "r");
        if (fl == NULL){return INVALID_NULL_POINTER;}

        while(!feof(fl)) {
        ch = fgetc(fl);
        if(ch == '\n') {
            row++; 
        } else {
            col++;
        }
        }
        *l = row; 
        *c = 3+(col/row)/4; // Precisa de correção
    
        fclose(fl);
        return SUCCESS;
    }
    else if (type_of(file) == IMM){ //Incompleto
        fl = fopen(file, "rb");
        if (fl == NULL){return INVALID_NULL_POINTER;}
 
        fclose(fl);
        return SUCCESS;
    }
    
}
    
