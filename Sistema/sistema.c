#include <stdio.h>
#include <string.h>

int opcao;

// Estrutura para guardar os dados da nossa empresa/remetente
typedef struct {
    char nomeResponsavel[100];
    int idEmpresa;
    char cnpj[20];
    char endereco[100];
    char telefone[15];
    char empresa[100];
    char email[100];
} remetente;

// Estrutura com as propriedades essenciais de cada produto
typedef struct {
    int idProduto;
    char nomeProduto[100];
    char category[100];
    float preco;
    float peso;
    float cubagem;
    int quantidade;
} produto;

// Nosso estoque físico simulado por um array (limite de 100 tipos de produtos)
produto estoque[100];
int totalProdutos = 0;

// Estrutura para registrar as vendas/pedidos dos clientes
typedef struct {
    int idPedido;
    char nomeCliente[100];
    int idProduto;
    char nomeProduto[100];
    float quantidade;
    float precoTotal;
} pedido;

// Histórico para armazenar os pedidos realizados
pedido listaPedidos[100];
int totalPedidos = 0;

// Função auxiliar para limpar o buffer do teclado e tratar erros de digitação do usuário
void erroEntrada() {
    printf("\nEntrada invalida! Por favor, tente novamente.\n");
    while (getchar() != '\n');
}

// Cria um novo produto no sistema com ID automático, validando as entradas numéricas
void cadastrarProduto() {
    produto p;
    p.idProduto = totalProdutos + 1; // ID gerado automaticamente com base no total atual
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", p.nomeProduto);
    printf("Categoria: ");
    scanf(" %[^\n]", p.categoria);
    
    // Loops 'do-while' para garantir que o usuário digite valores numéricos válidos
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
    
    p.quantidade = 0; // Todo produto novo começa com estoque zerado
    estoque[totalProdutos] = p;
    totalProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

// Adiciona unidades ao estoque de um produto já cadastrado (Entrada de mercadoria)
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
        // Varre o array procurando o ID correspondente
        for (int i = 0; i < totalProdutos; i++) {
            if (estoque[i].idProduto == idBusca) {
                printf("\n--- Produto Encontrado ---\n");
                printf("ID: %d | Nome: %s | Preco: R$%.2f | Quantidade: %d\n", 
                        estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].preco, estoque[i].quantidade);
                int quantidadeAdicionar;
                printf("Quantas unidades deseja adicionar? (0 para voltar): ");
                if (scanf("%d", &quantidadeAdicionar) == 1) {
                    if (quantidadeAdicionar == 0) {
                        printf("Operacao cancelada.\n");
                    } else {
                        estoque[i].quantidade += quantidadeAdicionar; // Soma as novas unidades ao saldo atual
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

// Remove unidades do estoque manualmente (Útil para perdas, avarias ou ajustes)
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
                        estoque[i].quantidade -= quantidadeBaixa; // Deduz a quantidade do estoque
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

// Realiza a venda de um produto: valida estoque, calcula preço total e abate do saldo físico
void cadastrarPedido() {
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio! cadastre um produto.\n");
        return;
    }

    if (totalPedidos >= 100) {
        printf("\nLimite de pedidos atingido!\n");
        return;
    }

    int idBusca;
    int encontrado = 0;

    printf("\n--- Novo Pedido ---\n");
    printf("Digite o ID do produto desejado: ");
    if (scanf("%d", &idBusca) != 1) {
        erroEntrada();
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].idProduto == idBusca) {
            encontrado = 1;
            printf("Produto: %s | Preco: R$%.2f | Estoque: %d unidades\n", 
                    estoque[i].nomeProduto, estoque[i].preco, estoque[i].quantidade);
            int quantidadePedido;
            if (estoque[i].quantidade <= 0) {
                printf("Produto sem estoque disponivel!\n");
                return;
            }
            printf("Quantas unidades deseja pedir? ");
            if (scanf("%d", &quantidadePedido) != 1) {
                erroEntrada();
                return;
            }
            if (quantidadePedido <= 0) {
                printf("Quantidade invalida!\n");
                return;
            }
            if (quantidadePedido > estoque[i].quantidade) {
                printf("Erro: Quantidade solicitada excede o estoque disponivel!\n");
                return;
            }

            // Monta o registro do pedido se todas as validações passarem
            pedido p;
            p.idPedido = totalPedidos + 1;
            printf("Digite o nome do cliente: ");
            scanf(" %[^\n]", p.nomeCliente);
            p.idProduto = estoque[i].idProduto;
            strcpy(p.nomeProduto, estoque[i].nomeProduto);
            p.quantidade = quantidadePedido;
            p.precoTotal = quantidadePedido * estoque[i].preco; // Multiplica quantidade pelo preço unitário

            listaPedidos[totalPedidos] = p; // Salva o pedido no nosso histórico de vendas
            totalPedidos++;

            estoque[i].quantidade -= quantidadePedido; // Dá baixa automática no estoque por conta da venda

            printf("\n--- Venda Finalizada com Sucesso ---\n");
            printf("Pedido #%d registrado para o cliente: %s\n", p.idPedido, p.nomeCliente);
            printf("Total a pagar: R$%.2f\n", p.precoTotal);
            printf("Estoque atualizado! Novo saldo de %s: %d unidades\n", estoque[i].nomeProduto, estoque[i].quantidade);
            
            break;
        }
    }

    if (!encontrado) {
        printf("\nErro: Produto com ID %d nao encontrado.\n", idBusca);
    }
}

// Subfunção para listar de forma tabular absolutamente tudo o que está cadastrado no estoque
void consultaEstoqueTotal() {
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio!\n");
        return;
    }
    printf("\n%-5s | %-20s | %-15s | %-10s | %-10s | %-10s\n", "ID", "NOME", "CATEGORIA", "PRECO", "PESO", "QUANTIDADE");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%-5d | %-20s | %-15s | R$%-8.2f | %-8.2fkg | %-10d\n", 
                estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].categoria, 
                estoque[i].preco, estoque[i].peso, estoque[i].quantidade);
    }
}

// Subfunção para buscar e exibir os dados detalhados de um produto específico filtrando por ID
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
            printf("ID: %d | Nome: %s | Preco: R$%.2f | Quantidade: %d\n", 
                    estoque[i].idProduto, estoque[i].nomeProduto, estoque[i].preco, estoque[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("\nErro: Produto com ID %d nao encontrado.\n", idBusca);
}

// Menu intermediário para o usuário escolher entre a listagem geral ou busca individual
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

// Menu intermediário para centralizar as operações de entrada e saída física de mercadorias
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

// Ponto de entrada do programa. Controla o fluxo principal através do switch-case dentro do loop global
int main() {
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Consultar Estoque\n");
        printf("3. Movimentar Estoque\n");
        printf("4. Cadastrar Pedido\n");
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
            case 4: cadastrarPedido(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
}
