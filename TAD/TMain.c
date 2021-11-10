#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TMain.h"

int open_file(char *file, mtz **mat)
{ // Função para devolver uma matriz com os dados
    int aux;
    aux = set_arq(file, mat); // Atribui os dados do arquivo em uma matriz
    if (aux != SUCCESS)
    {
        return UNDEFINED_ERROR;
    }
    else
    {
        return SUCCESS;
    }
}

int type_of(char *file)
{ // Função para determinar o tipo do arquivo
    char *c;
    c = strstr(file, "."); // Encontra o ponto no nome do arquivo e atrabui ele e o restante na variável c
    if (strcmp(c, ".txt") == 0)
    { // Compara c com .txt e retorna a definição TXT caso seja verdade
        return TXT;
    }
    else if (strcmp(c, ".imm") == 0)
    { // Compara c com .imm e retorna a definição IMM caso seja verdade
        return IMM;
    }
    else
    {
        return INCOMPATIBLE_TYPE;
    }
}

int convert(char *c1, char *c2)
{ // Função para converter um arquivo .txt para .imm
    if (type_of(c1) == TXT && type_of(c2) == IMM)
    { // Verifica os tipos dos arquivos
        mtz *mat;
        int aux, nrow, ncol;
        aux = open_file(c1, &mat); // Abre o arquivo c1 a ser convertido e atribui seus dados a uma matriz
        if (aux == SUCCESS)
        {
            aux = set_mat(c2, mat);
            if (aux == SUCCESS)
            {
                return SUCCESS;
            }
            else
            {
                return UNDEFINED_ERROR;
            }
        }
        return UNDEFINED_ERROR;
    }
    return INCOMPATIBLE_TYPE;
}

int segment(int thr, char *c1, char *c2)
{ // Função para transformar os dados de um arquivo txt e/ou imm em 1 ou 0, dependendo de thr
    mtz *mat;
    int aux;
    aux = open_file(c1, &mat); // Abre o arquivo c1 a ser segmentado e atribui seus dados a uma matriz
    if (aux != SUCCESS)
    {
        return UNDEFINED_ERROR;
    }

    aux = seg(thr, c1, c2, mat); // Segmenta a matriz de c1
    if (aux != SUCCESS)
    {
        return UNDEFINED_ERROR;
    }

    aux = set_mat(c2, mat); // Atribui os dados da matriz no arquvivo c2
    if (aux != SUCCESS)
    {
        return UNDEFINED_ERROR;
    }

    aux = mtz_free(mat); // Libera a matriz
    if (aux != SUCCESS)
    {
        return UNDEFINED_ERROR;
    }

    return SUCCESS;
}

int seg(int thr, char *c1, char *c2, mtz *mat)
{ // Função para segmentar uma matriz
    int num, aux, i, j, row, col;

    aux = tam_file(c1, &row, &col); // Recebe a quantidade de linhas e colunas presentes no arquivo
    if (aux != 0)
    {
        return UNDEFINED_ERROR;
    }
    for (i = 0; i < row; i++)
    { // Percorre o arquivo e a matriz
        for (j = 0; j < col; j++)
        {
            mtz_get(mat, i, j, &num); // Lê os dados da matriz
            printf("", num);          // BUG
            if (num < thr)
            {                          // Se o dado for <= a thr..
                mtz_set(mat, i, j, 0); // ..transforma em 0..
            }
            else
            {
                mtz_set(mat, i, j, 1); //..se não transforma em 1
            }
        }
        mtz_set(mat, i, j, '\t'); // Adiciona '\t' após todo elemento
    }
    printf("\n"); // Adiciona '\n' no final de toda linha
    return SUCCESS;
}

int componentConnected(char *entrance, char *exit){
    int nrows, ncolumns;
    mtz *me, *ms;
    ms = mtz_create(nrows, ncolumns);
    if ((open_file(entrance, &me)) != SUCCESS)
    {
        return UNDEFINED_ERROR;
    }
    if ((mtz_gdata(me, &nrows, &ncolumns)) != SUCCESS)
        {
            return UNDEFINED_ERROR;
        }

    if ((compCon(me, ms)) == SUCCESS){
        if (convert (entrance, exit) == SUCCESS){
            return SUCCESS;
        }
        else{
            return UNDEFINED_ERROR;
        }
    }
    mtz_free(me);
    mtz_free(ms);
}

