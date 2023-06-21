#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/resource.h>
#include <sys/time.h>

#include "kmp.c"
#include "bruta.c" 
#include "shiftand.c"

#define MAX_SEQUENCIA 101
#define MAX_PEDRA 10001

// inverter uma string
void inverterString(char str[]) {
  int i = 0;
  int j = strlen(str) - 1;

  while (i < j) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

// verificar se a sequência é circular
int sequenciaCircular(char sequencia[], char pedra[], int estrategia) {
  int tamanhoPedra = strlen(pedra);

  // concatena a pedra para fazer uma análise circular
  char *pedraConcatenada = (char *)malloc((tamanhoPedra * 2 + 1) * sizeof(char));
  strcpy(pedraConcatenada, pedra);
  strcat(pedraConcatenada, pedra);

  int posicao = -1;

  // vetor de ponteiros para as funções dos algoritmos
  int (*funcoes[])(char *, char *) = {shiftAnd, forcaBruta, kmp};
  if (estrategia >= 1 && estrategia <= 3) {
    // chama a função do algoritmo selecionado
    posicao = funcoes[estrategia - 1](sequencia, pedraConcatenada);
  } else {
    printf("\nEstratégia inválida!\n");
  }

  free(pedraConcatenada);

  return posicao;
}

// processa os casos de teste da entrada e executa a estratégia selecionada
void executarEstrategia(char *arquivoEntrada, int estrategia) {
  FILE *entrada = fopen(arquivoEntrada, "r");

  if (entrada == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    exit(1);
  }

  // cria o nome do arquivo de saída (entrada + .out)
  char arquivoSaida[100];
  strcpy(arquivoSaida, arquivoEntrada);
  char *extensao = strrchr(arquivoSaida, '.');
  if (extensao != NULL) {
    *extensao = '\0';
  }
  strcat(arquivoSaida, ".out");
  FILE *saida = fopen(arquivoSaida, "w");

  if (saida == NULL) {
    printf("Erro ao abrir o arquivo de saída.\n");
    fclose(entrada);
    exit(1);
  }

  int T;
  fscanf(entrada, "%d", &T);

  for (int i = 0; i < T; i++) {
    char *sequencia = (char *)malloc(MAX_SEQUENCIA * sizeof(char));
    char *pedra = (char *)malloc(MAX_PEDRA * sizeof(char));

    fscanf(entrada, "%s %s", sequencia, pedra);

    int posicao = -1;

    int (*funcoes[])(char *, char *) = {shiftAnd, forcaBruta, kmp};
    if (estrategia >= 1 && estrategia <= 3) {
      // chama a função do algoritmo selecionado
      posicao = funcoes[estrategia - 1](sequencia, pedra);
    } else {
      printf("Estratégia inválida.\n");
      fclose(entrada);
      fclose(saida);
      free(sequencia);
      free(pedra);
      exit(1);
    }

    if (posicao != -1) {
      fprintf(saida, "S %d\n", posicao);
    } else {
      // verificar sequência circular
      int posicaoCircular = sequenciaCircular(sequencia, pedra, estrategia);

      if (posicaoCircular != -1) {
        fprintf(saida, "S %d\n", posicaoCircular);
      } else {
        // verificar sequência invertida
        char *pedraInvertida = (char *)malloc(MAX_PEDRA * sizeof(char));
        int tamanhoPedra = strlen(pedra);

        // inverter pedra
        for (int j = 0; j < tamanhoPedra; j++) {
          pedraInvertida[j] = pedra[tamanhoPedra - j - 1];
        }

        pedraInvertida[tamanhoPedra] = '\0';

        int posicaoInvertida = -1;

        if (estrategia >= 1 && estrategia <= 3) {
          // chama a função do algoritmo selecionado
          posicaoInvertida = funcoes[estrategia - 1](sequencia, pedraInvertida);
        } else {
          printf("\nEstratégia inválida!\n");
          fclose(entrada);
          fclose(saida);
          free(sequencia);
          free(pedra);
          free(pedraInvertida);
          exit(1);
        }

        if (posicaoInvertida != -1) {
          fprintf(saida, "S %d\n", tamanhoPedra - posicaoInvertida + 1);
        } else {
          fprintf(saida, "N\n");
        }

        free(pedraInvertida);
      }
    }

    free(sequencia);
    free(pedra);
  }

  fclose(entrada);
  fclose(saida);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("./executavel arquivo_entrada.txt estrategia\n");
    return 1;
  }
  char *arquivoEntrada = argv[1];
  int estrategia = atoi(argv[2]);

  executarEstrategia(arquivoEntrada, estrategia);

  switch (estrategia) {
    case 1:
      printf("\n-- SHIFT AND --\n");
      break;
    case 2:
      printf("\n-- FORÇA BRUTA --\n");
      break;
    case 3:
      printf("\n-- KMP --\n");
      break;
    default:
      break;
  }

  // obter o tempo atual
  struct timeval tempo;
  gettimeofday(&tempo, NULL);
  printf("Tempo até hoje: %ld.%lds\n", tempo.tv_sec, tempo.tv_usec);

  // obter o tempo de uso da CPU
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  printf("Tempo de uso do usuário: %ld.%05lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
  printf("Tempo de uso do sistema: %ld.%05lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);

  return 0;
}
