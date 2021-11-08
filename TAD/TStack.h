#ifndef _TStack_
#define _TStack_

#include "ponto.h"
#define MAX 100
#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4

typedef struct TStack TStack;

TStack *stack_create();
int stack_free(TStack *st);

int stack_push(TStack *st, struct ponto p);
int stack_pop(TStack *st);
int stack_top(TStack *st, struct ponto *p);

int stack_size(TStack *st);
int stack_print(TStack *st);
int stack_tam(TStack *st);
#endif