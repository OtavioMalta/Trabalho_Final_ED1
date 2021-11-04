#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
struct mtz{
    int *data;
    int row;
    int col;
};

mtz *mtz_create(int row, int col){
    if (col < 1 || row < 1){return NULL;}

    mtz *aux;
    aux = malloc(sizeof(mtz));
    if (aux == NULL){return NULL;}

    aux->col = col;
    aux->row = row;
    aux->data = malloc((col*row)*sizeof(int));

    if (aux->data==NULL){
        free(aux);
        return NULL;}
    return aux;
}

int mtz_free(mtz *mat){
    if (mat == NULL){return INVALID_NULL_POINTER;}
    free(mat->data);
    free(mat);
    return SUCCESS;
}

void mtz_print(mtz *mat){
    int aux;
    for (int i = 0; i < mat->row; i++){
        for (int j = 0; j < mat->col; j++) {
            mtz_get(mat, i,j, &aux);
            printf("%d\t", aux);
        }
        printf("\n");
    }
}

int mtz_set(mtz *mat, int i, int j, int num){
    if (mat == NULL){return INVALID_NULL_POINTER;}
    if (i < 0 || j < 0){return OUT_OF_RANGE;}
    mat->data[j * mat->row + i] = num;
    return SUCCESS;
}

int mtz_get(mtz *mat, int i, int j, int *num){
    if (mat == NULL){return INVALID_NULL_POINTER;}
    if (i < 0 || j < 0){return OUT_OF_RANGE;}
    *num = mat->data[j * mat->row + i];
    return SUCCESS;
}

int mtz_gdata(mtz *mat, int *row, int *col){
    if (mat == NULL || col == NULL || row == NULL){return INVALID_NULL_POINTER;}
    *col = mat->col;
    *row = mat->row;
    return SUCCESS;
}

int mtz_gcol(mtz *mat, int *col){
    if (mat == NULL || col == NULL){return INVALID_NULL_POINTER;}
    *col = mat->col;
    return SUCCESS;
}

int mtz_grow(mtz *mat, int *row){
    if (mat == NULL || row == NULL){return INVALID_NULL_POINTER;}
    *row = mat->row;
    return SUCCESS;
}