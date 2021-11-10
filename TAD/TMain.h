#define SUCCESS 0
#define TXT 10
#define IMM 20
#define INVALID_NULL_POINTER -1
#define INCOMPATIBLE_TYPE -2
#define UNDEFINED_ERROR -3
#include "Matriz.h"
#include "TStack.h"


int open_file(char *file, mtz **mat); // OK
int convert(char *c1, char *c2); // OK
int segment(int thr, char name1[], char name2[]); // Com Bug

int tam_file(char *file, int *l, int *c); // OK
int type_of(char *file); // OK
int set_mat(char *file,mtz *mat); // OK
int set_arq(char *file, mtz **mat); // OK

int seg(int thr, char *c1, char *c2, mtz *mat); // Com Bug


int componentConnected(char *entrance, char *exit);

int compCon(mtz *matEntrance, mtz *matExit);