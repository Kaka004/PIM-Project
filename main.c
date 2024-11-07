#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUTOS 100
#define MAX_VENDAS 100

typedef struct {
    char nome[50];
    float preco;
    int codigo;
    int quantidade;
} Produto;

typedef struct {
    char nomeCliente[50];
    Produto produtosComprados[MAX_PRODUTOS];
    int quantidadeComprados[MAX_PRODUTOS];
    int totalItens;
    float totalVenda;
    float valorPago;
    float troco;
} Venda;

Produto produtos[MAX_PRODUTOS];
Venda vendas[MAX_VENDAS];
int totalProdutos = 0;
int totalVendas = 0;
float saldoCaixa = 100.00;

void inicializarProdutos();
void cadastrarProduto();
void atualizarEstoque();
void realizarVenda();
void consultarEstoque();
void fluxoDeCaixa();
void excluirProduto();
void sair();
void exibirMenu();
void limparConsole();
void voltarAoMenu();

int main() {
    inicializarProdutos();
    int opcao;

    do {
        limparConsole();
        exibirMenu();
        scanf("%d", &opcao);
        while (getchar() != '\n');

        limparConsole();

        switch (opcao) {
            case 1:
                realizarVenda();
                break;
            case 2:
                consultarEstoque();
                break;
            case 3:
                cadastrarProduto();
                break;
            case 4:
                atualizarEstoque();
                break;
            case 5:
                fluxoDeCaixa();
                break;
            case 6:
                excluirProduto();
                break;
            case 0:
                sair();
                break;
            default:
                printf("Opcao invalida. Tente novamente\n");
                voltarAoMenu();
        }

    } while (opcao != 0);

    return 0;
}

void inicializarProdutos() {
    Produto fruta1 = {"Banana", 5.00, 1, 50};
    Produto fruta2 = {"Maca", 8.00, 2, 40};
    Produto fruta3 = {"Laranja", 4.00, 3, 30};
    Produto fruta4 = {"Abacaxi", 6.50, 4, 20};
    Produto fruta5 = {"Manga", 7.00, 5, 10};

    produtos[totalProdutos++] = fruta1;
    produtos[totalProdutos++] = fruta2;
    produtos[totalProdutos++] = fruta3;
    produtos[totalProdutos++] = fruta4;
    produtos[totalProdutos++] = fruta5;
}

void cadastrarProduto()
{
    if (totalProdutos < MAX_PRODUTOS) {
        Produto novoProduto;
        FILE *file = fopen("produtos.txt", "a");

        if (file == NULL) {
            printf("Erro ao abrir o arquivo de produtos.\n");
            return;
        }

        printf("Digite o nome do produto: ");
        fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
        novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

        // Verificar se o preço é válido
        do {
            printf("Digite o preco do produto (positivo): ");
            scanf("%f", &novoProduto.preco);
            if (novoProduto.preco <= 0) {
                printf("O preço deve ser positivo.\n");
            }
        } while (novoProduto.preco <= 0);

        // Verificação de código duplicado
        int codigoValido;
int i; // Declarar i antes do laço for
do {
    codigoValido = 1;
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigo);

    for (i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == novoProduto.codigo) {
            printf("Código já existente. Insira um código único.\n");
            codigoValido = 0;
            break;
        }
    }
} while (!codigoValido);


        // Verificar se a quantidade é válida
        do {
            printf("Digite a quantidade do produto (positiva): ");
            scanf("%d", &novoProduto.quantidade);
            if (novoProduto.quantidade < 0) {
                printf("A quantidade deve ser positiva.\n");
            }
        } while (novoProduto.quantidade < 0);

        // Escreve o produto no arquivo
        fprintf(file, "%s %f %d %d\n", novoProduto.nome, novoProduto.preco, novoProduto.codigo, novoProduto.quantidade);

        fclose(file);

        // Atualiza o array de produtos
        produtos[totalProdutos] = novoProduto;
        totalProdutos++;

        printf("Produto cadastrado com sucesso e salvo em arquivo.\n");
    } else {
        printf("Limite de produtos atingido.\n");
    }

    voltarAoMenu();
}


