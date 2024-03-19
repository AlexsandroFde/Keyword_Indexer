#ifndef LIB_H
#define LIB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max_palavras 1000
#define max_palavra_tam 50

typedef struct { // Estrutura para armazenar as palavras e suas frequencias
  char palavra[max_palavra_tam];
  int linhas[max_palavras];
  int count;
} IndiceRemissivo;

int palavraExiste(IndiceRemissivo index[], char *word);
void addPalavra(IndiceRemissivo index[], char *word, int lineNumber);

#endif