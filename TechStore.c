#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_VENDAS 100

typedef struct {
  int codigo;
  char nome[50];
  float precoVenda;
  int quantidadeEstoque;
} Produto;

typedef struct {
  int codigoVenda;
  Produto produtoVendido;
  float valorTotal;
} Venda;

void cadastrarProduto(Produto produtos[], int *qtdProdutos) {
  printf("1. Cadastrar Produto\n");
  Produto novo;

  if (*qtdProdutos >= MAX_PRODUTOS) {
    printf("Erro. Não é possível cadastrar mais produtos.\n");
    return;
  }

  printf("Insira o codigo do produto: ");
  scanf("%d", &novo.codigo);

  if (novo.codigo <= 0) {
    printf("Digite um código válido!\n");
    return;
  }
  if (qtdProdutos) {
    for (int i = 0; i < *qtdProdutos; i++) {
      if (produtos[i].codigo == novo.codigo) {
        printf("Erro. Código já cadastrado em outro produto. Insira um código "
               "diferente.\n");
        return;
      }
    }
  }

  while (getchar() != '\n')
    ;

  printf("Insira o nome do produto: ");
  fgets(novo.nome, sizeof(novo.nome), stdin);
  novo.nome[strcspn(novo.nome, "\n")] = '\0';
  if (!strcmp(novo.nome, "")) {
    printf("Erro. Digite um nome válido!\n");
    return;
  }

  printf("Insira o preco de venda: ");
  scanf("%f", &novo.precoVenda);
  if (novo.precoVenda <= 0) {
    printf("Erro. Digite um preço válido!\n");
    return;
  }

  printf("Insira a quantidade em estoque: ");
  scanf("%d", &novo.quantidadeEstoque);

  if (novo.quantidadeEstoque < 0) {
    printf("Erro. Digite uma quantidade válida!\n");
    return;
  }

  produtos[*qtdProdutos] = novo;
  (*qtdProdutos)++;

  printf("Produto cadastrado.\n");
}

void registrarVenda(Venda vendas[], int *qtdVendas, Produto produtos[],
                    int *qtdProdutos) {
  printf("2. Registrar Venda\n");
  int qtd;
  int codigoProduto;

  if (*qtdVendas >= MAX_VENDAS) {
    printf("Erro. Não é possível registrar mais vendas.\n");
    return;
  };

  printf("Insira o código do produto vendido: ");
  scanf("%d", &codigoProduto);
  printf("Insira a quantidade vendida: ");
  scanf("%d", &qtd);

  if (qtd <= 0) {
    printf("Erro. Digite uma quantidade válida!\n");
    return;
  }

  for (int i = 0; i < *qtdProdutos; i++) {
    if (produtos[i].codigo == codigoProduto) {
      if (qtd > produtos[i].quantidadeEstoque) {
        printf("Erro. A quantidade excede o estoque disponível.\n");
        return;
      }
      Venda vendido;
      vendido.codigoVenda = *qtdVendas + 1;
      vendido.produtoVendido = produtos[i];
      vendido.valorTotal = qtd * produtos[i].precoVenda;

      produtos[i].quantidadeEstoque -= qtd;
      vendas[*qtdVendas] = vendido;
      (*qtdVendas)++;

      printf("Venda registrada com sucesso.\n");
      return;
    }
  }
  printf("Erro: Produto com código %d não encontrado.\n", codigoProduto);
}

void listarVendas(Venda vendas[], int *qtdVendas) {
  printf("4. Lista de Vendas Efetuadas.\n");
  if (!*qtdVendas) {
    printf("Nenhuma venda foi efetuada ainda.\n");
    return;
  }
  for (int i = 0; i < *qtdVendas; i++) {
    printf("Código de venda: %d\n", vendas[i].codigoVenda);
    printf("Código do produto vendido: %d\n", vendas[i].produtoVendido.codigo);
    printf("Nome do produto: %s\n", vendas[i].produtoVendido.nome);
    printf("Valor total vendido: R$ %.2f \n", vendas[i].valorTotal);
    printf("\n");
  }
}