void atualizarEstoque()
{
    int opcao;
    int codigoProduto, quantidade;
    int i;
    printf("\n(1) Adicionar ao estoque\n");
    printf("(2) Remover do estoque\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Digite o codigo do produto para adicionar: ");
        scanf("%d", &codigoProduto);
        for (i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoProduto) {
                printf("Produto encontrado: %s\n", produtos[i].nome);
                printf("Digite a quantidade para adicionar: ");
                scanf("%d", &quantidade);
                produtos[i].quantidade += quantidade;
                printf("Quantidade atualizada: %d\n", produtos[i].quantidade);
                break;
            }
        }
    } else if (opcao == 2) {
        printf("Digite o codigo do produto para remover: ");
        scanf("%d", &codigoProduto);
        for (i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoProduto) {
                printf("Produto encontrado: %s\n", produtos[i].nome);
                printf("Digite a quantidade para remover: ");
                scanf("%d", &quantidade);
                if (quantidade <= produtos[i].quantidade) {
                    produtos[i].quantidade -= quantidade;
                    printf("Quantidade atualizada: %d\n", produtos[i].quantidade);
                } else {
                    printf("Quantidade insuficiente no estoque\n");
                }
                break;
            }
        }
    } else {
        printf("Opcao invalida\n");
    }

    voltarAoMenu();
}


void realizarVenda()
{
    if (totalProdutos == 0)
    {
        printf("Nenhum produto cadastrado para realizar venda.\n");
        voltarAoMenu();
        return;
    }

    int codigoProduto;
    float quantidadeKg;
    int i;
    float totalVenda = 0.0f;
    char continuar = 's';

    Venda novaVenda;
    novaVenda.totalItens = 0;

    printf("Digite o nome do cliente: ");
    while (getchar() != '\n');
    fgets(novaVenda.nomeCliente, sizeof(novaVenda.nomeCliente), stdin);
    novaVenda.nomeCliente[strcspn(novaVenda.nomeCliente, "\n")] = '\0';

    // Exibir a lista de produtos disponíveis
    printf("Produtos disponiveis:\n");
    printf("%-20s %-10s %-15s %-10s\n", "Nome", "Codigo", "Valor (R$/kg)", "Quantidade (kg)");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < totalProdutos; i++) {
        printf("%-20s %-10d R$%-13.2f %-10d\n",
               produtos[i].nome,
               produtos[i].codigo,
               produtos[i].preco,
               produtos[i].quantidade);
    }
printf("\n");

    do
    {
        int produtoEncontrado = 0;

        while (!produtoEncontrado)
        {
            printf("Digite o codigo do produto: ");
            scanf("%d", &codigoProduto);

            for (i = 0; i < totalProdutos; i++)
            {
                if (produtos[i].codigo == codigoProduto)
                {
                    produtoEncontrado = 1;
                    printf("Produto encontrado: %s - Preco: R$%.2f\n", produtos[i].nome, produtos[i].preco);

                    // Valida a quantidade solicitada em Kg
                    do {
                        printf("Digite a quantidade em Kg (disponivel: %d kg): ", produtos[i].quantidade);
                        scanf("%f", &quantidadeKg);

                        if (quantidadeKg <= 0) {
                            printf("A quantidade deve ser um valor positivo.\n");
                        } else if (quantidadeKg > produtos[i].quantidade) {
                            printf("Quantidade em estoque insuficiente. Tente uma quantidade menor.\n");
                        }
                    } while (quantidadeKg <= 0 || quantidadeKg > produtos[i].quantidade);

                    // Processa a venda se a quantidade for válida
                    int quantidadeInteira = (int)quantidadeKg; // Converte para int
                    float subtotal = produtos[i].preco * quantidadeInteira;
                    totalVenda += subtotal;
                    produtos[i].quantidade -= quantidadeInteira;

                    novaVenda.produtosComprados[novaVenda.totalItens] = produtos[i];
                    novaVenda.quantidadeComprados[novaVenda.totalItens] = quantidadeInteira;
                    novaVenda.totalItens++;

                    printf("Subtotal: R$%.2f\n", subtotal);
                    break;
                }
            }

            if (!produtoEncontrado) {
                printf("Produto com codigo %d nao encontrado. Tente novamente.\n", codigoProduto);
            }
        }

        printf("Deseja adicionar outro produto a venda? (s/n): ");
        while (getchar() != '\n');
        scanf("%c", &continuar);

    } while (continuar == 's');

    printf("Total da venda: R$%.2f\n", totalVenda);

    float valorRecebido = 0.0f;
	do
	{
    printf("Digite o valor recebido: R$ ");
    scanf("%f", &valorRecebido);

    if (valorRecebido < 0) {
        printf("Erro: O valor recebido nao pode ser negativo.\n");
    } else if (valorRecebido < totalVenda) {
        printf("Valor insuficiente. Faltam R$%.2f para completar a venda.\n", totalVenda - valorRecebido);
        printf("Por favor, insira um novo valor.\n");
    }
} while (valorRecebido < totalVenda || valorRecebido < 0);


    float troco = valorRecebido - totalVenda;
    printf("Troco: R$%.2f\n", troco);

    saldoCaixa += totalVenda;
    saldoCaixa -= troco;

    novaVenda.totalVenda = totalVenda;
    novaVenda.valorPago = valorRecebido;
    novaVenda.troco = troco;

    vendas[totalVendas++] = novaVenda;

    voltarAoMenu();
}


