# 📦 Sistema de Gerenciamento de Estoque em C

Este projeto é um sistema simples de **controle de estoque** com funcionalidades de **cadastro de usuários**, **login seguro** e **operações CRUD** (Criar, Ler, Atualizar, Deletar) para produtos, desenvolvido em linguagem **C**.

---

## ✨ Funcionalidades

- 👤 Cadastro e login de usuários
- ➕ Adição de novos produtos ao estoque
- 📄 Listagem de todos os produtos registrados
- 🔍 Busca por nome e setor do produto
- ✏️ Atualização de dados dos produtos
- ❌ Exclusão de um ou mais produtos por código
- 💾 Armazenamento local em arquivos `.txt` (`usuarios.txt` e `estoque.txt`)

---

## 🛠 Estrutura do Projeto

- `usuarios.txt`: Armazena os usuários cadastrados no formato `nome|senha`.
- `estoque.txt`: Armazena os produtos no formato `nome|codigo|ano|setor|status`.

---

## 📌 Como Utilizar

1. **Clone o repositório:**

git clone https://github.com/seu-usuario/seu-repositorio.git
cd seu-repositorio

2. **Compile o código:**

gcc main.c -o estoque

3. **Execute o programa:**

./estoque

---

## 🖥️ Navegação no Programa
Ao iniciar:
Você terá as opções:

1 - Cadastrar novo usuário

2 - Fazer login

Após o login com sucesso, o menu principal será exibido:

1 - Adicionar produto
2 - Listar todos os produtos
3 - Buscar um produto
4 - Atualizar um produto
5 - Excluir um produto
6 - Encerrar o programa

---

## 📂 Exemplo de Registro no Arquivo
nginx
Copiar
Editar
Teclado USB|TK001|2023|TI|Funcionando

---

## ✅ Validações
Impede o cadastro de produtos com código duplicado.

Verifica se o status informado é válido: Funcionando, Obsoleto, ou Em manutencao.

Confirmações antes da exclusão de produtos.

---

## 📚 Tecnologias Utilizadas
Linguagem C

Manipulação de arquivos com fopen, fprintf, fscanf

Estruturas (struct) para organização de dados

---

## 🔐 Segurança
O sistema faz validação de usuário e senha antes de permitir acesso às funcionalidades de gerenciamento de estoque. As credenciais são armazenadas em texto simples (para fins didáticos). Em sistemas reais, recomenda-se criptografar as senhas.

---

## 🤝 Contribuição
Sinta-se livre para abrir issues, propor melhorias ou enviar pull requests!

---

## 📄 Licença
Este projeto está sob a licença MIT. Consulte o arquivo LICENSE para mais informações.

---

## 👨‍💻 Autor
Desenvolvido por JricLP
