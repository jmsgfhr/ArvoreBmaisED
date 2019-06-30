#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define BEFORE_TEST before();

#define NOME_ARQUIVO_METADADOS "metadados.dat"
#define NOME_ARQUIVO_INDICE "indice.dat"
#define NOME_ARQUIVO_DADOS "clientes.dat"
#define D 2

#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "cliente.h"
#include "no_interno.h"
#include "no_folha.h"
#include "lista_clientes.h"
#include "lista_nos_internos.h"
#include "lista_nos_folhas.h"
#include "metadados.h"
#include "arvore_b_mais.h"


void before() {
    remove(NOME_ARQUIVO_METADADOS);
    remove(NOME_ARQUIVO_INDICE);
    remove(NOME_ARQUIVO_DADOS);
}

// Arvore B+ de altura H = 1, com apenas 1 noh (raiz eh uma folha) que tem 2 registros
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h1() {
    TMetadados *tabMetadados = metadados(D, 0, 1, 0, 1 * tamanho_no_folha(D));
    salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);

    fclose(fopen(NOME_ARQUIVO_INDICE, "w"));

    TListaNosFolhas *tabDados = cria_nos_folhas(D, 1,
                                                cria_no_folha(D, -1, -1, 2,
                                                              cliente(10, "Joao"),
                                                              cliente(13, "Ana Maria")));
    salva_nos_folhas(D, NOME_ARQUIVO_DADOS, tabDados);
    free(tabMetadados);
    libera_nos_folhas(D, tabDados);
}

// Arvore B+ de altura H = 1, com apenas 1 noh (raiz eh uma folha) que tem 4 registros
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h1_cheia() {
    TMetadados *tabMetadados = metadados(D, 0, 1, 0, 1 * tamanho_no_folha(D));
    salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);

    fclose(fopen(NOME_ARQUIVO_INDICE, "w"));

    TListaNosFolhas *tabDados = cria_nos_folhas(D, 1,
                                                cria_no_folha(D, -1, -1, 4,
                                                              cliente(10, "Joao"),
                                                              cliente(13, "Ana Maria"),
                                                              cliente(15, "Bianca"),
                                                              cliente(26, "Clara")));
    salva_nos_folhas(D, NOME_ARQUIVO_DADOS, tabDados);
    free(tabMetadados);
    libera_nos_folhas(D, tabDados);
}

// Arvore B+ de altura H = 2, com raiz e mais 3 folhas
// Ordem de insercao das chaves na arvores: 10, 13, 15, 20, 25, 35, 37
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2() {
    TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
    salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
    // Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
    // Atencao: os ponteiros sao absolutos
    TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                     cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                     0,
                                                                     1 * tamanho_no_folha(D),
                                                                     2 * tamanho_no_folha(D),
                                                                     15,
                                                                     25
                                                     )
    );
    salva_nos_internos(D, NOME_ARQUIVO_INDICE, tabIndice);

    // Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
    TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                              cliente(10, "Joao"),
                                                              cliente(13, "Ana Maria")
                                                ),
                                                cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 2,
                                                              cliente(15, "Jose"),
                                                              cliente(20, "Mariana")
                                                ),
                                                cria_no_folha(D, 0, -1, 3,
                                                              cliente(25, "Ronaldo"),
                                                              cliente(35, "Marcela"),
                                                              cliente(37, "Leonardo")
                                                )
    );
    salva_nos_folhas(D, NOME_ARQUIVO_DADOS, tabDados);
    free(tabMetadados);
    libera_nos_internos(tabIndice);
    libera_nos_folhas(D, tabDados);
}

// Arvore B+ de altura H = 2, com raiz e mais 3 folhas, 1 delas cheia
// Ordem de insercao das chaves na arvore: 10, 13, 15, 20, 25, 35, 37, 21, 23
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2_cheia() {
    TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
    salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
    // Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
    // Atencao: os ponteiros sao absolutos
    TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                     cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                     0,
                                                                     1 * tamanho_no_folha(D),
                                                                     2 * tamanho_no_folha(D),
                                                                     15,
                                                                     25
                                                     )
    );
    salva_nos_internos(D, NOME_ARQUIVO_INDICE, tabIndice);

    // Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
    TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                              cliente(10, "Joao"),
                                                              cliente(13, "Ana Maria")
                                                ),
                                                cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 4,
                                                              cliente(15, "Jose"),
                                                              cliente(20, "Mariana"),
                                                              cliente(21, "Bruna"),
                                                              cliente(23, "Bruno")
                                                ),
                                                cria_no_folha(D, 0, -1, 3,
                                                              cliente(25, "Ronaldo"),
                                                              cliente(35, "Marcela"),
                                                              cliente(37, "Leonardo")
                                                )
    );
    salva_nos_folhas(D, NOME_ARQUIVO_DADOS, tabDados);
    free(tabMetadados);
    libera_nos_internos(tabIndice);
    libera_nos_folhas(D, tabDados);
}

