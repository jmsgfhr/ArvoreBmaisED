#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>

#include "lista_nos_folhas.h"


void imprime_nos_folhas(int d, TListaNosFolhas *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		imprime_no_folha(d, lc->lista[i]);
	}
}

TListaNosFolhas *cria_nos_folhas(int d, int qtd, ...)
{
	va_list ap;
	TListaNosFolhas *lc = (TListaNosFolhas *)  malloc(sizeof(TListaNosFolhas));
	lc->qtd = qtd;
	lc->lista = (TNoFolha **) malloc(sizeof(TNoFolha *) * (qtd));
	int i;
	va_start(ap, qtd);
	for (i = 0; i < qtd; i++) {
        lc->lista[i] = va_arg(ap, TNoFolha *);
    }
    va_end(ap);
    return lc;
}

void salva_nos_folhas(int d, char *nome_arquivo, TListaNosFolhas *lc)
{
	FILE *out = fopen(nome_arquivo, "wb");
	int i;
	for (i = 0; i < lc->qtd; i++) {
		salva_no_folha(d, lc->lista[i], out);
	}
	fclose(out);
}

TListaNosFolhas *le_nos_folhas(int d, char *nome_arquivo)
{
	int qtd = 0;
	TListaNosFolhas *lc = (TListaNosFolhas *)  malloc(sizeof(TListaNosFolhas));
	FILE *in = fopen(nome_arquivo, "rb");
	if (in != NULL) {
		TNoFolha *no = NULL;
		while((no = le_no_folha(d, in)) != NULL) {
			qtd += 1;
			libera_no_folha(d, no);
		}
		fseek(in, 0, SEEK_SET);
		lc->qtd = qtd;
		lc->lista = (TNoFolha **) malloc(sizeof(TNoFolha *) * (qtd));
		qtd = 0;
		while((no = le_no_folha(d, in)) != NULL) {
			lc->lista[qtd++] = no;
		}
		fclose(in);
	} else {
		lc->qtd = 0;
		lc->lista = NULL;
	}
	return lc;
}

int cmp_nos_folhas(int d, TListaNosFolhas *c1, TListaNosFolhas *c2)
{
	if (c1->qtd != c2->qtd) {
		return 0;
	}
	int i;
	for (i = 0; i < c1->qtd; i++) {
		if (!cmp_no_folha(d, c1->lista[i], c2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

void libera_nos_folhas(int d, TListaNosFolhas *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		libera_no_folha(d, lc->lista[i]);
	}
	free(lc->lista);
	free(lc);
}
