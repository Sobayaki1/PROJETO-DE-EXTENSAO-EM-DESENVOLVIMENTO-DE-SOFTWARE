#include <stdio.h>
#include <string.h>

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
    p.idProduto++;

}

void adicionarProduto(){ //adiciona produto ao estoque
    
}

void cadastrarPedido(){ //cadastra pedido, com item e cria um id
  
}

void consultaEstoque(){ //Caio** mostra itens de estoque e da opcao de busca
   
}

void baixaEstoque(){ //da baixa em produto baseado no pedido e atualiza esqtoque
  
}

int main(){

    do{
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Buscar produto\n");
        printf("4. Baixa no estoque\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listaritem();
                break;
            case 3:
                buscar();
                break;
            case 4:
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
