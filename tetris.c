#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO_FILA 5
#define MAX_NOME 10

// Estrutura para representar uma peça
typedef struct {
    int id;
    char nome[MAX_NOME];
} Peca;

// Estrutura para a fila circular
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int quantidade;
} FilaCircular;

// Protótipos das funções
void inicializarFila(FilaCircular *fila);
Peca gerarPeca();
void enfileirar(FilaCircular *fila, Peca peca);
Peca desenfileirar(FilaCircular *fila);
void visualizarFila(FilaCircular *fila);
void mostrarMenu();

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios
    
    FilaCircular fila;
    int opcao;
    
    // Inicializa a fila com 5 peças
    inicializarFila(&fila);
    
    printf("=== Tetris Stack - Nível Novato ===\n");
    printf("Fila inicializada com 5 peças:\n");
    
    do {
        visualizarFila(&fila);
        mostrarMenu();
        
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: {
                // Jogar peça (remover da frente)
                if (fila.quantidade > 0) {
                    Peca pecaRemovida = desenfileirar(&fila);
                    printf(">>> Peça jogada: ID=%d, Nome='%s'\n", pecaRemovida.id, pecaRemovida.nome);
                    
                    // Insere automaticamente uma nova peça
                    Peca novaPeca = gerarPeca();
                    enfileirar(&fila, novaPeca);
                    printf(">>> Nova peça adicionada: ID=%d, Nome='%s'\n", novaPeca.id, novaPeca.nome);
                } else {
                    printf(">>> Fila vazia! Não há peças para jogar.\n");
                }
                break;
            }
            case 2: {
                // Inserir nova peça manualmente
                Peca novaPeca = gerarPeca();
                enfileirar(&fila, novaPeca);
                printf(">>> Nova peça inserida: ID=%d, Nome='%s'\n", novaPeca.id, novaPeca.nome);
                break;
            }
            case 3:
                printf(">>> Saindo do jogo...\n");
                break;
            default:
                printf(">>> Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while(opcao != 3);
    
    return 0;
}

// Inicializa a fila com 5 peças geradas automaticamente
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->quantidade = 0;
    
    // Adiciona 5 peças iniciais
    for(int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enfileirar(fila, novaPeca);
    }
}

// Gera uma peça aleatória
Peca gerarPeca() {
    Peca peca;
    static int proximoId = 1; // Variável estática para gerar IDs únicos
    
    peca.id = proximoId++;
    
    // Tipos de peças do Tetris
    char tipos[7][MAX_NOME] = {"I", "O", "T", "L", "J", "S", "Z"};
    int indiceAleatorio = rand() % 7;
    
    strcpy(peca.nome, tipos[indiceAleatorio]);
    
    return peca;
}

// Adiciona uma peça no final da fila
void enfileirar(FilaCircular *fila, Peca peca) {
    if (fila->quantidade < TAMANHO_FILA) {
        fila->pecas[fila->tras] = peca;
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->quantidade++;
    } else {
        printf(">>> Erro: Fila cheia! Não é possível adicionar mais peças.\n");
    }
}

// Remove e retorna a peça da frente da fila
Peca desenfileirar(FilaCircular *fila) {
    Peca pecaVazia = {0, ""}; // Peça vazia para retorno em caso de erro
    
    if (fila->quantidade > 0) {
        Peca pecaRemovida = fila->pecas[fila->frente];
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
        fila->quantidade--;
        return pecaRemovida;
    } else {
        printf(">>> Erro: Fila vazia! Não há peças para remover.\n");
        return pecaVazia;
    }
}

// Exibe o estado atual da fila
void visualizarFila(FilaCircular *fila) {
    printf("\n--- Estado da Fila (%d/%d peças) ---\n", fila->quantidade, TAMANHO_FILA);
    
    if (fila->quantidade == 0) {
        printf("Fila vazia!\n");
        return;
    }
    
    int indice = fila->frente;
    int posicao = 1;
    
    for(int i = 0; i < fila->quantidade; i++) {
        printf("%d. [ID: %d, Tipo: '%s']", posicao++, 
               fila->pecas[indice].id, 
               fila->pecas[indice].nome);
        
        if (i == 0) {
            printf(" <-- PRÓXIMA");
        }
        
        printf("\n");
        indice = (indice + 1) % TAMANHO_FILA;
    }
}

// Exibe o menu de opções
void mostrarMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Jogar peça (remover da frente e adicionar nova)\n");
    printf("2. Inserir nova peça\n");
    printf("3. Sair\n");
}
