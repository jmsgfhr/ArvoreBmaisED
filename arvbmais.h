#ifndef ARVBMAIS_H
#define ARVBMAIS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"

typedef struct arvbm{
  int nchaves, folha, *chave;
  struct arvbm **filho, *prox;
  TPizza **pizza;
}TABM;

TABM *cria(int t);

TABM *busca(TABM *a, int mat);

void imprime(TABM *a, int andar);

TABM *insere(TABM *T, int mat, int t);

TABM *inicializa(void);

#endif