void listarProdutosEmFalta(Produto produtos[], int *qtdProdutos) {
  printf("5. Lista de Produtos Em Falta\n");
  if (!*qtdProdutos) {
    printf("Não há produtos cadastrados.\n");
    return;
  }
  int cont = 0;
  for (int i = 0; i < *qtdProdutos; i++) {
    if (produtos[i].quantidadeEstoque == 0) {
      cont++;
      printf("Codigo do Produto: %d\n", produtos[i].codigo);
      printf("Nome do produto: %s\n", produtos[i].nome);
      printf("Preço de venda: R$%.2f\n", produtos[i].precoVenda);
      printf("Quantidade: %d\n", produtos[i].quantidadeEstoque);
      printf("\n");
    }
  }
  if (!cont) {
    printf("Não há produtos em falta.\n");
    return;
  }
}

void listarProdutos(Produto produtos[], int *qtdProdutos) {
  printf("3. Lista de Produtos Disponíveis\n");
  if (!*qtdProdutos) {
    printf("Cadastre ao menos um produto para exibir a lista.\n");
    return;
  }
  int cont = 0;
  for (int i = 0; i < *qtdProdutos; i++) {
    if (produtos[i].quantidadeEstoque > 0) {
      cont++;
      printf("Codigo do Produto %d: %d\n", i + 1, produtos[i].codigo);
      printf("Nome do produto: %s\n", produtos[i].nome);
      printf("Preço de venda: R$%.2f\n", produtos[i].precoVenda);
      printf("Quantidade em estoque: %d\n", produtos[i].quantidadeEstoque);
      printf("\n");
    }
  }
  if (!cont) {
    printf("Não há produtos disponíveis no momento.\n");
  }
}

void maisVendido(Produto produtos[], int qtdProdutos, Venda vendas[],
                 int qtdVendas) {
  printf("1. Produto Mais Vendido.\n");

  int contagem[MAX_PRODUTOS] = {0};

  if (!qtdVendas) {
    printf("Nenhum produto vendido ainda.\n");
    return;
  }

  for (int i = 0; i < qtdVendas; i++) {
    int codigoVenda = vendas[i].produtoVendido.codigo;
    float valorTotal = vendas[i].valorTotal;

    for (int j = 0; j < qtdProdutos; j++) {
      if (produtos[j].codigo == codigoVenda) {
        float preco = vendas[i].produtoVendido.precoVenda;

        int qtdVendida = (int)((valorTotal / preco) + 0.5f);
        contagem[j] += qtdVendida;
        break;
      }
    }
  }
  int maxIndice = 0;
  for (int i = 1; i < qtdProdutos; i++) {
    if (contagem[i] > contagem[maxIndice]) {
      maxIndice = i;
    }
  }

  if (contagem[maxIndice] == 0) {
    printf("Nenhum produto foi vendido ainda.\n");
    return;
  }

  printf("Nome: %s\n", produtos[maxIndice].nome);
  printf("Codigo: %d\n", produtos[maxIndice].codigo);
  printf("Quantidade vendida: %d\n", contagem[maxIndice]);
}

void vendasPorProduto(Produto produtos[], int qtdProdutos, Venda vendas[],
                      int qtdVendas) {
  printf("2. Vendas por produto\n");
  int qtdVendida[MAX_PRODUTOS] = {0};
  int numeroVendas[MAX_PRODUTOS] = {0};

  if (!qtdVendas) {
    printf("Nenhuma venda efetuada ainda.\n");
    return;
  }

  for (int i = 0; i < qtdVendas; i++) {
    int codigoVenda = vendas[i].produtoVendido.codigo;
    float valorTotal = vendas[i].valorTotal;
    for (int j = 0; j < qtdProdutos; j++) {
      if (codigoVenda == produtos[j].codigo) {
        float preco = vendas[i].produtoVendido.precoVenda;
        numeroVendas[j] += 1;
        qtdVendida[j] += (int)((valorTotal / preco) + 0.5f);
        break;
      }
    }
  }

  // imprimir informações
  for (int i = 0; i < qtdProdutos; i++) {
    printf("Produto: %s\n", produtos[i].nome);
    printf("Código do produto: %d\n", produtos[i].codigo);
    printf("Vendas do Produto: %d\n", numeroVendas[i]);
    printf("Quantidade vendida: %d\n", qtdVendida[i]);
    printf("\n");
  }
}

