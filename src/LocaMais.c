#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_VEICULOS 100
#define MAX_LOCACOES 100

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// Estruturas para armazenar os dados

//----------Clientes-----------
typedef struct
{
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
} Cliente;

Cliente clientes[MAX_CLIENTES]; // Array para armazenar os clientes
int num_clientes = 0;           // Contador do número de clientes

// Função para verificar se um código de cliente já existe
int codigoExiste(int codigo)
{
    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].codigo == codigo)
        {
            return 1;
        }
    }
    return 0;
}
//----------------------------

//----------Veiculos----------
typedef struct
{
    int codigo;
    char descricao[100];
    char modelo[50];
    char cor[20];
    char placa[10];
    float valor_diaria;
    int ocupantes;
    char status[15]; // alugado, disponível, em manutenção
} Veiculo;

Veiculo veiculos[MAX_VEICULOS]; // Array para armazenar os veículos
int num_veiculos = 0;           // Contador do número de veículos

// Função para verificar se um código de veículo já existe
int codigoVeiculoExiste(int codigo)
{
    for (int i = 0; i < num_veiculos; i++)
    {
        if (veiculos[i].codigo == codigo)
        {
            return 1;
        }
    }
    return 0;
}
//----------------------------

//----------Locacao-----------
typedef struct
{
    int codigo;
    char data_retirada[10];
    char data_devolucao[10];
    int seguro; // 0 para não, 1 para sim
    int dias;
    int codigo_cliente;
    int codigo_veiculo;
} Locacao;

Locacao locacoes[MAX_LOCACOES]; // Array para armazenar as locações
int num_locacoes = 0;           // Contador do número de locações

// Funções para cadastrar um cliente, um veículo e uma locação

// Função para cadastrar um cliente
void cadastrarCliente()
{
    if (num_clientes >= MAX_CLIENTES)
    {
        printf("Não é possível cadastrar mais clientes.\n");
        return;
    }

    Cliente novo_cliente;
    printf("Digite o código do cliente: ");
    scanf("%d", &novo_cliente.codigo);

    // Verificar se o código já existe
    while (codigoExiste(novo_cliente.codigo))
    {
        printf("Este código já existe. Por favor, digite um novo código: ");
        scanf("%d", &novo_cliente.codigo);
    }

    printf("Digite o nome do cliente: ");
    scanf("%s", novo_cliente.nome);
    printf("Digite o endereço do cliente: ");
    scanf("%s", novo_cliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf("%s", novo_cliente.telefone);

    // Adicionar o novo cliente ao array de clientes
    clientes[num_clientes] = novo_cliente;
    num_clientes++;
}

// Função para cadastrar um veículo
void cadastrarVeiculo()
{
    if (num_veiculos >= MAX_VEICULOS)
    {
        printf("Não é possível cadastrar mais veículos.\n");
        return;
    }

    Veiculo novo_veiculo;
    printf("Digite o código do veículo: ");
    scanf("%d", &novo_veiculo.codigo);

    // Verificar se o código já existe
    while (codigoVeiculoExiste(novo_veiculo.codigo))
    {
        printf("Este código já existe. Por favor, digite um novo código: ");
        scanf("%d", &novo_veiculo.codigo);
    }

    printf("Digite a descrição do veículo: ");
    scanf("%s", novo_veiculo.descricao);
    printf("Digite o modelo do veículo: ");
    scanf("%s", novo_veiculo.modelo);
    printf("Digite a cor do veículo: ");
    scanf("%s", novo_veiculo.cor);
    printf("Digite a placa do veículo: ");
    scanf("%s", novo_veiculo.placa);
    printf("Digite o valor da diária do veículo: ");
    scanf("%f", &novo_veiculo.valor_diaria);
    printf("Digite a quantidade de ocupantes do veículo: ");
    scanf("%d", &novo_veiculo.ocupantes);
    printf("Digite o status do veículo: ");
    scanf("%s", novo_veiculo.status);

    // Adicionar o novo veículo ao array de veículos
    veiculos[num_veiculos] = novo_veiculo;
    num_veiculos++;
}

// Função para cadastrar uma locação
void cadastrarLocacao()
{
    if (num_locacoes >= MAX_LOCACOES)
    {
        printf("Não é possível cadastrar mais locações.\n");
        return;
    }

    Locacao nova_locacao;
    printf("Digite o código da locação: ");
    scanf("%d", &nova_locacao.codigo);
    printf("Digite a data de retirada: ");
    scanf("%s", nova_locacao.data_retirada);
    printf("Digite a data de devolução: ");
    scanf("%s", nova_locacao.data_devolucao);
    char opcao;
    printf("Deseja um seguro? (s/n): ");
    scanf(" %c", &opcao);
    nova_locacao.seguro = (opcao == 's' || opcao == 'S') ? 1 : 0;
    printf("Digite a quantidade de dias: ");
    scanf("%d", &nova_locacao.dias);
    printf("Digite o código do cliente: ");
    scanf("%d", &nova_locacao.codigo_cliente);
    printf("Digite o código do veículo: ");
    scanf("%d", &nova_locacao.codigo_veiculo);

    // Verificar se o cliente e o veículo estão cadastrados
    if (!codigoExiste(nova_locacao.codigo_cliente) || !codigoVeiculoExiste(nova_locacao.codigo_veiculo))
    {
        printf("Cliente ou veículo não cadastrados.\n");
        return;
    }

    // Verificar se o veículo está disponível
    for (int i = 0; i < num_veiculos; i++)
    {
        if (veiculos[i].codigo == nova_locacao.codigo_veiculo)
        {
            if (strcmp(veiculos[i].status, "disponível") != 0)
            {
                printf("Veículo não disponível.\n");
                return;
            }
            break;
        }
    }

    // Adicionar a nova locação ao array de locações
    locacoes[num_locacoes] = nova_locacao;
    num_locacoes++;
}

// Função main que exibe um menu na tela
int main()
{
    int opcao;
    do {
        printf("\nMenu de opções:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar veículo\n");
        printf("3. Cadastrar locação\n");
        printf("4. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarVeiculo();
                break;
            case 3:
                cadastrarLocacao();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 4);

    return 0;
}
