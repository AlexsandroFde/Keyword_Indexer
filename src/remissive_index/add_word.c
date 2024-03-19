#include "../include/lib.h"

void addPalavra(IndiceRemissivo index[], char *word, int lineNumber) {
  // Adiciona a palavra e a linha ao índice remissivo
  for (int i = 0; i < max_palavras; i++) {
    if (index[i].count == 0 || strcmp(index[i].palavra, word) > 0) {
      if (!palavraExiste(index, word)) { // Verifica se a palavra já existe no índice
        for (int j = max_palavras - 1; j > i; j--) { // Move as palavras para abrir espaço para a nova palavra
          strcpy(index[j].palavra, index[j - 1].palavra);
          memcpy(index[j].linhas, index[j - 1].linhas, sizeof(index[j].linhas));
          index[j].count = index[j - 1].count;
        }
        strcpy(index[i].palavra, word); // Insere a nova palavra na posição correta no índice
        index[i].linhas[0] = lineNumber; // Armazena apenas a linha atual
        index[i].count = 1;
      }
      break;
    } else if (strcmp(index[i].palavra, word) == 0) { 
      index[i].linhas[index[i].count] = lineNumber; // Adiciona a linha atual ao vetor de linhas da palavra
      index[i].count++; // Incrementa o contador de linhas da palavra
      break;
    }
  }
} // Fim addPalavra