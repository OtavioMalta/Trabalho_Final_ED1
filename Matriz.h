#ifndef _Matrizh_
#define _Matrizh_

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define mtz_NOT_ALlOCATED -6

typedef struct mtz mtz;

mtz *mtz_create(int row, int col);
int mtz_free(mtz *mat);
void mtz_print(mtz *mat);

int mtz_set(mtz *mat, int i, int j, int num);
int mtz_get(mtz *mat, int i, int j, int *num);

int mtz_gcol(mtz *mat, int *col);
int mtz_grow(mtz *mat, int *row);
int mtz_gdata(mtz *mat, int *row, int *col);

#endif