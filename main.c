#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto estoque[MAX_PRODUTOS];
int totalProdutos = 0;

void cadastrarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\n[ERRO] Limite de armazenamento de produtos atingido!\n");
        return;
    }

    Produto p;
    p.id = totalProdutos + 1;

    printf("\n--- CADASTRO DE PRODUTO ---\n");
    printf("Nome do produto: ");
    scanf(" %[^\n]", p.nome);
    printf("Quantidade em estoque: ");
    scanf("%d", &p.quantidade);
    printf("Preco unitario (R$): ");
    scanf("%f", &p.preco);

    estoque[totalProdutos] = p;
    totalProdutos++;

    printf("[SUCESSO] Produto '%s' cadastrado com ID %d!\n", p.nome, p.id);
}

void listarEstoque() {
    printf("\n=======================================================\n");
    printf("                 RELATORIO DE ESTOQUE                  \n");
    printf("=======================================================\n");
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado no sistema.\n");
        return;
    }

    printf("%-5s %-25s %-12s %-10s\n", "ID", "Nome", "Quantidade", "Preco (R$)");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%-5d %-25s %-12d R$ %-8.2f\n", 
               estoque[i].id, estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }
    printf("-------------------------------------------------------\n");
}

void registrarVenda() {
    int id, qtdVenda;
    printf("\n--- REGISTRO DE VENDA E EMISSAO ---\n");
    printf("Informe o ID do produto: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[ERRO] Produto nao encontrado!\n");
        return;
    }

    printf("Produto selecionado: %s (Estoque atual: %d)\n", estoque[index].nome, estoque[index].quantidade);
    printf("Quantidade a vender: ");
    scanf("%d", &qtdVenda);

    if (qtdVenda <= 0 || qtdVenda > estoque[index].quantidade) {
        printf("[ERRO] Quantidade invalida ou estoque insuficiente!\n");
        return;
    }

    // Atualiza estoque
    estoque[index].quantidade -= qtdVenda;

    // Calculo financeiro
    float subtotal = qtdVenda * estoque[index].preco;
    float impostoICMS = subtotal * 0.18f; // Aliquota ficticia de 18%
    float totalGeral = subtotal;

    // Impressao de comprovante / nota
    printf("\n=======================================================\n");
    printf("                   COMPROVANTE DE VENDA                \n");
    printf("=======================================================\n");
    printf("Item: %s\n", estoque[index].nome);
    printf("Quantidade vendida: %d\n", qtdVenda);
    printf("Preco unitario: R$ %.2f\n", estoque[index].preco);
    printf("Subtotal: R$ %.2f\n", subtotal);
    printf("ICMS Estimado (18%% embutido): R$ %.2f\n", impostoICMS);
    printf("-------------------------------------------------------\n");
    printf("TOTAL DA OPERACAO: R$ %.2f\n", totalGeral);
    printf("=======================================================\n");
    printf("[SUCESSO] Venda registrada e estoque atualizado!\n");
}

int main() {
    int opcao;

    // Dados para inicializar o sistema com itens de teste
    estoque[0] = (Produto){1, "Roteador Wi-Fi AC1200", 15, 215.00f};
    estoque[1] = (Produto){2, "Cabo de Rede UTP Cat6 1m", 50, 12.50f};
    totalProdutos = 2;

    do {
        printf("\n=== SISTEMA DE GESTAO DE ESTOQUE E VENDAS ===\n");
        printf("1. Cadastrar Novo Produto\n");
        printf("2. Listar Estoque\n");
        printf("3. Registrar Venda (Emitir Comprovante)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarEstoque();
                break;
            case 3:
                registrarVenda();
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
