#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/bruta.h"

int forcaBruta(char sequencia[], char pedra[]) {
  int tamanhoSequencia = strlen(sequencia);  // tamanho da sequência
  int tamanhoPedra = strlen(pedra);  // tamanho da pedra

  // loop que percorre todas as posições na pedra
  for (int i = 0; i <= tamanhoPedra - tamanhoSequencia; i++) {
    int j;
    
    // loop que percorre os caracteres da sequencia
    for (j = 0; j < tamanhoSequencia; j++) {
      // compara os caracteres, se achar algum diferente, o loop é interrompido
      if (pedra[i + j] != sequencia[j]) {
        break; // se for diferente interrompe o segundo for
      }
    }
    
    // verifica se todos os caracteres da sequência correspondem aos caracteres correspondentes da pedra
    if (j == tamanhoSequencia) {
      // uma sequência foi encontrada na posição i
      return i + 1;  // retorna a posição inicial da sequencia na pedra
    }
  }

  // nenhum casamento de sequência foi encontrado na pedra
  return -1;
}
