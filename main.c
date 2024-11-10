#include <stdio.h>
#include <string.h>

typedef struct {
    char nome_item[50];
    char codigo_item[6];
    char ano_item[5];
    char setor_item[50];
    char status_item[15];
} Estoque; //Estrutura de dados do código de registro

int codigoExistente(const char *codigo) { //Verificação da existência do arquivo
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        return 0; // Se o arquivo não existe, o código é considerado inexistente
    }

    Estoque estoque;
    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigo) == 0) {
            fclose(arquivo);
            return 1; // Código encontrado - Arquivo encontrado
        }
    }

    fclose(arquivo);
    return 0; // Código não encontrado - Arquivo não encontrado
}
//Função para a gravação de dados
void gravarDados() {
    FILE *arquivo = fopen("estoque.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravacao.\n");
        return;
    }

    Estoque estoque;
    char opcao;

    do {
        printf("Digite o nome do produto: ");
        scanf(" %[^\n]", estoque.nome_item);

        printf("Digite o codigo do produto: ");
        scanf(" %[^\n]", estoque.codigo_item);

        // Verifica se o código já existe
        if (codigoExistente(estoque.codigo_item)) {
            printf("Erro: Codigo ja existente. Tente novamente com outro codigo.\n");
            continue;
        }

        printf("Digite o ano do produto: ");
        scanf(" %[^\n]", estoque.ano_item);

        printf("Digite o setor do produto: ");
        scanf(" %[^\n]", estoque.setor_item);

        printf("Digite o status do produto (Funcionando/Obsoleto/Em manutencao): ");
        scanf(" %[^\n]", estoque.status_item);

        fprintf(arquivo, "%s|%s|%s|%s|%s\n", estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item);
        printf("Produto registrado!\n");

        printf("Deseja adicionar outro produto? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    fclose(arquivo);
}
//Função para o listamento dos dados gravados no arquivo "estoque.txt"
void listarDados() {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    Estoque estoque;
    printf("\nLista de Estoque:\n");
    printf("|   Nome do Produto    | Codigo |  Ano |       Setor        |     Status   \n");
    printf("-----------------------------------------------------------------------------\n");

    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        printf("|%-21s | %-6s | %-4s | %-18s | %-10s\n",
               estoque.nome_item,
               estoque.codigo_item,
               estoque.ano_item,
               estoque.setor_item,
               estoque.status_item);
    }

    fclose(arquivo);
}
//Função para a busca de produtos no arquivo "estoque.txt"
void buscarProduto(const char *codigoProduto) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    Estoque estoque;
    int encontrado = 0;

    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigoProduto) == 0) {
            printf("\nProduto encontrado:\n");
            printf("Nome do item: %s\n", estoque.nome_item);
            printf("Codigo do item: %s\n", estoque.codigo_item);
            printf("Ano do item: %s\n", estoque.ano_item);
            printf("Setor: %s\n", estoque.setor_item);
            printf("Status: %s\n", estoque.status_item);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }

    fclose(arquivo);
}
//Função para a atualização de dados no arquivo "estoque.txt"
void atualizarProduto(const char *codigoProduto) {
    FILE *arquivo = fopen("estoque.txt", "r");
    FILE *tempArquivo = fopen("temp.txt", "w");
    if (arquivo == NULL || tempArquivo == NULL) {
        printf("Erro ao abrir o arquivo para atualizacao!\n");
        if (arquivo) fclose(arquivo);
        if (tempArquivo) fclose(tempArquivo);
        return;
    }

    Estoque estoque;
    int encontrado = 0;

    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigoProduto) == 0) {
            encontrado = 1;
            printf("Digite o novo nome: ");
            scanf(" %[^\n]", estoque.nome_item);

            printf("Digite o novo codigo: ");
            scanf(" %[^\n]", estoque.codigo_item);

            printf("Digite o novo ano: ");
            scanf(" %[^\n]", estoque.ano_item);

            printf("Digite o novo setor: ");
            scanf(" %[^\n]", estoque.setor_item);

            printf("Digite o novo status (Funcionando/Obsoleto/Em manutencao): ");
            scanf(" %[^\n]", estoque.status_item);

            printf("Produto atualizado com sucesso!\n");
        }

        fprintf(tempArquivo, "%s|%s|%s|%s|%s\n", estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item);
    }

    fclose(arquivo);
    fclose(tempArquivo);

    remove("estoque.txt");
    rename("temp.txt", "estoque.txt");

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}
//Função para a exclusão de dados no arquivo "estoque.txt"
void excluirProduto(const char *codigoProduto) {
    FILE *arquivo = fopen("estoque.txt", "r");
    FILE *tempArquivo = fopen("temp.txt", "w");
    if (arquivo == NULL || tempArquivo == NULL) {
        printf("Erro ao abrir o arquivo para exclusao!\n");
        if (arquivo) fclose(arquivo);
        if (tempArquivo) fclose(tempArquivo);
        return;
    }

    Estoque estoque;
    int encontrado = 0;

    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigoProduto) == 0) {
            encontrado = 1;
            printf("Produto excluido com sucesso!\n");
        } else {
            fprintf(tempArquivo, "%s|%s|%s|%s|%s\n",
                    estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item);
        }
    }

    fclose(arquivo);
    fclose(tempArquivo);

    remove("estoque.txt");
    rename("temp.txt", "estoque.txt");

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

int main() {
    char opcao;
    char codigoProduto[6];

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Listar todos os produtos\n");
        printf("3 - Buscar um produto\n");
        printf("4 - Atualizar um produto\n");
        printf("5 - Excluir um produto\n");
        printf("6 - Encerrar o programa\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                gravarDados();
                break;
            case '2':
                listarDados();
                break;
            case '3':
                printf("Digite o codigo do produto que deseja buscar: ");
                scanf(" %[^\n]", codigoProduto);
                buscarProduto(codigoProduto);
                break;
            case '4':
                printf("Digite o codigo do produto: ");
                scanf(" %[^\n]", codigoProduto);
                atualizarProduto(codigoProduto);
                break;
            case '5':
                printf("Digite o codigo do produto a ser excluido: ");
                scanf(" %[^\n]", codigoProduto);
                excluirProduto(codigoProduto);
                break;
            case '6':
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção invalida! Tente novamente.\n");
        }

    } while (opcao != '6'); //Encerramento do programa

    return 0;
}