// Arvore B+ de altura H = 2, com raiz e mais 5 folhas, 1 delas cheia
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h2_completa() {
    TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 5 * tamanho_no_folha(D));
    salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
    // Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
    // Atencao: os ponteiros sao absolutos
    TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                     cria_no_interno(D, 4, -1, 1, 4 * 2 + 1,
                                                                     0,
                                                                     1 * tamanho_no_folha(D),
                                                                     2 * tamanho_no_folha(D),
                                                                     3 * tamanho_no_folha(D),
                                                                     4 * tamanho_no_folha(D),
                                                                     15,
                                                                     25,
                                                                     40,
                                                                     70
                                                     )
    );
    salva_nos_internos(D, NOME_ARQUIVO_INDICE, tabIndice);

    // Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
    TListaNosFolhas *tabDados = cria_nos_folhas(D, 5,
                                                cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                              cliente(10, "Joao"),
                                                              cliente(13, "Ana Maria")
                                                ),
                                                cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 4,
                                                              cliente(15, "Jose"),
                                                              cliente(20, "Mariana"),
                                                              cliente(21, "Bruna"),
                                                              cliente(23, "Bruno")
                                                ),
                                                cria_no_folha(D, 0, 3 * tamanho_no_folha(D), 3,
                                                              cliente(25, "Ronaldo"),
                                                              cliente(35, "Marcela"),
                                                              cliente(37, "Leonardo")
                                                ),
                                                cria_no_folha(D, 0, 4 * tamanho_no_folha(D), 2,
                                                              cliente(40, "Aline"),
                                                              cliente(45, "Juca")
                                                ),
                                                cria_no_folha(D, 0, -1, 2,
                                                              cliente(70, "Nicolas"),
                                                              cliente(77, "Lina")
                                                )
    );
    salva_nos_folhas(D, NOME_ARQUIVO_DADOS, tabDados);
    free(tabMetadados);
    libera_nos_internos(tabIndice);
    libera_nos_folhas(D, tabDados);
}

// Arvore B de altura H = 3, com raiz que aponta para 2 nohs internos, e mais 6 folhas
// Ver arquivo ArvoreTesteDOJO.pdf para o desenho da arvore
void monta_arvore_h3() {
    TMetadados *tabMetadados = metadados(D, 0, 0, 3 * tamanho_no_interno(D), 6 * tamanho_no_folha(D));
    salva_arq_metadados(NOME_ARQUIVO_METADADOS, tabMetadados);
    // Estrutura do No Interno: m, pont_pai, aponta_folha, 2m + 1, lista de ponteiros, lista de chaves
    // Atencao: os ponteiros sao absolutos
    TListaNosInternos *tabIndice = cria_nos_internos(D, 3,
                                                     cria_no_interno(D, 1, -1, 0, 1 * 2 + 1,
                                                                     1 * tamanho_no_interno(D),
                                                                     2 * tamanho_no_interno(D),
                                                                     37
                                                     ),
                                                     cria_no_interno(D, 2, 0, 1, 2 * 2 + 1,
                                                                     0 * tamanho_no_folha(D),
                                                                     1 * tamanho_no_folha(D),
                                                                     2 * tamanho_no_folha(D),
                                                                     15,
                                                                     25
                                                     ),
                                                     cria_no_interno(D, 2, 0, 1, 2 * 2 + 1,
                                                                     3 * tamanho_no_folha(D),
                                                                     4 * tamanho_no_folha(D),
                                                                     5 * tamanho_no_folha(D),
                                                                     39,
                                                                     55
                                                     )
    );
    salva_nos_internos(D, NOME_ARQUIVO_INDICE, tabIndice);

    // Estrutura do No Folha: pont_pai, pont_prox, m, registros de clientes
    TListaNosFolhas *tabDados = cria_nos_folhas(D, 6,
                                                cria_no_folha(D, 1 * tamanho_no_interno(D), 1 * tamanho_no_folha(D), 2,
                                                              cliente(10, "Joao"),
                                                              cliente(13, "Ana Maria")
                                                ),
                                                cria_no_folha(D, 1 * tamanho_no_interno(D), 2 * tamanho_no_folha(D), 2,
                                                              cliente(15, "Jose"),
                                                              cliente(20, "Mariana")
                                                ),
                                                cria_no_folha(D, 1 * tamanho_no_interno(D), 3 * tamanho_no_folha(D), 2,
                                                              cliente(25, "Ronaldo"),
                                                              cliente(35, "Marcela")
                                                ),
                                                cria_no_folha(D, 2 * tamanho_no_interno(D), 4 * tamanho_no_folha(D), 2,
                                                              cliente(37, "Leonardo"),
                                                              cliente(38, "Karla")
                                                ),
                                                cria_no_folha(D, 2 * tamanho_no_interno(D), 5 * tamanho_no_folha(D), 2,
                                                              cliente(39, "Mario"),
                                                              cliente(50, "Ricardo")
                                                ),
                                                cria_no_folha(D, 2 * tamanho_no_interno(D), -1, 2,
                                                              cliente(55, "Rosa"),
                                                              cliente(60, "Michele"),
                                                              cliente(70, "Rafael")
                                                )
    );
    salva_nos_folhas(D, NOME_ARQUIVO_DADOS, tabDados);
    free(tabMetadados);
    libera_nos_internos(tabIndice);
    libera_nos_folhas(D, tabDados);
}

