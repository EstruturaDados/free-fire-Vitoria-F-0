//Desafio Nível Novato - Código da Ilha: Edição Free Fire.
//Objetivo: simular um inventário de itens coletados em jogo.
//Mochila inicial de loot: cadastrar, remover, listar e buscar itens.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACIDADE_MAX 10

//Definição do struct Item da mochila
typedef struct {
    char nome[30];
    char tipo[20]; //Arma, munição, cura, colete, etc)
    int quantidade;
} Item;

//Vetor mochila
Item mochila[CAPACIDADE_MAX];
int contador = 0; //Controla quantos itens foram adicionados/removidos

//Necessário para limpar o buffer
void limparBuffer() {
    while (getchar() != '\n');
}

//Tabela para listar e exibir todos os itens atuais na mochila
void listarItens() {

    printf("\n--- Itens da Mochila (%d/%d) ---\n", contador, CAPACIDADE_MAX);
    printf("----------------------------------------------------------\n");
    printf("Nome               | Tipo           | Quantidade\n");
    printf("----------------------------------------------------------\n");

    //Verificar se a mochila está vazia
    if (contador == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    //Para adicionar os itens e exibi-los conforme a estrutura da tabela
    for (int i = 0; i < contador; i++) {
        printf("| %-20s | %-20s | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
        printf("----------------------------------------------------------\n");
    }
}

//Adicionar item na mochila
void inserirItem() {
    //Verificar se a capacidade máxima foi atingida
    if (contador >= CAPACIDADE_MAX) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("Nome: ");
    fgets(mochila[contador].nome, 30, stdin); //fgets para aceitar nomes compostos
    mochila[contador].nome[strcspn(mochila[contador].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[contador].tipo, 20, stdin);
    mochila[contador].tipo[strcspn(mochila[contador].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[contador].quantidade);

    contador++;
}

//Função para procurar o item pelo nome
int buscarItem(char nome[]) {
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) { //strcmp para comparar nomes
            return i;
        }
    }
    return -1; //Se não encontrar
}

//Remover item da mochila pelo nome
void removerItem() {
    char nome[30];

    printf("Digite o nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscarItem(nome);

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = pos; i < contador - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    contador--;
    printf("Item removido!\n");
}

//Menu para o usuário
void mostrarMenu() {
    printf("-----------------------------------------");
    printf("\n ---Mochila de Sobrevivente--- \n");
    printf("-----------------------------------------\n");
    printf("Itens na Mochila: %d/%d\n\n", contador, CAPACIDADE_MAX); //Representa e atualiza os itens

    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//Main
//Para o menu funcionar
int main() {
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);
        limparBuffer();//Limpa o que sobrou no buffer para o próximo pedido

        switch (opcao) {
            case 1: inserirItem(); 
            listarItens(); 
            break;
            case 2: removerItem(); 
            listarItens(); 
            break;
            case 3: listarItens(); 
            break;
            case 0: printf("Saindo do sistema \n"); 
            break;
            default: printf("Opção inválida! \n");
        }

    } while (opcao != 0);

    return 0;
}