#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/shiftand.h"

int shiftAnd(char sequencia[], char pedra[]) {
  int i;
  int posicao = -1;  // posição inicial da sequência na pedra
  int encontrado = 0;  // sequencia encontrada
  int tamanhoSequencia = strlen(sequencia);  // tamanho da sequência
  int tamanhoPedra = strlen(pedra);  // tamanho da pedra
  unsigned long long mascara[256] = {0};  // tabela de máscara para cada caractere
  unsigned long long estado = 0;  // estado atual

  // calcula as máscaras
  for (i = 0; i < tamanhoSequencia; i++) {
    mascara[(unsigned char)sequencia[i]] |= (1ull << i);  // define a mascara para o caractere correspondente
  }

  // faz a busca utilizando o algoritmo shift and
  for (i = 0; i < tamanhoPedra; i++) {
    estado = ((estado << 1) | 1ull) & mascara[(unsigned char)pedra[i]];  // atualiza o estado de acordo com a mascara

    if (estado & (1ull << (tamanhoSequencia - 1))) {
      // verifica a sequência completa
      int j;
      for (j = 0; j < tamanhoSequencia; j++) {
        if (pedra[i - tamanhoSequencia + 1 + j] != sequencia[j]) {
          break;
        }
      }

      if (j == tamanhoSequencia) {
        // quando a sequência é encontrada na posição i - tamanhoSequencia + 1
        posicao = i - tamanhoSequencia + 1;
        encontrado = 1;
        break;
      }
    }
  }

  if (encontrado) {
    return posicao + 1;
  } else {
    return -1;  // quando a sequencia nao é encontrada
  }
}
