#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TMain.h"

int open_file(char *file, mtz **mat){ // Função para abrir um arquivo .txt ou .imm -> devolve uma matriz com os dados
    int aux, i, j,row, col, num;
    FILE *fl;
    if (type_of(file) == TXT){ // Verifica se o arquivo é txt
        fl = fopen(file, "r"); // Abre o arquivo para leitura
        if (fl == NULL){return INVALID_NULL_POINTER;}

        aux = tam_file(file, &row, &col); // Recebe a quantidade de linhas e colunas presentes no arquivo
        if(aux!=0){return UNDEFINED_ERROR;}

        *mat = mtz_create(row, col); // Cria uma matriz

        for (int i = 0; i < row; i++){ // Percorre o arquivo e a matriz
            for (int j = 0; j < col; j++){
                fscanf(fl, "%d", &num); // Lê os dados do arquivo
                mtz_set(*mat, i,j, num); // Coloca na matriz
            }
        }
        fclose(fl); // Fecha o arquivo
        return SUCCESS;

    }else if(type_of(file) == IMM){ // Verifica se o arquivo é imm
        fl = fopen(file, "rb"); // Abre o arquivo binario para leitura
        if (fl == NULL){return INVALID_NULL_POINTER;}
        aux = tam_file(file, &row, &col); // Recebe a quantidade de linhas e colunas presentes no arquivo
        if(aux!=0){return UNDEFINED_ERROR;}
        
        *mat = mtz_create(row, col); // Cria uma matriz
    
        for (i = 0; i < row; i++){ // Percorre o arquivo e a matriz
            for (j = 0; j < col; j++){
                fread(&num, sizeof(int), 1, fl); // Lê os dados do arquivo
                mtz_set(*mat, i, j, num); // Coloca na matriz
            }
        }
        fclose(fl); // Fecha o arquivo
        return SUCCESS;
    }
}

int type_of(char *file){ // Função para determinar o tipo do arquivo
    char *c;
    c = strstr(file, "."); // Encontra o ponto no nome do arquivo e atrabui ele e o restante na variável c
    if (strcmp(c, ".txt") == 0){ // Compara c com .txt e retorna a definição TXT caso seja verdade
        return TXT;
    }
    else if (strcmp(c, ".imm") == 0){ // Compara c com .imm e retorna a definição IMM caso seja verdade
        return IMM;
    }else{
        return INCOMPATIBLE_TYPE;
    }
}

