#include "../include/lib.h"

int palavraExiste(IndiceRemissivo index[], char *word) {
  // Verifica se a palavra já existe no índice
  for (int i = 0; i < max_palavras; i++) {
    if (strcmp(index[i].palavra, word) == 0) {
      return 1; // Palavra encontrada no índice
    }
  }
  return 0; // Palavra não encontrada
} // Fim palavraExiste