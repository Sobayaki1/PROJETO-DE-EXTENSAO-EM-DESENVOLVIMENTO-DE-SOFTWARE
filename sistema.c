#include <stdio.h>
#include <string.h>
#include <windows.h>

int opcao;

typedef struct{ 

    char nomeResponsavel;
    float idEmpresa;
    char cnpj;
    char endereço ;
    char telefone [15];
    char empresa [100];
    char email [100];
    
}remetente;

typedef struct{ //struct de item, com typedef para nao necessitar chamar struct toda vez

    int idProduto;
    char nomeProduto[100];
    char categoria[100];
    float preço;
    float peso;
    float cubagem;
    
}produto;

produto estoque [100];
int totalProdutos = 0;

typedef struct{ 
    
    int idPedido;
    char nomeCliente [100];
    int idProduto;
    char nomeProduto [100];
    float quantidade;
    float preçoTotal;
    
}pedido;


void cadastrarProduto(){ //cadastra um produto, cria um id
    
    
    produto p;
    
    p.idProduto = totalProdutos + 1; 

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", p.nomeProduto);
    
    printf("Categoria: ");
    scanf(" %[^\n]", p.categoria);
    
    printf("Preco: ");
    scanf("%f", &p.preço);

    printf("Cubagem: ");
    scanf("%f", &p.cubagem);
    
    printf("Peso: ");
    scanf("%f", &p.peso);

    estoque[totalProdutos] = p;
    totalProdutos++;

}

void adicionarProduto(){ //adiciona produto ao estoque
    
}

void cadastrarPedido(){ //cadastra pedido, com item e cria um id
  
}

void consultaEstoqueTotal() {
    if (totalProdutos == 0) {
        printf("\nO estoque esta vazio!\n");
        return;
    }

    printf("\n%-5s | %-20s | %-15s | %-10s | %-10s\n", "ID", "NOME", "CATEGORIA", "PRECO", "PESO");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < totalProdutos; i++) {
        // Usamos i+1 para o ID se você quiser um número sequencial simples
        printf("%-5d | %-20s | %-15s | R$%-8.2f | %-8.2fkg\n", 
                i + 1, 
                estoque[i].nomeProduto, 
                estoque[i].categoria, 
                estoque[i].preço, 
                estoque[i].peso);
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
        // Agora o estoque[i].idProduto terá o valor 1, 2, 3...
        if (estoque[i].idProduto == idBusca) {
            printf("\n--- Produto Encontrado ---\n");
            printf("ID: %d | Nome: %s | Preco: R$%.2f\n", 
                    estoque[i].idProduto, 
                    estoque[i].nomeProduto, 
                    estoque[i].preço);
            encontrado = 1;
            break; 
        }
    }

    if (!encontrado) {
        printf("\nErro: Produto com ID %d nao encontrado.\n", idBusca);
    }
}

void consultaEstoque(){ //Caio** mostra itens de estoque e da opcao de busca
    int op;
    produto p;

    do{
        printf("\n=== MENU ===\n");
        printf("1. Consultar Estoque Geral\n");
        printf("2. Consultar Estoque por Produto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                consultaEstoqueTotal();
                break;
            case 2:
                consultaEstoquePorProduto();
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(op != 0);
}

void baixaEstoque(){ //da baixa em produto baseado no pedido e atualiza esqtoque
  
}

int main(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    do{
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Consultar Estoque\n");
        printf("3. Baixa no estoque\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                consultaEstoque();
                break;
            case 3:
                baixaEstoque();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