int convert(char *c1, char *c2){ // Função para converter um arquivo .txt para .imm
    if (type_of(c1) == TXT && type_of(c2) == IMM){ // Verifica os tipos dos arquivos
    mtz *mat;
    int aux,nrow,ncol;
    aux = open_file(c1, &mat); // Abre o arquivo c1 a ser convertido e atribui seus dados a uma matriz
    if (aux == SUCCESS){
        FILE *fl;
        int num, i, j;;
        mtz_grow(mat, &nrow); // Pega a quantidade de linhas da matriz c1
        mtz_gcol(mat, &ncol); // Pega a quantidade de colunas da matriz c1
        

        fl = fopen(c2, "wb"); // Abre o arquivo c2 a ser convertido para escrita binária
        if (fl == NULL){return INVALID_NULL_POINTER;}

        fwrite(&nrow, sizeof(int), 1, fl); // Atribui no arquivo c2 a quantidade de linhas
        fwrite(&ncol, sizeof(int), 1, fl); // Atribui no arquvio c2 a quantidade de colunas
        
        for (i = 0; i < nrow; i++){ // Percorre o arquivo e a matriz
            for (j = 0; j < ncol; j++){
                mtz_get(mat, i, j, &num); // Lê os dados da matriz
                fwrite(&num, sizeof(int), 1, fl); // Coloca no arquivo
            }
            fprintf(fl, "\n"); // Coloca ao final de toda linha um '\n'
        }
        fclose(fl);
        return SUCCESS;
    }return UNDEFINED_ERROR;
    }
    return INCOMPATIBLE_TYPE;
}
int segment(int thr, char *c1, char *c2){ // Função para transformar os dados de um arquivo txt e/ou imm em 1 ou 0, dependendo de thr
    mtz *mat;
    
    int num, aux, i, j, row, col;

    aux = open_file(c1, &mat); // Abre o arquivo c1 a ser segmentado e atribui seus dados a uma matriz
    if (aux != SUCCESS){return UNDEFINED_ERROR;}

    mtz_grow(mat, &row); // Pega a quantidade de linhas da matriz c1
    mtz_gcol(mat, &col); // Pega a quantidade de colunas da matriz c1
    
    for (i = 0; i < row; i++){ // Percorre o arquivo e a matriz
        for (j = 0; j < col; j++){
            mtz_get(mat, i, j, &num); // Lê os dados da matriz

            if (num < thr){ // Se o dado for <= a thr..
                mtz_set(mat, i, j, 0); // ..transforma em 0..
            }else{
                mtz_set(mat, i, j, 1); //..se não transforma em 1
            }
        }
    }
    set_mat(mat, c2); // Atribui os dados da matriz no arquvivo c2
    mtz_free(mat);

    return SUCCESS;
}
int set_mat(mtz *mat, char *res){ // Função para atribuir os dados de uma matriz em um arquivo txt ou imm
    FILE *fl;
    int num, aux, i, j, row, col;
    mtz_grow(mat, &row); // Pega a quantidade de linhas da matriz c1
    mtz_gcol(mat, &col); // Pega a quantidade de colunas da matriz c1

    if (type_of(res) == TXT){ // Verifica se o arquivo é txt
        fl = fopen(res, "w"); // Abre o arquivo para escrita
        if (fl == NULL){return INVALID_NULL_POINTER;}

        for (i = 0; i < row; i++){ // Percorre o arquivo e a matriz
            for (j = 0; j < col; j++){
                mtz_get(mat, i, j, &num); // Lê os dados da matriz
                fprintf(fl, "%1d", num); // Coloca no arquivo
            }
            fprintf(fl, "\n"); // Coloca ao final de toda linha um '\n'
        }
        fclose(fl);
        return SUCCESS;
    }else if(type_of(res) == IMM){ // Verifica se o arquivo é imm
        fl = fopen(res, "wb"); // Abre o arquivo binário para escrita
        if (fl == NULL){return INVALID_NULL_POINTER;}
        fwrite( mat, sizeof(mat), 1, fl ) ; // Coloca todos os dados da matriz no arquivo
        fclose(fl);
        return SUCCESS;
    }
}
int tam_file(char *file, int *l, int *c){ // Função para determinar a quantidade de linhas e colunas de um arquivo .txt ou .imm
    FILE *fl;
    int aux, num = 0, row = 1, col = 1;
    char ch;

    if (type_of(file) == TXT){ // Verifica se o arquivo é txt
        fl = fopen(file, "r"); // Abre o arquivo para leitura
        if (fl == NULL){return INVALID_NULL_POINTER;}
        char ch;
        
        while(!feof(fl)) {// Enquanto não for o final do arquivo
        ch = fgetc(fl); // Lê o próximo caracter do arquivo
        if(ch == '\n') { // Se for quebra de linha..
            row++; // ..adiciona uma linha na contagem..
        } else if (row == 1 && (ch == '\t' || ch == ' ')){ //..se a contagem de linha for 1 e o caracter for um tab ou um espaço..
            col++; //..adiciona uma coluna na contagem
        }
        }
        *l = row; // Atribui a contagem de linha no retorno de linhas
        *c = col; // Atribui a contagem de colunas no retorno de colunas
    
        fclose(fl);
        return SUCCESS;
    }
    else if (type_of(file) == IMM){ // Verifica se o arquivo é imm
        FILE *fl = fopen(file, "rb"); // Abre o arquivo binário para leitura
        if (fl == NULL){return INVALID_NULL_POINTER;}
        int nrow, ncol;

        fread(&nrow, sizeof(int), 1, fl); // Lê a quantidade de linhas (atribuído na função convert)
        fread(&ncol, sizeof(int), 1, fl); // Lê a quantidade de colunas (atribuído na função convert)
        
        *l = nrow; // Atribui a contagem de linha no retorno de linhas
        *c = ncol; // Atribui a contagem de colunas no retorno de colunas
        
        fclose(fl);
        return SUCCESS;
    }
    
}
    
