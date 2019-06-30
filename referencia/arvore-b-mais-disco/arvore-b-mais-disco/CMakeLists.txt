cmake_minimum_required(VERSION 3.10)
project(arvore_b_mais_disco)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(arvore_b_mais_disco
        arvore_b_mais.c
        arvore_b_mais.h
        cliente.c
        cliente.h
        lista_clientes.c
        lista_clientes.h
        lista_nos_folhas.c
        lista_nos_folhas.h
        lista_nos_internos.c
        lista_nos_internos.h
        Makefile
        metadados.c
        metadados.h
        no_folha.c
        no_folha.h
        no_interno.c
        no_interno.h
        test_arvore_b_mais.c
        ufftest.h)
