#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_VEICULOS 100
#define MAX_LOCACOES 100

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

int calcularDiferencaDatas(char* data1, char* data2);

// Estruturas para armazenar os dados

//----------Clientes-----------
typedef struct
{
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int pontosFidelidade;
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
    int status; // 0 para disponível, 1 para alugado, 2 para em manutenção
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
    char data_retirada[11];
    char data_devolucao[11];
    int seguro; // 0 para não, 1 para sim
    int dias;
    int codigo_cliente;
    int codigo_veiculo;
    float valorTotal;
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

    printf("Cliente cadastrado com sucesso.");
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
    novo_veiculo.status = 0; // Veículo disponível por padrão

    // Adicionar o novo veículo ao array de veículos
    veiculos[num_veiculos] = novo_veiculo;
    num_veiculos++;

    printf("Veículo cadastrado com sucesso.");
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
    nova_locacao.dias = calcularDiferencaDatas(nova_locacao.data_retirada, nova_locacao.data_devolucao);
    char opcao;
    printf("Deseja um seguro? (s/n): ");
    scanf(" %c", &opcao);
    nova_locacao.seguro = (opcao == 's' || opcao == 'S') ? 1 : 0;
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
for (int i = 0; i < num_veiculos; i++) {
    if (veiculos[i].codigo == nova_locacao.codigo_veiculo) {
        if (veiculos[i].status != 0) { // 0 para disponível
            printf("Veículo não disponível.\n");
            return;
        }
        nova_locacao.valorTotal = nova_locacao.dias * veiculos[i].valor_diaria + (nova_locacao.seguro ? 50 : 0);
        break;
    }
}

    // Encontrar o cliente e adicionar pontos de fidelidade
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].codigo == nova_locacao.codigo_cliente) {
            clientes[i].pontosFidelidade += nova_locacao.dias * 10;
            break;
        }
    }

    // Adicionar a nova locação ao array de locações
    locacoes[num_locacoes] = nova_locacao;
    num_locacoes++;
}

// Função para encontrar uma locação por código de cliente
int encontrarLocacaoPorCliente(int codigo_cliente) {
    for (int i = 0; i < num_locacoes; i++) {
        if (locacoes[i].codigo_cliente == codigo_cliente) {
            return i;
        }
    }
    return -1;
}

