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

int palavraExiste(IndiceRemissivo index[], char *word) {
  // Verifica se a palavra já existe no índice
  for (int i = 0; i < max_palavras; i++) {
    if (strcmp(index[i].palavra, word) == 0) {
      return 1; // Palavra encontrada no índice
    }
  }
  return 0; // Palavra não encontrada
} // Fim palavraExiste

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

void printIndice(IndiceRemissivo index[]) {
  // Exibe o índice remissivo
  printf("Índice Remissivo:\n");
  for (int i = 0; i < max_palavras && index[i].count > 0; i++) {
    printf("%s: ", index[i].palavra); // Exibe a palavra
    for (int j = 0; j < index[i].count; j++) {
      printf("%d ", index[i].linhas[j]); // Exibe as linhas da palavra
    }
    printf("\n");
  }
} // Fim printIndice

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