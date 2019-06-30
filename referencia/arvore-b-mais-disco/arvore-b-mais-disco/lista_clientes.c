#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>

#include "lista_clientes.h"


void imprime_clientes(TListaClientes *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		imprime_cliente(lc->lista[i]);
	}
}

TListaClientes *cria_clientes(int qtd, ...)
{
	va_list ap;
	TListaClientes *lc = (TListaClientes *)  malloc(sizeof(TListaClientes));
	lc->qtd = qtd;
	lc->lista = (TCliente **) malloc(sizeof(TCliente *) * (qtd));
	int i;
	va_start(ap, qtd);
	for (i = 0; i < qtd; i++) {
        lc->lista[i] = va_arg(ap, TCliente *);
    }
    va_end(ap);
    return lc;
}

void salva_clientes(char *nome_arquivo, TListaClientes *lc)
{
	FILE *out = fopen(nome_arquivo, "wb");
	int i;
	for (i = 0; i < lc->qtd; i++) {
		salva_cliente(lc->lista[i], out);
	}
	fclose(out);
}

TListaClientes * le_clientes(char *nome_arquivo)
{
	int qtd = 0;
	TListaClientes *lc = (TListaClientes *)  malloc(sizeof(TListaClientes));
	FILE *in = fopen(nome_arquivo, "rb");
	if (in != NULL) {
		TCliente *cliente = NULL;
		while((cliente = le_cliente(in)) != NULL) {
			qtd += 1;
			free(cliente);
		}
		fseek(in, 0, SEEK_SET);
		lc->qtd = qtd;
		lc->lista = (TCliente **) malloc(sizeof(TCliente *) * (qtd));
		qtd = 0;
		while((cliente = le_cliente(in)) != NULL) {
			lc->lista[qtd++] = cliente;
		}
		fclose(in);
	} else {
		lc->qtd = 0;
		lc->lista = NULL;
	}
	return lc;
}

int cmp_clientes(TListaClientes *c1, TListaClientes *c2)
{
	if (c1->qtd != c2->qtd) {
		return 0;
	}
	int i;
	for (i = 0; i < c1->qtd; i++) {
		if (!cmp_cliente(c1->lista[i], c2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

void libera_clientes(TListaClientes *lc)
{
	int i;
	for (i = 0; i < lc->qtd; i++) {
		free(lc->lista[i]);
	}
	free(lc->lista);
	free(lc);
}
