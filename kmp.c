#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/kmp.h"

int kmp(char sequencia[], char pedra[]) {
  int tamanhoSequencia = strlen(sequencia);  // tamanho da sequência
  int tamanhoPedra = strlen(pedra);  // tamanho da pedra

  if (tamanhoSequencia == 0) {
    // sequência vazia, retorna 0
    return 0;
  }

  int *vpi = (int *)malloc(tamanhoSequencia * sizeof(int));  // vetor que armazena os valores do prefixo e do sufixo
  int i = 1, j = 0;

  vpi[0] = 0;  // valor de prefixo e sufixo

  // cria um vetor de prefixo e sufixo usando o KMP
  while (i < tamanhoSequencia) {
    if (sequencia[i] == sequencia[j]) {
      j++;
      vpi[i] = j;  // armazena os valores na posição atual
      i++;
    } else {
      if (j != 0) {
        j = vpi[j - 1];  // atualiza o valor do prefixo e do sufixo baseado no anterior
      } else {
        vpi[i] = 0;
        i++;
      }
    }
  }

  i = 0;
  j = 0;

  // busca da sequência na pedra usando o vetor de prefixo e sufixo
  while (i < tamanhoPedra) {
    if (sequencia[j] == pedra[i]) {
      j++;
      i++;
    }

    if (j == tamanhoSequencia) {
      // sequência encontrada na posição i - j
      free(vpi);  // libera a memória alocada
      return i - j + 1;  // retorna a posição inicial da sequência na pedra

    } else if (i < tamanhoPedra && sequencia[j] != pedra[i]) {
      if (j != 0) {
        j = vpi[j - 1];  // atualiza o valor do prefixo e do sufixo baseado no anterior
      } else {
        i++;
      }
    }
  }

  /* mesmo se a sequência não for encontrada, a memória alocada para o vetor de prefixo e sufixo também é liberada, e a função retorna -1.*/
  free(vpi); 
  return -1;
}