int compCon(mtz *matEntrance, mtz *matExit)
{
    int row, column;
    int img;
    int img_root;
    int label = 1;                  // sera usado para diferenciar
    TStack *stack = stack_create(); // fazendo uma pilha para comparar
    ponto p, p_att, p_aux;
    if (mtz_gdata(matEntrance, &row, &column) != SUCCESS)
        return UNDEFINED_ERROR;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        { // percorre toda a matriz
            p.x = i;
            p.y = j;
            mtz_set(matEntrance, p.x, p.y, img);  // pega dados matriz de entrada
            mtz_get (matExit, p.x, p.y, &img_root); // pega dados matriz de saida
            if ((img == 1) && (img_root == 0))
            {
                mtz_set(matEntrance, p.x, p.y, label); // colocando o label na pos (i,j) matriz saida
                stack_push(stack, p);                                // anexa o ponto na pilha
                while (stack_size(stack) != 0)                       // se for diferente de 0 vou buscar o prox dos conexos
                {
                    stack_find(stack, &p_att);  // pega prox item
                    stack_pop(stack);           // retira item da pilha
                    for (int l = 0; l < 4; l++) // verifica os vizinhos do atual ponto
                    {
                        p_aux.x = p.x;
                        p_aux.y = p.y;
                        p.x = p_att.x - (l == 0) + (l == 1);                 // d == 0 baixo, d == 1 cima
                        p.y = p_att.y - (l == 2) + (l == 3);                 //  d == 2 esquerda, d == 3 direita
                        mtz_get(matEntrance, p.x, p.y, &img);  // pega valores matriz entrada e coloca em img
                        mtz_get(matExit, p.x, p.y, &img_root); // pega valores da matriz saida e coloca em img_root 
                        if ((img == 1) && (img_root == 0))                   // verifica se os pontos não são 1 e não foi rotulado
                        {
                            mtz_get(matExit, p.x, p.y, label); // atribui o label a posição (i,j) da matriz saida
                            stack_push(stack, p);                             // empilha para verificar vizinhos no proximo laço
                        }
                        p.x = p_aux.x;
                        p.y = p_aux.y;
                    }
                }
                label++;
            }
        }
    }
    stack_free(stack);
    return SUCCESS;
}

int labirinto()
{

}

int lab()
{
}

int set_mat(char *file, mtz *mat)
{ // Função para atribuir os dados de uma matriz em um arquivo txt ou imm
    FILE *fl;
    int num, aux, i, j, row, col;
    mtz_grow(mat, &row); // Pega a quantidade de linhas da matriz
    mtz_gcol(mat, &col); // Pega a quantidade de colunas da matriz

    if (type_of(file) == TXT)
    {                          // Verifica se o arquivo é txt
        fl = fopen(file, "w"); // Abre o arquivo para escrita
        if (fl == NULL)
        {
            return INVALID_NULL_POINTER;
        }

        for (i = 0; i < row; i++)
        { // Percorre o arquivo e a matriz
            for (j = 0; j < col; j++)
            {
                mtz_get(mat, i, j, &num); // Lê os dados da matriz
                printf("");
                fprintf(fl, "%d ", num); // Coloca no arquivo
            }
            fprintf(fl, "\n"); // Coloca ao final de toda linha um '\n'
        }

        fclose(fl);
        return SUCCESS;
    }
    else if (type_of(file) == IMM)
    {                           // Verifica se o arquivo é imm
        fl = fopen(file, "wb"); // Abre o arquivo binário para escrita
        if (fl == NULL)
        {
            return INVALID_NULL_POINTER;
        }

        fwrite(&row, sizeof(int), 1, fl); // Atribui no arquivo c2 a quantidade de linhas
        fwrite(&col, sizeof(int), 1, fl); // Atribui no arquvio c2 a quantidade de colunas

        for (i = 0; i < row; i++){ // Percorre o arquivo e a matriz
            for (j = 0; j < col; j++){
                printf("");
                mtz_get(mat, i, j, &num);         // Lê os dados da matriz
                fwrite(&num, sizeof(int), 1, fl); // Coloca no arquivo
            }
            fprintf(fl, "\n"); // Coloca ao final de toda linha um '\n'
        }
        return SUCCESS;
    }
}

