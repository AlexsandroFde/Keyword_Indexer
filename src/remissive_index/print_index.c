#include "../include/lib.h"

void printIndice(IndiceRemissivo index[]) {
  // Exibe o índice remissivo
  printf("Indice Remissivo:\n");
  for (int i = 0; i < max_palavras && index[i].count > 0; i++) {
    printf("%s: ", index[i].palavra); // Exibe a palavra
    for (int j = 0; j < index[i].count; j++) {
      printf("%d ", index[i].linhas[j]); // Exibe as linhas da palavra
    }
    printf("\n");
  }
} // Fim printIndice