#include<stdio.h>
#include<stdlib.h>
#include"TStack.h"
typedef struct node node;

struct TStack{
    int tam;
    node *head;
};

struct node{
    node *next;
    ponto data;
};

int TStack_tam(TStack *st){
    if(st==NULL){return INVALID_NULL_POINTER;}
    return st->tam;
}

TStack *TStack_create(){
    TStack *st;
    st = malloc(sizeof(TStack));
    if(st != NULL){
        st->tam = 0;
        st->head = NULL;
    }
    return st;
}

int  TStack_free(TStack *st){
    node *no, *no2;

    if(st==NULL){return INVALID_NULL_POINTER;}

    if(st->tam >= 1){
        no = st->head;
        while(no != NULL){
            no2 = no;
            no = no->next;
            free(no2);
        }
    }
    free(st);
    return SUCCESS;
}

int TStack_print(TStack *st){
    node *no;
    if(st==NULL){return INVALID_NULL_POINTER;}
    if(st->tam == 0){return ELEM_NOT_FOUND;}

    no = st->head;
    while(no != NULL){
        printf("X -> %d\n", no->data.x);
        printf("Y -> %d\n\n", no->data.y);
        no = no->next;
    }
    return SUCCESS;
}

int TStack_pop(TStack *st){
    node *no;

    if(st==NULL){return INVALID_NULL_POINTER;}

    if(st->tam <= 0){return OUT_OF_RANGE;}

    if(st->tam == 1){
        st->tam--;
        free(st->head);
        st->head = NULL;
    }else{
        no = st->head->next;
        free(st->head);
        st->head = no;
        st->tam--;
    }
        return SUCCESS;
}

int TStack_top(TStack *st, ponto *p){

    if(st==NULL){return INVALID_NULL_POINTER;}

    if(st->tam == 0){return ELEM_NOT_FOUND;}
    *p = st->head->data;
    return SUCCESS;
}

int TStack_push(TStack *st, ponto p){
    node *no;

    if(st==NULL){return INVALID_NULL_POINTER;}
    no = malloc(sizeof(node));
    
    if(no==NULL){return OUT_OF_MEMORY;}

    no->data = p;
    no->next = NULL;

    if(st->tam == 0){
        st->tam++;
        st->head = no; 
    }else{
        st->tam++;
        no->next = st->head;
        st->head = no;
    }
    return SUCCESS;
}