#include <stdio.h>
#include <string.h>
#include <windows.h>

int opcao;

typedef struct {
    char nomeResponsavel;
    float idEmpresa;
    char cnpj;
    char endereco[100];
    char telefone[15];
    char empresa[100];
    char email[100];
} remetente;

typedef struct {
    int idProduto;
    char nomeProduto[100];
    char categoria[100];
    float preco;
    float peso;
    float cubagem;
    int quantidade;
} produto;

produto estoque[100];
int totalProdutos = 0;

typedef struct {
    int idPedido;
    char nomeCliente[100];
    int idProduto;
    char nomeProduto[100];
    float quantidade;
    float precoTotal;
} pedido;

void erroEntrada() {
    printf("\nEntrada invalida! Por favor, tente novamente.\n");
    while (getchar() != '\n');
}

void cadastrarProduto() {
    produto p;
    p.idProduto = totalProdutos + 1;
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", p.nomeProduto);
    printf("Categoria: ");
    scanf(" %[^\n]", p.categoria);
    do {
        printf("Preco: ");
        if (scanf("%f", &p.preco) != 1) {
            erroEntrada();
        } else {
            break;
        }
    } while (1);
    do {
        printf("Cubagem: ");
        if (scanf("%f", &p.cubagem) != 1) {
            erroEntrada();
        } else {
            break;
        }
    } while (1);
    do {
        printf("Peso: ");
        if (scanf("%f", &p.peso) != 1) {
            erroEntrada();
        } else {
            break;
        }
    } while (1);
    p.quantidade = 0;
    estoque[totalProdutos] = p;
    totalProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void adicionarProduto() {
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio! Cadastre um produto primeiro.\n");
        return;
    }
    int idBusca;
    int encontrado;
    do {
        encontrado = 0;
        printf("\nDigite o ID do produto para adicionar: ");
        if (scanf("%d", &idBusca) != 1) {
            erroEntrada();
            continue;
        }
        for (int i = 0; i < totalProdutos; i++) {
            if (estoque[i].idProduto == idBusca) {
                printf("\n--- Produto Encontrado ---\n");
                printf("ID: %d | Nome: %s | Preco: R$%.2f\n", 
                        estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].preco);
                int quantidadeAdicionar;
                printf("Quantas unidades deseja adicionar? (0 para voltar): ");
                if (scanf("%d", &quantidadeAdicionar) == 1) {
                    if (quantidadeAdicionar == 0) {
                        printf("Operacao cancelada.\n");
                    } else {
                        estoque[i].quantidade += quantidadeAdicionar;
                        printf("Quantidade atualizada! Novo estoque de %s: %d unidades\n", 
                                estoque[i].nomeProduto, estoque[i].quantidade);
                    }
                    encontrado = 1;
                } else {
                    erroEntrada();
                }
                break;
            }
        }
        if (!encontrado) printf("\nErro: Produto com ID %d nao encontrado.\n", idBusca);
    } while (!encontrado);
}

void baixaEstoque() {
    int idBusca;
    int encontrado;
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio!\n");
        return;
    }
    do {
        encontrado = 0;
        printf("\nDigite o ID do produto para dar baixa: ");
        if (scanf("%d", &idBusca) != 1) {
            erroEntrada();
            continue;
        }
        for (int i = 0; i < totalProdutos; i++) {
            if (estoque[i].idProduto == idBusca) {
                printf("\n--- Produto Encontrado ---\n");
                printf("ID: %d | Nome: %s | Estoque: %d unidades\n", 
                        estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].quantidade);
                int quantidadeBaixa;
                printf("Quantas unidades deseja remover? (0 para voltar): ");
                if (scanf("%d", &quantidadeBaixa) == 1) {
                    if (quantidadeBaixa == 0) {
                        printf("Operacao cancelada.\n");
                    } else if (quantidadeBaixa <= estoque[i].quantidade) {
                        estoque[i].quantidade -= quantidadeBaixa;
                        printf("Baixa realizada! Novo estoque de %s: %d unidades\n", 
                                estoque[i].nomeProduto, estoque[i].quantidade);
                    } else {
                        printf("Erro: Quantidade insuficiente em estoque!\n");
                    }
                    encontrado = 1;
                } else {
                    erroEntrada();
                }
                break;
            }
        }
        if (!encontrado) printf("\nErro: Produto com ID %d nao encontrado.\n", idBusca);
    } while (!encontrado);
}

void cadastrarPedido() {}

void consultaEstoqueTotal() {
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio!\n");
        return;
    }
    printf("\n%-5s | %-20s | %-15s | %-10s | %-10s\n", "ID", "NOME", "CATEGORIA", "PRECO", "PESO");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%-5d | %-20s | %-15s | R$%-8.2f | %-8.2fkg\n", 
                estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].categoria, 
                estoque[i].preco, estoque[i].peso);
    }
}

void consultaEstoquePorProduto() {
    int idBusca;
    int encontrado = 0;
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio!\n");
        return;
    }
    printf("Digite o ID do produto para busca: ");
    scanf("%d", &idBusca);
    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].idProduto == idBusca) {
            printf("\n--- Produto Encontrado ---\n");
            printf("ID: %d | Nome: %s | Preco: R$%.2f\n", 
                    estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].preco);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("\nErro: Produto com ID %d nao encontrado.\n", idBusca);
}

void consultaEstoque() {
    int op;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Consultar Estoque Geral\n");
        printf("2. Consultar Estoque por Produto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) {
            erroEntrada();
            continue;
        }
        switch(op) {
            case 1: consultaEstoqueTotal(); break;
            case 2: consultaEstoquePorProduto(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n");
        }
    } while(op != 0);
}

void MovimentarEstoque() {
    int busca;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Entrada no Estoque\n");
        printf("2. Baixa no Estoque\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &busca) != 1) {
            erroEntrada();
            continue;
        }
        switch(busca) {
            case 1: adicionarProduto(); break;
            case 2: baixaEstoque(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n");
        }
    } while(busca != 0);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Consultar Estoque\n");
        printf("3. Movimentar Estoque\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            erroEntrada();
            continue;
        }
        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: consultaEstoque(); break;
            case 3: MovimentarEstoque(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
}