// Função para calcular a diferença entre duas datas
int calcularDiferencaDatas(char* data1, char* data2) {
    struct tm tm1, tm2;
    time_t t1, t2;

    // Converter as datas para struct tm
    sscanf(data1, "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
    sscanf(data2, "%d/%d/%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);

    // Ajustar os valores lidos
    tm1.tm_year -= 1900; // O ano é contado a partir de 1900
    tm1.tm_mon--; // Os meses são contados de 0 a 11
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 0;
    tm1.tm_isdst = -1;

    tm2.tm_year -= 1900;
    tm2.tm_mon--;
    tm2.tm_hour = 0;
    tm2.tm_min = 0;
    tm2.tm_sec = 0;
    tm2.tm_isdst = -1;

    // Converter struct tm para time_t
    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    // Calcular a diferença em segundos
    double diferenca = difftime(t2, t1);

    // Converter a diferença para dias
    return diferenca / (60 * 60 * 24);
}

// Função para devolução de carro
void devolucaoCarro() {
    int codigo_cliente;
    printf("Digite o código do cliente: ");
    scanf("%d", &codigo_cliente);

    // Encontrar a locação do cliente
    int indice_locacao = encontrarLocacaoPorCliente(codigo_cliente);
    if (indice_locacao == -1) {
        printf("Cliente não possui um carro alugado.\n");
        return;
    }

    char data_entrega[10];
    printf("Digite a data de entrega: ");
    scanf("%s", data_entrega);

    // Calcular a diferença entre a data de entrega e a data de devolução
    int atraso = calcularDiferencaDatas(data_entrega, locacoes[indice_locacao].data_devolucao);
    if (atraso > 0) {
        // Calcular a multa por atraso
        float multa = locacoes[indice_locacao].valorTotal * 1.05 + 30 * atraso;
        locacoes[indice_locacao].valorTotal += multa;
        printf("Atraso na entrega. Multa de R$ %.2f aplicada.\n", multa);
    }

    // Recalcular o valor total com base na quantidade real de dias
    int dias_real = calcularDiferencaDatas(locacoes[indice_locacao].data_retirada, data_entrega);
    for (int i = 0; i < num_veiculos; i++) {
        if (veiculos[i].codigo == locacoes[indice_locacao].codigo_veiculo) {
            locacoes[indice_locacao].valorTotal = dias_real * veiculos[i].valor_diaria + (locacoes[indice_locacao].seguro ? 50 : 0);
            break;
        }
    }

    printf("Valor total a ser pago: R$ %.2f\n", locacoes[indice_locacao].valorTotal);

    // Alterar o status do veículo para disponível
    for (int i = 0; i < num_veiculos; i++) {
        if (veiculos[i].codigo == locacoes[indice_locacao].codigo_veiculo) {
            veiculos[i].status = 0;
            break;
        }
    }

    // Remover a locação
    for (int i = indice_locacao; i < num_locacoes - 1; i++) {
        locacoes[i] = locacoes[i + 1];
    }
    num_locacoes--;
}

// Função para pesquisar um cliente por código ou nome
void pesquisarCliente() {
    int codigo;
    char nome[50];

    printf("Digite o código ou nome do cliente: ");
    scanf("%s", nome);

    // Verificar se o usuário digitou um código ou nome
    if (sscanf(nome, "%d", &codigo) == 1) {
        // O usuário digitou um código
        for (int i = 0; i < num_clientes; i++) {
            if (clientes[i].codigo == codigo) {
                printf("Código: %d\n", clientes[i].codigo);
                printf("Nome: %s\n", clientes[i].nome);
                printf("Endereço: %s\n", clientes[i].endereco);
                printf("Telefone: %s\n", clientes[i].telefone);
                printf("Pontos de fidelidade: %d\n", clientes[i].pontosFidelidade);
                return;
            }
        }
    } else {
        // O usuário digitou um nome
        for (int i = 0; i < num_clientes; i++) {
            if (strcmp(clientes[i].nome, nome) == 0) {
                printf("Código: %d\n", clientes[i].codigo);
                printf("Nome: %s\n", clientes[i].nome);
                printf("Endereço: %s\n", clientes[i].endereco);
                printf("Telefone: %s\n", clientes[i].telefone);
                printf("Pontos de fidelidade: %d\n", clientes[i].pontosFidelidade);
                return;
            }
        }
    }

    printf("Cliente não encontrado.\n");
}

// Função para pesquisar um veículo por código
void pesquisarVeiculo() {
    int codigo;

    printf("Digite o código do veículo: ");
    scanf("%d", &codigo);

    for (int i = 0; i < num_veiculos; i++) {
        if (veiculos[i].codigo == codigo) {
            printf("Código: %d\n", veiculos[i].codigo);
            printf("Descrição: %s\n", veiculos[i].descricao);
            printf("Modelo: %s\n", veiculos[i].modelo);
            printf("Cor: %s\n", veiculos[i].cor);
            printf("Placa: %s\n", veiculos[i].placa);
            printf("Valor da diária: %.2f\n", veiculos[i].valor_diaria);
            printf("Quantidade de ocupantes: %d\n", veiculos[i].ocupantes);
            printf("Status: %s\n", veiculos[i].status == 0 ? "disponível" : veiculos[i].status == 1 ? "alugado" : "em manutenção");
            return;
        }
    }

    printf("Veículo não encontrado.\n");
}

// Função para mostrar todas as locações de um cliente
void mostrarLocacoesCliente() {
    int codigo_cliente;
    char nome[50];

    printf("Digite o código ou nome do cliente: ");
    scanf("%s", nome);

    // Verificar se o usuário digitou um código ou nome
    if (sscanf(nome, "%d", &codigo_cliente) == 1) {
        // O usuário digitou um código
        for (int i = 0; i < num_locacoes; i++) {
            if (locacoes[i].codigo_cliente == codigo_cliente) {
                printf("Código da locação: %d\n", locacoes[i].codigo);
                printf("Modelo do veículo: %s\n", veiculos[i].modelo);
                printf("Cor do veículo: %s\n", veiculos[i].cor);
                printf("Data inicial da locação: %s\n", locacoes[i].data_retirada);
                printf("Data de devolução: %s\n", locacoes[i].data_devolucao);
            }
        }
    } else {
        // O usuário digitou um nome
        for (int i = 0; i < num_clientes; i++) {
            if (strcmp(clientes[i].nome, nome) == 0) {
                for (int j = 0; j < num_locacoes; j++) {
                    if (locacoes[j].codigo_cliente == clientes[i].codigo) {
                        printf("Código da locação: %d\n", locacoes[j].codigo);
                        printf("Modelo do veículo: %s\n", veiculos[j].modelo);
                        printf("Cor do veículo: %s\n", veiculos[j].cor);
                        printf("Data inicial da locação: %s\n", locacoes[j].data_retirada);
                        printf("Data de devolução: %s\n", locacoes[j].data_devolucao);
                    }
                }
                break;
            }
        }
    }
}

// Função para mostrar todos os clientes com 500 ou mais pontos de fidelidade
void mostrarClientesFidelidade() {
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].pontosFidelidade >= 500) {
            printf("Código: %d\n", clientes[i].codigo);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Pontos de fidelidade: %d\n", clientes[i].pontosFidelidade);
        }
    }
}

// Função main que exibe um menu na tela
int main() {
    int opcao;
    do {
        printf("\nMenu de opções:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar veículo\n");
        printf("3. Cadastrar locação\n");
        printf("4. Devolução de carro\n");
        printf("5. Pesquisar cliente\n");
        printf("6. Pesquisar veículo\n");
        printf("7. Mostrar locações de um cliente\n");
        printf("8. Mostrar clientes com 500 ou mais pontos de fidelidade\n");
        printf("9. Sair\n");
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
                devolucaoCarro();
                break;
            case 5:
                pesquisarCliente();
                break;
            case 6:
                pesquisarVeiculo();
                break;
            case 7:
                mostrarLocacoesCliente();
                break;
            case 8:
                mostrarClientesFidelidade();
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 9);

    return 0;
}