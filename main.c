#include "arvbmais.h"
#include "arvbmais.c"
#include "pizza.h"

int main(int argc, char *argv[]){

    int t;
    int cod;
    TABM *arvore = inicializa();
    printf("Digite o fator de ramificacao: ");
    scanf("%d", &t);

    //Visualizar dados do arquivo
    /*  FILE *dados = fopen("dados_iniciais.dat", "rb+");
	int num_pizzas = quantidade_pizzas(dados);
	printf("Quantidade de pizzas: %i\n", num_pizzas);

	imprimir_cardapio(dados,num_pizzas);

	fclose(dados);
    */

    int opcao = 1;
    while(opcao){
        printf("1 - Visualizar cardapio\n2 - Inserir pizza\n3 - Remover pizza\n4 - Remover pizzas por categoria\n5 - Alterar pizza\n6 - Buscar pizza\n7 - Buscar pizza por categoria\n0 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 0:
                // Sair
                return 0;
            case 1:
                // Visualizar cardapio
                printf("1\n");
                break;
            case 2:
                // Inserir pizza
                scanf("%d",&cod);
                arvore = insere(arvore,cod,t);
                printf("2\n");
                break;
            case 3:
                // Remover pizza
                printf("3\n");
                break;
            case 4:
                // Remover pizzas por categoria
                printf("4\n");
                break;
            case 5:
                // Alterar pizza
                printf("5\n");
                break;
            case 6:
            // Buscar pizza
                printf("6\n");
                break;
            case 7:
            // Buscar pizza por categoria
                printf("7\n");
                break;
        }
    }
}