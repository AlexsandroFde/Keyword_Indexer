#include "../include/lib.h"

int main() {
  FILE *arq;
  FILE *arqKeys;
  char nomeArq[50];
  char palavra[max_palavra_tam];
  IndiceRemissivo indice[max_palavras];
  char palavraKey[max_palavra_tam][max_palavra_tam];
  int linha = 1;
  for (int i = 0; i < max_palavras; i++) { // Inicializa o índice remissivo com palavras vazias
    strcpy(indice[i].palavra, "");
    indice[i].count = 0;
  }
  printf("Digite o nome do arquivo contendo um texto: ");
  fgets(nomeArq, sizeof(nomeArq), stdin); // Lê o nome do arquivo
  nomeArq[strlen(nomeArq) - 1] = '\0'; // Remove o caractere de nova linha
  arq = fopen(nomeArq, "r");
  if (arq == NULL) { // Caso o arquivo não exista
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  printf("Digite o nome do arquivo contendo as palavras-chave do texto: ");
  fgets(nomeArq, sizeof(nomeArq), stdin); // Lê o nome do arquivo
  nomeArq[strlen(nomeArq) - 1] = '\0'; // Remove o caractere de nova linha
  arqKeys = fopen(nomeArq, "r");
  if (arqKeys == NULL) { // Caso o arquivo não exista
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  int keyCount = 0;
  while (fscanf(arqKeys, "%s", palavra) != EOF) { // Lê as palavras-chave do arquivo
    int len = strlen(palavra);
    if (ispunct(palavra[len - 1])) { // Remove o caractere de pontuação do final da palavra
      palavra[len - 1] = '\0';
    }
    strcpy(palavraKey[keyCount], palavra);
    keyCount++;
  }
  int c;
  while ((c = fgetc(arq)) != EOF) { // Lê o arquivo caractere por caractere
    if (c == '\n') {
      linha++;
    } else if (isalpha(c)) {
      ungetc(c, arq);
      fscanf(arq, "%s", palavra);
      int len = strlen(palavra);
      if (ispunct(palavra[len - 1])) { // Remove o caractere de pontuação do final da palavra
        palavra[len - 1] = '\0';
      }
      for (int i = 0; i < keyCount; i++) { // Verifica se a palavra-chave está no arquivo
        if (strcmp(palavra, palavraKey[i]) == 0) {
          addPalavra(indice, palavra, linha);
          break;
        }
      }
    }
  }
  printIndice(indice); // Imprime o índice remissivo
  fclose(arq); // Fecha o arquivo
  fclose(arqKeys); // Fecha o arquivo das chaves
  return 0;
}