void somaDasVendas(Produto produtos[], int qtdProdutos, Venda vendas[],
                   int qtdVendas) {
  printf("3. Arrecadação Total das Vendas\n");
  float somaVendas = 0;

  if (!qtdVendas) {
    printf("Nenhuma venda efetuada ainda.\n");
    return;
  }

  for (int i = 0; i < qtdVendas; i++) {
    somaVendas += vendas[i].valorTotal;
  }

  printf("Total obtido com as vendas: R$ %.2f\n", somaVendas);
  printf("\nDetalhamento das vendas:\n");
  for (int i = 0; i < qtdVendas; i++) {
    printf("Código da Venda: %d\n", vendas[i].codigoVenda);
    printf("Código do produto: %d\n", vendas[i].produtoVendido.codigo);
    printf("Valor da Venda deste produto: R$ %.2f\n", vendas[i].valorTotal);
    printf("\n");
  }
}

void limparTela() { system("cls"); }

void relatorios(Produto produtos[], int qtdProdutos, Venda vendas[],
                int qtdVendas) {
  int opcao;
  printf("6. Relatórios\n");
  printf("Selecione o tipo de relatório que você deseja analisar: \n");
  printf("0. Voltar ao menu principal\n");
  printf("1. Exibir o produto mais vendido\n");
  printf("2. Vendas por produto\n");
  printf("3. Arrecadação total das vendas\n");
  printf("Sua opção: ");
  scanf("%d", &opcao);

  switch (opcao) {
  case 0:
    return;
    break;
  case 1:
    limparTela();
    maisVendido(produtos, qtdProdutos, vendas, qtdVendas);
    break;
  case 2:
    limparTela();
    vendasPorProduto(produtos, qtdProdutos, vendas, qtdVendas);
    break;
  case 3:
    limparTela();
    somaDasVendas(produtos, qtdProdutos, vendas, qtdVendas);
    break;
  default:
    printf("Erro. Opção inválida.\n");
    break;
  }
}

void exibirMenu() {
  printf("----------------------------------------\n");
  printf("    SISTEMA DE VENDAS - TECH STORE\n");
  printf("----------------------------------------\n");
  printf("1. Cadastrar Produto\n");
  printf("2. Registrar Venda\n");
  printf("3. Listar Produtos Disponíveis\n");
  printf("4. Listar Vendas Realizadas\n");
  printf("5. Listar Produtos em Falta\n");
  printf("6. Relatórios\n");
  printf("0. Sair do programa\n");
  printf("----------------------------------------\n");
  printf("Escolha uma opção: ");
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  Produto produtos[MAX_PRODUTOS];
  Venda vendas[MAX_VENDAS];
  int qtdProdutos = 0;
  int qtdVendas = 0;
  int opcao;

  do {
    limparTela();
    exibirMenu();
    scanf("%d", &opcao);

    limparTela();

    switch (opcao) {
    case 1:
      cadastrarProduto(produtos, &qtdProdutos);
      break;
    case 2:
      registrarVenda(vendas, &qtdVendas, produtos, &qtdProdutos);
      break;
    case 3:
      listarProdutos(produtos, &qtdProdutos);
      break;
    case 4:
      listarVendas(vendas, &qtdVendas);
      break;
    case 5:
      listarProdutosEmFalta(produtos, &qtdProdutos);
      break;
    case 6:
      relatorios(produtos, qtdProdutos, vendas, qtdVendas);
      break;
    /* case 7: */
    /*   maisVendido(produtos, qtdProdutos, vendas, qtdVendas); */
    /*   break; */
    case 0:
      printf("Encerrando o programa. Obrigado por usar o Tech Store!\n");
      break;
    default:
      printf("Opcao invalida! Tente novamente.\n");
    }

    if (opcao != 0) {
      printf("\nPressione Enter para continuar...");
      while (getchar() != '\n')
        ;
      getchar();
    }

  } while (opcao != 0);

  return 0;
}