void consultarEstoque()
{
    printf("Estoque atual:\n");
    printf("%-20s %-10s %-15s %-10s\n", "Nome", "Codigo", "Valor (R$/kg)", "Quantidade");
    printf("------------------------------------------------------------\n");

    int i;
    for (i = 0; i < totalProdutos; i++) {
        printf("%-20s %-10d R$%-13.2f %-10d\n",
               produtos[i].nome,
               produtos[i].codigo,
               produtos[i].preco,
               produtos[i].quantidade);
    }

    voltarAoMenu();
}


void fluxoDeCaixa()
{
    if (totalVendas == 0) {
        printf("Nenhuma venda realizada ate o momento.\n");
        printf("Saldo atual do caixa: R$%.2f\n", saldoCaixa);
        voltarAoMenu();
        return;
    }

    printf("Relatorio de vendas:\n");
    printf("%-20s %-10s %-15s %-10s\n", "Cliente", "Valor Pago", "Total Venda", "Troco");
    printf("------------------------------------------------------------\n");

    int i, j;
    for (i = 0; i < totalVendas; i++) {
        printf("%-20s R$%-9.2f R$%-12.2f R$%-9.2f\n",
               vendas[i].nomeCliente,
               vendas[i].valorPago,
               vendas[i].totalVenda,
               vendas[i].troco);

        printf("Itens comprados:\n");
        for (j = 0; j < vendas[i].totalItens; j++) {
            printf("  %s - Quantidade: %d\n",
                   vendas[i].produtosComprados[j].nome,
                   vendas[i].quantidadeComprados[j]);
        }
        printf("------------------------------------------------------------\n");
    }

    printf("Saldo atual do caixa: R$%.2f\n", saldoCaixa);

    voltarAoMenu();
}


void excluirProduto() {
    int opcao, codigoProduto, quantidade, i, j, produtoEncontrado = 0;

    printf("\n(1) Excluir produto por completo\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Digite o codigo do produto a ser excluido: ");
        scanf("%d", &codigoProduto);

        for (i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoProduto) {
                for (j = i; j < totalProdutos - 1; j++) {
                    produtos[j] = produtos[j + 1];
                }
                totalProdutos--;
                produtoEncontrado = 1;
                printf("Produto excluido com sucesso!\n");
                break;
            }
        }

        if (!produtoEncontrado) {
            printf("Produto com codigo %d não encontrado.\n", codigoProduto);
        }

    }  else {
        printf("Opção invalida.\n");
    }

    voltarAoMenu();
}

void sair() {
    printf("Saindo do sistema\n");
}

void exibirMenu() {
    printf("\n----------------------------\n");
    printf("|       Bioconnect         |\n");
    printf("|--------------------------|\n");
    printf("| (1) Realizar Venda       |\n");
    printf("| (2) Consultar Estoque    |\n");
    printf("| (3) Cadastrar Produto    |\n");
    printf("| (4) Atualizar Estoque    |\n");
    printf("| (5) Fluxo de Caixa       |\n");
    printf("| (6) Excluir Produto      |\n");
    printf("| (0) Sair                 |\n");
    printf("----------------------------\n");
    printf("Escolha uma opcao: ");
}

void limparConsole() {
    system("cls");
}

void voltarAoMenu() {
    int opcao;
    printf("\n(1) Voltar ao menu\n");
    printf("(2) Fechar o programa\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
    } else if (opcao == 2) {
        sair();
        exit(0);
    } else {
        printf("Opcao invalida, voltando ao menu...\n");
}
}
