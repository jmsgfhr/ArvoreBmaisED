#ifndef LISTA_NOS_INTERNOS_H
#define LISTA_NOS_INTERNOS_H

#include "no_interno.h"

/***
 * ESSE ARQUIVO EH USADO APENAS NOS TESTES AUTOMATIZADOS
 */

typedef struct ListaNosInternos {
	TNoInterno **lista;
	int qtd;
} TListaNosInternos;

// Imprime nohs internos
void imprime_nos_internos(int d, TListaNosInternos *lc);

// Cria lista de nohs internos. Lembrar de usar libera_nos_internos(lista_nos)
TListaNosInternos *cria_nos_internos(int d, int qtd, ...);

// Salva lista de nohs internos no arquivo nome_arquivo
void salva_nos_internos(int d, char *nome_arquivo, TListaNosInternos *lc);

// Le lista de nohs internos do arquivo nome_arquivo
TListaNosInternos *le_nos_internos(int d, char *nome_arquivo);

// Compara duas listas de nohs internos
// Retorna 1 se os nohs das duas listas forem iguais
// e 0 caso contrario
int cmp_nos_internos(int d, TListaNosInternos *c1, TListaNosInternos *c2);

// Desaloca lista de nohs internos
void libera_nos_internos(TListaNosInternos *lc);

#endif