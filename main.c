#include <stdio.h>
#include <string.h>
#include <strings.h>


typedef struct {
    char nome_item[50];
    char codigo_item[6];
    char ano_item[5];
    char setor_item[50];
    char status_item[15];
} Estoque; //Estrutura de dados do codigo de registro


typedef struct {
    char nome_usuario[50];
    char senha[50];
} Usuario;
//Fun��o de cadastro do usu�rio
void cadastrarUsuario() {
    FILE *arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuarios para gravacao.\n");
        return;
    }

    Usuario usuario;
    printf("Digite o nome de usuario: ");
    scanf(" %[^\n]", usuario.nome_usuario);
    printf("Digite a senha: ");
    scanf(" %[^\n]", usuario.senha);

    //Grava os dados do usu�rio
    fprintf(arquivo, "%s|%s\n", usuario.nome_usuario, usuario.senha);
    printf("Usuario cadastrado com sucesso!\n");

    fclose(arquivo);
}
//Fun��o para o login do usu�rio
int fazerLogin() {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuarios para leitura!\n");
        return 0;
    }

    Usuario usuario;
    char nome_usuario[50], senha[50];
    int login_sucesso = 0;

    printf("Digite seu nome de usuario: ");
    scanf(" %[^\n]", nome_usuario);
    printf("Digite sua senha: ");
    scanf(" %[^\n]", senha);

    //Verifica se o nome de usu�rio e senha est�o corretos
    while (fscanf(arquivo, "%49[^|]|%49[^\n]\n", usuario.nome_usuario, usuario.senha) != EOF) {
        if (strcmp(usuario.nome_usuario, nome_usuario) == 0 && strcmp(usuario.senha, senha) == 0) {
            login_sucesso = 1;
            break;
        }
    }



    fclose(arquivo);
    if (login_sucesso) {
        printf("Login realizado com sucesso!\n");
        return 1;
    } else {
        printf("Nome de usuario ou senha incorretos.\n");
        return 0;
    }
}


int codigoExistente(const char *codigo) { //Verificacao da existencia do arquivo
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        return 0; //Se o arquivo nao existe, o codigo e considerado inexistente
    }

    Estoque estoque;
    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigo) == 0) {
            fclose(arquivo);
            return 1; // C?digo encontrado - Arquivo encontrado
        }
    }

    fclose(arquivo);
    return 0; //Codigo nao encontrado - Arquivo nao encontrado
}
//Fun��o para a grava��o de dados
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

        //Verifica se o c�digo j� existe
        if (codigoExistente(estoque.codigo_item)) {
            printf("Erro: Codigo ja existente. Tente novamente com outro codigo.\n");
            continue;
        }

        printf("Digite o ano do produto: ");
        scanf(" %[^\n]", estoque.ano_item);

        printf("Digite o setor do produto: ");
        scanf(" %[^\n]", estoque.setor_item);

        //Loop para validar o status
        while (1) {
            printf("Digite o status do produto (Funcionando/Obsoleto/Em manutencao): ");
            scanf(" %[^\n]", estoque.status_item);

            // Verificar se o status � v�lido
            if (strcasecmp(estoque.status_item, "Funcionando") == 0 ||
                strcasecmp(estoque.status_item, "Obsoleto") == 0 ||
                strcasecmp(estoque.status_item, "Em manutencao") == 0) {
                break; // Status v�lido, sai do loop
            } else {
                printf("Status invalido! Por favor, digite novamente.\n");
            }
        }

        fprintf(arquivo, "%s|%s|%s|%s|%s\n", estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item);
        printf("Produto registrado!\n");

        printf("Deseja adicionar outro produto? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    fclose(arquivo);
}

//Funcao para o listamento dos dados gravados no arquivo "estoque.txt"
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
//Funcao para a busca de produtos no arquivo "estoque.txt"
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
//Funcao para a atualizacao de dados no arquivo "estoque.txt"
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
    char atualizarCodigo;
    int encontrado = 0;

    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigoProduto) == 0) {
            encontrado = 1;
            printf("Deseja manter o codigo atual deste produto na atualizacao? (s/n): ");
            scanf(" %c", &atualizarCodigo);
            if (atualizarCodigo == 'n' || atualizarCodigo == 'N'){
                printf("Digite o novo codigo: ");
                scanf(" %[^\n]", estoque.codigo_item);
                while (codigoExistente(estoque.codigo_item)) {
                    printf("Erro: Codigo ja existente. Tente novamente com outro codigo.\nDigite o novo codigo: ");
                    scanf(" %[^\n]", estoque.codigo_item);
                    continue;}
            }

            printf("Digite o novo nome: ");
            scanf(" %[^\n]", estoque.nome_item);

            printf("Digite o novo ano: ");
            scanf(" %[^\n]", estoque.ano_item);

            printf("Digite o novo setor: ");
            scanf(" %[^\n]", estoque.setor_item);

            while (1) {
                    printf("Digite o novo status (Funcionando/Obsoleto/Em manutencao): ");
                    scanf(" %[^\n]", estoque.status_item);

                    if (strcasecmp(estoque.status_item, "Funcionando") == 0 ||
                        strcasecmp(estoque.status_item, "Obsoleto") == 0 ||
                        strcasecmp(estoque.status_item, "Em manutencao") == 0) {
                        break; // Status v�lido, sai do loop
                    } else {
                        printf("Status invalido! Por favor, digite novamente.\n");
                    }
                }

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
//Funcao para a exclusao de dados no arquivo "estoque.txt"
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
    char confirmacao;

    while (fscanf(arquivo, "%49[^|]|%5[^|]|%4[^|]|%49[^|]|%14[^\n]\n",
                  estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item) != EOF) {
        if (strcmp(estoque.codigo_item, codigoProduto) == 0) {
            encontrado = 1;

            //Mostrar os dados do produto
            printf("\nProduto encontrado:\n");
            printf("Nome do item: %s\n", estoque.nome_item);
            printf("Codigo do item: %s\n", estoque.codigo_item);
            printf("Ano do item: %s\n", estoque.ano_item);
            printf("Setor: %s\n", estoque.setor_item);
            printf("Status: %s\n", estoque.status_item);

            //Perguntar se deseja excluir
            printf("\nTem certeza que deseja excluir este produto? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S') {
                printf("Produto excluido com sucesso!\n");
                continue; //N�o escreve no arquivo tempor�rio, efetivamente excluindo
            } else {
                printf("Operacao de exclusao cancelada.\n");
            }
        }

        //Escrever no arquivo tempor�rio se n�o for o produto a excluir
        fprintf(tempArquivo, "%s|%s|%s|%s|%s\n",
                estoque.nome_item, estoque.codigo_item, estoque.ano_item, estoque.setor_item, estoque.status_item);
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
    int login_realizado = 0;

    //Loop para permitir cadastro ou login
    do {

            printf("\nEscolha uma opcao:\n");
            printf("1 - Cadastrar novo usuario\n");
            printf("2 - Fazer login\n");
            printf("Opcao: ");
            scanf(" %c", &opcao);

            if (opcao == '1') {
                cadastrarUsuario(); //Cadastrar novo usu�rio
            } else if (opcao == '2') {
                login_realizado = fazerLogin(); //Tentar fazer login
            } else {
                getchar();
                printf("Opcao invalida! Tente novamente.\n");
            }


    } while (!login_realizado); //Continua at� o login ser realizado com sucesso

    //Menu do sistema de estoque ap�s login
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
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != '6'); //Continua o menu de estoque at� o usu�rio encerrar

    return 0;
}
