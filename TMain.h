#define SUCCESS 0
#define TXT 10
#define IMM 20
#define INVALID_NULL_POINTER -1
#define INCOMPATIBLE_TYPE -2
#define UNDEFINED_ERROR -3
#include "Matriz.h"


int open_file(char *file, mtz **mat);
int convert(char *c1, char *c2);
int segment(int thr, char name1[], char name2[]);

int tam_file(char *file, int *l, int *c);
int type_of(char *file);
int set_mat(mtz *mat, char *res);

