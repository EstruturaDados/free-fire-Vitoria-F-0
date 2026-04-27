//Arrumar problemas de lógica/ Coisas que não estão funcionando/ Comentários faltando/ Se tem tudo que o professor pediu
//Desafio Nível Novato - Código da Ilha: Edição Free Fire.
//Objetivo: simular um inventário de itens coletados em jogo.
//Mochila inicial de loot: cadastrar, remover, listar e buscar itens.
//Desafio Nível Aventureiro - Zona de Perigo: O Caos Começa.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACIDADE_MAX_V 10 //Contador para vetor
#define CAPACIDADE_MAX_LE 10 //Contador para lista encadeada

//Definição do struct Item da mochila para vetor
typedef struct {
    char nome[30];
    char tipo[20]; //Arma, munição, cura, colete, etc)
    int quantidade;
} Item;

//Definição do struct Item da mochila para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//Vetor mochila
Item mochilaVetor[CAPACIDADE_MAX_V];
int contadorV = 0; //Controla quantos itens foram adicionados/removidos

//Lista encadeada mochila
No* mochilaLista = NULL;
int contadorLE = 0;

//
int comparacoesBin = 0;
int comparacoesSeqV = 0;
int comparacoesSeqL = 0;

//Necessário para limpar o buffer
void limparBuffer() {
    while (getchar() != '\n');
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//Tabela para listar e exibir todos os itens atuais na mochila
void listarItensVetor() {

    printf("\n--- Itens da Mochila (%d/%d) ---\n", contadorV, CAPACIDADE_MAX_V);
    printf("----------------------------------------------------------\n");
    printf("Nome               | Tipo           | Quantidade\n");
    printf("----------------------------------------------------------\n");

    //Verificar se a mochila está vazia
    if (contadorV == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    //Para adicionar os itens e exibi-los conforme a estrutura da tabela
    for (int i = 0; i < contadorV; i++) {
        printf("| %-20s | %-20s | %-10d |\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
        printf("----------------------------------------------------------\n");
    }
}

//Adicionar item na mochila
void inserirItemVetor() {
    //Verificar se a capacidade máxima foi atingida
    if (contadorV >= CAPACIDADE_MAX_V) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("Nome: ");
    fgets(mochilaVetor[contadorV].nome, 30, stdin); //fgets para aceitar nomes compostos
    mochilaVetor[contadorV].nome[strcspn(mochilaVetor[contadorV].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochilaVetor[contadorV].tipo, 20, stdin);
    mochilaVetor[contadorV].tipo[strcspn(mochilaVetor[contadorV].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[contadorV].quantidade);
    limparBuffer();

    contadorV++;
}

//Função para procurar o item pelo nome
int buscarSequencialVetor(char nome[]) {
    comparacoesSeqV = 0;

    for (int i = 0; i < contadorV; i++) {
        comparacoesSeqV++;

        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

//Remover item da mochila pelo nome
void removerItemVetor() {
    char nome[30];

    printf("Digite o nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscarSequencialVetor(nome);

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = pos; i < contadorV - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    contadorV--;
    printf("Item removido!\n");
}

//Função para organizar os itens da Mochila Vetor (busca binária precisa que a lista esteja organizada)
void ordenarVetor() {
    for (int i = 0; i < contadorV - 1; i++) {
        for (int j = 0; j < contadorV - i - 1; j++) {

            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // troca
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }

        }
    }

    printf("Mochila ordenada por nome!\n");
}

//Função para buscar os itens dentro da mochila pelo seu nome
int buscarBinariaVetor(char nome[]) {
    int inicio = 0;
    int fim = contadorV - 1;

    comparacoesBin = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        comparacoesBin++;

        int resultado = strcmp(mochilaVetor[meio].nome, nome);

        if (resultado == 0) {
            return meio; // encontrou
        }
        else if (resultado < 0) {
            inicio = meio + 1; // busca na direita
        }
        else {
            fim = meio - 1; // busca na esquerda
        }
    }

    return -1; // não encontrou
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer(); //Para o fgets e scanf não se misturarem

    //Inserção no início da lista
    novo->proximo = mochilaLista;
    mochilaLista = novo;

    contadorLE++;

    printf("Item inserido na lista!\n");
}

No* buscarSequencialLista(char nome[]) {
    No* atual = mochilaLista;
    comparacoesSeqL = 0;

    while (atual != NULL) {
        comparacoesSeqL++;

        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

void removerItemLista() {
    char nome[30];

    printf("Digite o nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }

    //Se for o primeiro da lista
    if (anterior == NULL) {
        mochilaLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    contadorLE--;

    printf("Item removido da lista!\n");
}

void listarItensLista() {
    No* atual = mochilaLista;

    printf("\n--- Itens da Mochila (Lista) (%d) ---\n", contadorLE);

    if (atual == NULL) {
        printf("Mochila vazia!\n");
        return;
    }

    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);

        atual = atual->proximo;
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//Menu para o usuário
void mostrarMenu() {
    printf("-----------------------------------------");
    printf("\n ---Mochila de Sobrevivente--- \n");
    printf("-----------------------------------------\n");
    printf("Itens na Mochila: %d/%d\n\n", contadorV, CAPACIDADE_MAX_V); //Representa e atualiza os itens

    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//Main
//Para o menu funcionar
int main() {
    int opcao;

    int tipoEstrutura;

printf("Escolha a estrutura:\n");
printf("1 - Vetor\n");
printf("2 - Lista Encadeada\n");
scanf("%d", &tipoEstrutura);
limparBuffer();

    do {
        mostrarMenu();
        scanf("%d", &opcao);
        limparBuffer();//Limpa o que sobrou no buffer para o próximo pedido

        switch (opcao) {
            
            case 1: {
            inserirItemVetor(); 
            listarItensVetor();}  
            {inserirItemLista();
            listarItensLista();
    }
            break;
            
            case 2: {
            removerItemVetor(); 
            listarItensVetor();} 
            {removerItemLista();
            listarItensLista();
    }
            break;
            
            case 3: 
            listarItensVetor(); 
            listarItensLista();
            break;
            
           case 4: {
            char nome[30];

            printf("Digite o nome do item: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            int posSeq = buscarSequencialVetor(nome);

            ordenarVetor();
            int posBin = buscarBinariaVetor(nome);

            No* posLista = buscarSequencialLista(nome);

            printf("\n====== COMPARACAO ======\n");

            printf("Vetor (Sequencial): %d comparacoes\n", comparacoesSeqV);

            printf("Vetor (Binaria): %d comparacoes\n", comparacoesBin);

            printf("Lista (Sequencial): %d comparacoes\n", comparacoesSeqL);

            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
    }

} while (opcao != 0);

return 0;
}