BEGIN_TESTS();

    TEST("Busca 1 -- chave procurada esta na raiz. Raiz eh folha");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h1();

        pont = busca(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);
    }

    TEST("Busca 2 -- chave procurada nao esta na arvore. Raiz eh folha");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h1();

        pont = busca(6, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);
    }

    TEST("Busca 3 -- chave esta na arvore");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2();

        pont = busca(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(1 * tamanho_no_folha(D), pont);
    }

    TEST("Busca 4 -- chave nao esta na arvore");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2();

        pont = busca(16, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(1 * tamanho_no_folha(D), pont);
    }

    TEST("Busca 5 -- chave esta na arvore");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h3();

        pont = busca(37, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(3 * tamanho_no_folha(D), pont);
    }

    TEST("Busca 6 -- chave nao esta na arvore");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h3();

        pont = busca(26, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(2 * tamanho_no_folha(D), pont);
    }


    TEST("Insercao 1 em arvore de altura H = 1, sem particionamento");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h1();

        pont = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);

        TMetadados *tabMetadados = metadados(D, 0, 1, 0, 1 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 1,
                                                    cria_no_folha(D, -1, -1, 3,
                                                                  cliente(10, "Joao"),
                                                                  cliente(11, "Vanessa"),
                                                                  cliente(13, "Ana Maria")));
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Insercao 2 em arvore de altura H = 2, sem particionamento");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2();

        pont = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         15,
                                                                         25
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 3,
                                                                  cliente(10, "Joao"),
                                                                  cliente(11, "Vanessa"),
                                                                  cliente(13, "Ana Maria")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 2,
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Insercao 3 em arvore de altura H = 2. Exige particionamento de uma pagina folha");
    if (!skip) {
        int pont = INT_MAX;
        // Arvore tem um dos nohs folha cheio. E eh neste noh que a insercao ocorrera
        monta_arvore_h2_cheia();

        pont = insere(16, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(1 * tamanho_no_folha(D), pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 4 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 3, -1, 1, 3 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         3 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         15,
                                                                         20,
                                                                         25
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 4,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(13, "Ana Maria")
                                                    ),
                                                    cria_no_folha(D, 0, 3 * tamanho_no_folha(D), 2,
                                                                  cliente(15, "Jose"),
                                                                  cliente(16, "Vanessa")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 3,
                                                                  cliente(20, "Mariana"),
                                                                  cliente(21, "Bruna"),
                                                                  cliente(23, "Bruno")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Insercao 4 em arvore de altura H = 2, chave de registro ja existe -- nao inserir");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2();

        pont = insere(13, "Manriana", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(-1, pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         15,
                                                                         25
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(13, "Ana Maria")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 2,
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Insercao 5 em arvore de altura H = 1 cheia, que causa aumento na altura da arvore");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h1_cheia();

        pont = insere(11, "Vanessa", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, 1 * tamanho_no_interno(D), 2 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 1, -1, 1, 1 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         13
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 2,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(11, "Vanessa")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(13, "Ana Maria"),
                                                                  cliente(15, "Bianca"),
                                                                  cliente(26, "Clara")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Insercao 6 em arvore de altura H = 2 completa. Folha estah cheia, raiz tambem");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2_completa();

        pont = insere(22, "Camila", NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(5 * tamanho_no_folha(D), pont);

        TMetadados *tabMetadados = metadados(D, 2 * tamanho_no_interno(D), 0, 3 * tamanho_no_interno(D),
                                             6 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 3,
                // Antigo noh raiz
                                                         cria_no_interno(D, 2, 2 * tamanho_no_interno(D), 1, 2 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         5 * tamanho_no_folha(D),
                                                                         15,
                                                                         21
                                                         ),
                // Noh que surgiu do particionamento da raiz
                                                         cria_no_interno(D, 2, 2 * tamanho_no_interno(D), 1, 2 * 2 + 1,
                                                                         2 * tamanho_no_folha(D),
                                                                         3 * tamanho_no_folha(D),
                                                                         4 * tamanho_no_folha(D),
                                                                         40,
                                                                         70
                                                         ),
                // Novo noh raiz
                                                         cria_no_interno(D, 1, -1, 0, 1 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_interno(D),
                                                                         25
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 6,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(13, "Ana Maria")
                                                    ),
                                                    cria_no_folha(D, 0, 5 * tamanho_no_folha(D), 2,
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 1 * tamanho_no_interno(D), 3 * tamanho_no_folha(D),
                                                                  3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    ),
                                                    cria_no_folha(D, 1 * tamanho_no_interno(D), 4 * tamanho_no_folha(D),
                                                                  2,
                                                                  cliente(40, "Aline"),
                                                                  cliente(45, "Juca")
                                                    ),
                                                    cria_no_folha(D, 1 * tamanho_no_interno(D), -1, 2,
                                                                  cliente(70, "Nicolas"),
                                                                  cliente(77, "Lina")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 3,
                                                                  cliente(21, "Bruna"),
                                                                  cliente(22, "Camila"),
                                                                  cliente(23, "Bruno")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);
        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Exclusao 1 em arvore de altura H = 2 cheia, nao eh necessario tratamento especial");
    if (!skip) {
        int pont = INT_MAX;
        // Arvore tem um dos nohs folha cheio. E eh neste noh que a excusao ocorrera
        monta_arvore_h2_cheia();

        pont = exclui(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(1 * tamanho_no_folha(D), pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         15,
                                                                         25
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(13, "Ana Maria")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 3,
                                                                  cliente(15, "Jose"),
                                                                  cliente(21, "Bruna"),
                                                                  cliente(23, "Bruno")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);
        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Exclusao 2 em arvore de altura H = 2, eh necessario redistribuição");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2();

        pont = exclui(20, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(1 * tamanho_no_folha(D), pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         15,
                                                                         35
                                                         )
        );

        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(13, "Ana Maria")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 2,
                                                                  cliente(15, "Jose"),
                                                                  cliente(25, "Ronaldo")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 2,
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    )
        );

        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Exclusao 3 em arvore de altura H = 2, eh necessario redistribuicao");
    if (!skip) {
        int pont = INT_MAX;
        // Arvore tem um dos nohs folha cheio. E eh neste noh que a excusao ocorrera
        monta_arvore_h2_cheia();

        pont = exclui(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 2, -1, 1, 2 * 2 + 1,
                                                                         0,
                                                                         1 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         20,
                                                                         25
                                                         )
        );
        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                    cria_no_folha(D, 0, 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(15, "Jose")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 3,
                                                                  cliente(20, "Mariana"),
                                                                  cliente(21, "Bruna"),
                                                                  cliente(23, "Bruno")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    )
        );
        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Exclusao 4 em arvore de altura H = 2, eh necessario concatenação");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h2();

        pont = exclui(10, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);

        TMetadados *tabMetadados = metadados(D, 0, 0, tamanho_no_interno(D), 3 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 1,
                                                         cria_no_interno(D, 1, -1, 1, 2 * 1 + 1,
                                                                         0,
                                                                         2 * tamanho_no_folha(D),
                                                                         25
                                                         )
        );

        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 3,
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D), 3,
                                                                  cliente(13, "Ana Maria"),
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 0, 2 * tamanho_no_folha(D),
                                                                  2, //Esse noh eh lixo -- fica como estava -- nao ha mais ninguem apontando para ele
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 0, -1, 3,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela"),
                                                                  cliente(37, "Leonardo")
                                                    )
        );

        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

    TEST("Exclusao 5 em arvore de altura H = 3, eh necessario concatenação, causa diminuicao da altura da arvore");
    if (!skip) {
        int pont = INT_MAX;
        monta_arvore_h3();

        pont = exclui(13, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_INDICE, NOME_ARQUIVO_DADOS, 2);
        ASSERT_EQUAL(0, pont);

        TMetadados *tabMetadados = metadados(D, tamanho_no_interno(D), 0, 3 * tamanho_no_interno(D), 6 * tamanho_no_folha(D));
        TMetadados *tabMetadadosSaida = le_arq_metadados(NOME_ARQUIVO_METADADOS);
        ASSERT_EQUAL_CMP(D, tabMetadados, tabMetadadosSaida, cmp_metadados);
        free(tabMetadados);
        free(tabMetadadosSaida);

        TListaNosInternos *tabIndice = cria_nos_internos(D, 3,
                                                         cria_no_interno(D, 1, -1, 0, 1 * 2 + 1, //esse noh eh lixo -- era a antiga raiz -- permanece como estava
                                                                         1 * tamanho_no_interno(D),
                                                                         2 * tamanho_no_interno(D),
                                                                         37
                                                         ),
                                                         cria_no_interno(D, 4, 0, 1, 2 * 2 + 1,
                                                                         0 * tamanho_no_folha(D),
                                                                         2 * tamanho_no_folha(D),
                                                                         3 * tamanho_no_folha(D),
                                                                         4 * tamanho_no_folha(D),
                                                                         5 * tamanho_no_folha(D),
                                                                         25,
                                                                         37,
                                                                         39,
                                                                         55
                                                         ),
                                                         cria_no_interno(D, 2, 0, 1, 2 * 2 + 1, //esse noh eh lixo -- permanece como estava
                                                                         3 * tamanho_no_folha(D),
                                                                         4 * tamanho_no_folha(D),
                                                                         5 * tamanho_no_folha(D),
                                                                         39,
                                                                         55
                                                         )
        );

        TListaNosInternos *tabIndiceSaida = le_nos_internos(D, NOME_ARQUIVO_INDICE);
        ASSERT_EQUAL_CMP(D, tabIndice, tabIndiceSaida, cmp_nos_internos);
        libera_nos_internos(tabIndice);
        libera_nos_internos(tabIndiceSaida);

        TListaNosFolhas *tabDados = cria_nos_folhas(D, 6,
                                                    cria_no_folha(D, 1 * tamanho_no_interno(D), 1 * tamanho_no_folha(D), 2,
                                                                  cliente(10, "Joao"),
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 1 * tamanho_no_interno(D), 2 * tamanho_no_folha(D), 2, //esse noh eh lixo -- permanece como estava -- nao ha mais ninguem apontando para ele
                                                                  cliente(15, "Jose"),
                                                                  cliente(20, "Mariana")
                                                    ),
                                                    cria_no_folha(D, 1 * tamanho_no_interno(D), 3 * tamanho_no_folha(D), 2,
                                                                  cliente(25, "Ronaldo"),
                                                                  cliente(35, "Marcela")
                                                    ),
                                                    cria_no_folha(D, 2 * tamanho_no_interno(D), 4 * tamanho_no_folha(D), 2,
                                                                  cliente(37, "Leonardo"),
                                                                  cliente(38, "Karla")
                                                    ),
                                                    cria_no_folha(D, 2 * tamanho_no_interno(D), 5 * tamanho_no_folha(D), 2,
                                                                  cliente(39, "Mario"),
                                                                  cliente(50, "Ricardo")
                                                    ),
                                                    cria_no_folha(D, 2 * tamanho_no_interno(D), -1, 2,
                                                                  cliente(55, "Rosa"),
                                                                  cliente(60, "Michele"),
                                                                  cliente(70, "Rafael")
                                                    )
        );

        TListaNosFolhas *tabDadosSaida = le_nos_folhas(D, NOME_ARQUIVO_DADOS);

        ASSERT_EQUAL_CMP(D, tabDados, tabDadosSaida, cmp_nos_folhas);
        libera_nos_folhas(D, tabDados);
        libera_nos_folhas(D, tabDadosSaida);
    }

END_TESTS();