int tam_file(char *file, int *l, int *c)
{ // Função para determinar a quantidade de linhas e colunas de um arquivo .txt ou .imm
    FILE *fl;
    int aux, num = 0, row = 1, col = 1;
    char ch;

    if (type_of(file) == TXT)
    {                          // Verifica se o arquivo é txt
        fl = fopen(file, "r"); // Abre o arquivo para leitura
        if (fl == NULL)
        {
            return INVALID_NULL_POINTER;
        }
        char ch;

        while (!feof(fl))
        {                   // Enquanto não for o final do arquivo
            ch = fgetc(fl); // Lê o próximo caracter do arquivo
            if (ch == '\n')
            {          // Se for quebra de linha..
                row++; // ..adiciona uma linha na contagem..
            }
            else if (row == 1 && (ch == '\t' || ch == ' '))
            {          //..se a contagem de linha for 1 e o caracter for um tab ou um espaço..
                col++; //..adiciona uma coluna na contagem
            }
        }
        if (row == 0 || col == 0)
        {
            return UNDEFINED_ERROR;
        }
        *l = row; // Atribui a contagem de linha no retorno de linhas
        *c = col; // Atribui a contagem de colunas no retorno de colunas

        fclose(fl);
        return SUCCESS;
    }
    else if (type_of(file) == IMM)
    {                                 // Verifica se o arquivo é imm
        FILE *fl = fopen(file, "rb"); // Abre o arquivo binário para leitura
        if (fl == NULL)
        {
            return INVALID_NULL_POINTER;
        }

        fread(&row, sizeof(int), 1, fl); // Lê a quantidade de linhas (atribuído na função convert)
        fread(&col, sizeof(int), 1, fl); // Lê a quantidade de colunas (atribuído na função convert)
        if (row <= 1 || col <= 1)
        {
            return UNDEFINED_ERROR;
        }
        *l = row; // Atribui a contagem de linha no retorno de linhas
        *c = col; // Atribui a contagem de colunas no retorno de colunas

        fclose(fl);
        return SUCCESS;
    }
}

int set_arq(char *file, mtz **mat)
{ // Função para atribuir os dados de um arquivo em uma matriz
    FILE *fl;
    int aux, num, row, col;
    if (type_of(file) == TXT)
    {                          // Verifica se o arquivo é txt
        fl = fopen(file, "r"); // Abre o arquivo para leitura
        if (fl == NULL)
        {
            return INVALID_NULL_POINTER;
        }

        aux = tam_file(file, &row, &col); // Recebe a quantidade de linhas e colunas presentes no arquivo
        if (aux != 0)
        {
            return UNDEFINED_ERROR;
        }

        *mat = mtz_create(row, col); // Cria uma matriz

        for (int i = 0; i < row; i++)
        { // Percorre o arquivo e a matriz
            for (int j = 0; j < col; j++)
            {
                fscanf(fl, "%d", &num);   // Lê os dados do arquivo
                mtz_set(*mat, i, j, num); // Coloca na matriz
            }
        }
        fclose(fl); // Fecha o arquivo
        return SUCCESS;
    }
    else if (type_of(file) == IMM)
    {                           // Verifica se o arquivo é imm
        fl = fopen(file, "rb"); // Abre o arquivo binario para leitura
        if (fl == NULL)
        {
            return INVALID_NULL_POINTER;
        }
        aux = tam_file(file, &row, &col); // Recebe a quantidade de linhas e colunas presentes no arquivo
        if (aux != 0)
        {
            return UNDEFINED_ERROR;
        }

        *mat = mtz_create(row, col); // Cria uma matriz

        for (int i = 0; i < row; i++)
        { // Percorre o arquivo e a matriz
            for (int j = 0; j < col; j++)
            {
                fread(&num, sizeof(int), 1, fl); // Lê os dados do arquivo
                mtz_set(*mat, i, j, num);        // Coloca na matriz
            }
        }
        fclose(fl); // Fecha o arquivo
        return SUCCESS;
    }
}
