#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX_CAT 3
#define MAX_PROD 5

struct categoria_produto
  {
  char cod;
  char nome[20];
  };

struct produto
  {
  unsigned int id;
  char Nome[20];
  int cod_cat;
  float preco;
  };

typedef struct categoria_produto categoria;
typedef struct produto produto;


int produto_preenchido(produto vetor[], int tamanho)
  {
  for(int i = 0; i < tamanho; i++)
    {
    if(vetor[i].id == 0)
      {
      printf("Espaco vazio encontrado no indice: %d\n", i);
      return 0;
      }
    }
  return 1;
  }

int categoria_preenchida(categoria vetor[], int tamanho)
  {
  for(int i = 0; i < tamanho; i++)
    {
    if(vetor[i].cod == '\0')
      {
      printf("Espaco vazio encontrado no indice: %d\n", i);
      return 0;
      }
    }
  return 1;
  }

bool codigo_categoria_em_uso(struct categoria_produto categorias[], int tamanho, char novo_cod)
  {
  for(int i = 0; i < tamanho; i++)
    {
    if(categorias[i].cod == novo_cod)
      {
      return true;
      }
    }
    return false;
  }

bool id_produto_em_uso(struct produto produtos[], int tamanho, int novo_id)
  {
  for(int i = 0; i < tamanho; i++)
    {
    if(produtos[i].id == novo_id)
      {
      return true;
      }
    }
  return false;
  }

int main()
  {
  unsigned int opcao;
  char update_cat;
  char confirma;
  char novo_cod;
  char novo_nome[20];
  char novo_nome_prod[20];
  int novo_id;
  int novo_cod_cat;
  int update_prod;
  int var_produto = 0;
  int categoria_existe = 0;
  int produto_existe = 0;
  float novo_preco = 0.0;

  categoria categorias[MAX_CAT] = {
    {'A', "Alimentos"},
    {'B', "Roupas"},
    {'C', "Bebidas"}
  };
  produto produtos[MAX_PROD] = {
    {1, "Arroz", 1, 25.90},
    {2, "Trigo", 1, 5.99},
    {3, "Casaco", 2, 70.00},
    {4, "Cerveja Brahma", 3, 3.49},
    {5, "Monster Energy", 3, 8.40}
  };

  do{
    printf("\n[Menu]\n\n");
    printf("1 - Listar produtos \n");
    printf("2 - Inserir nova categoria \n");
    printf("3 - Inserir novo produto \n");
    printf("4 - Atualizar categoria \n");
    printf("5 - Atualizar produto \n");
    printf("6 - Excluir categoria\n");
    printf("7 - Excluir produto\n");
    printf("0 - Sair \n");
    printf("\nEntre com uma opcao: ");
    scanf ("%u", &opcao);


  switch(opcao)
    {
    case 1:
      for(int i = 0; i < MAX_PROD; i++)
        {
        printf("\n[Produto %d]\n", produtos[i].id);
        printf("  Nome: %s\n", produtos[i].Nome);
        printf("  Categoria: %s\n", categorias[produtos[i].cod_cat-1].nome);
        printf("  Preco: %.2f\n", produtos[i].preco);
        }
      break;
    case 2:
      printf("\n[Inserir nova categoria]\n\n");

      if(categoria_preenchida(categorias, MAX_CAT))
        {
        printf("O limite de categorias excedido!\n");
        }
      else
        {
        printf("Insira o codigo da nova categoria: ");
        scanf(" %c", &novo_cod);
        novo_cod = toupper(novo_cod);

        if (codigo_categoria_em_uso(categorias, MAX_CAT, novo_cod))
          {
          printf("\nO codigo da categoria %c ja esta em uso.\n", novo_cod);
          }
        else
          {
          printf("Insira o nome da nova categoria: ");
          scanf("%s", novo_nome);

          //verificar se essa categoria esta vazia
          if(novo_nome[0] == '\0')
            {
            printf("O nome da categoria nao pode estar vazio.\n");
            }
          else
            {
            printf("\nTem certeza que deseja inserir a categoria %c - %s?\n['S' para sim ou 'N' para nao] -> ", novo_cod, novo_nome);
            scanf(" %c", &confirma);

            if(confirma == 's' || confirma == 'S')
              {
              int indice_vazio = -1;
              for(int i = 0; i < MAX_CAT; i++)
                {
                if(categorias[i].cod == '\0')
                  {
                  indice_vazio = i;
                  printf("Espaco vazio encontrado no indice: %d\n", indice_vazio); // Novo print para debug
                  break;
                  }
                }

              if(indice_vazio != -1)
                {
                categorias[indice_vazio].cod = novo_cod;
                strcpy(categorias[indice_vazio].nome, novo_nome);
                printf("\nCategoria inserida com sucesso!\n");
                }
              else
                {
                printf("\nNao ha espaco disponivel para inserir uma nova categoria.\n");
                }
              }
      	    else
              {
              printf("\nA insercao da categoria foi cancelada.\n");
              }
            }
          }
        }

      break;
    case 3:
      printf("\n[Inserir produto]\n\n");
      // validar se ainda tem espaco
      if(produto_preenchido(produtos, MAX_PROD))
        {
        printf("O limite de produtos excedido!\n");
        }
      else
        {
        int indice_vazio_prod;
        for (int i = 0; i < MAX_PROD; i++)
          {
          if(produtos[i].id == 0)
            {
            indice_vazio_prod = i;
            break;
            }
          }

        printf("Insira o novo ID de produto: ");
        scanf("%d", &novo_id);
        if(id_produto_em_uso(produtos, MAX_PROD, novo_id))
          {
          printf("O ID %d ja esta em uso.\n", novo_id);
          }
        else
          {
          if(novo_id <= 0)
            {
            printf("O ID do produto nao pode estar vazio.\n");
            }
          else
            {
            printf("Insira o novo nome de produto: ");
            scanf("%s", novo_nome_prod);

            if(novo_nome_prod == '\0')
              {
              printf("O nome do produto nao pode estar vazio.\n");
              }
            else
              {
              printf("Insira o novo codigo numerico da categoria de produto: ");
              scanf("%d", &novo_cod_cat);

              if(novo_cod_cat <= 0)
                {
                printf("O codigo da categoria nao pode estar vazio.\n");
                }
              else
                {
                printf("Insira o novo preco de produto: ");
                scanf("%f", &novo_preco);
                if(novo_preco == 0.0)
                  {
                  printf("O preco do produto nao pode estar vazio.\n");
                  }
                else
                  {
                  //acha o campo disponivel
                  //atribui as novas variavei, salva e atualiza
                  printf("\nTem certeza que deseja inserir o produto %d?\n['S' para sim ou 'N' para nao] -> ", update_prod);
                  scanf(" %c", &confirma);

                  if(confirma == 's' || confirma == 'S')
                    {
                    produtos[indice_vazio_prod].id = novo_id;
                    strcpy(produtos[indice_vazio_prod].Nome, novo_nome_prod);
                    produtos[indice_vazio_prod].cod_cat = novo_cod_cat;
                    produtos[indice_vazio_prod].preco = novo_preco;
                    printf("\n\nProduto inserido com sucesso!\n");
                    }
                  else
                    {
                    printf("\nA insercao do produto foi cancelada.\n");
                    }
                  }
                }
              }
            }
          }
        }
      break;
    case 4:
      printf("[Atualizar categoria]\n\n");
      printf("Qual categoria deseja atualizar?\nInsira o codigo da categoria: ");
      scanf(" %c", &update_cat);
      update_cat = toupper(update_cat);

      for(int i = 0; i < MAX_CAT; i++)
        {
        if(categorias[i].cod == update_cat)
          {
          categoria_existe++;
          printf("\nCategoria encontrada: %c - %s\n", categorias[i].cod, categorias[i].nome);
          printf("Insira o novo codigo da categoria: ");
          scanf(" %c", &novo_cod);
          novo_cod = toupper(novo_cod);

          if (codigo_categoria_em_uso(categorias, MAX_CAT, novo_cod))
            {
            printf("\nO codigo da categoria %c ja esta em uso.\n", novo_cod);
            }
          else
            {
            if (categorias[i].nome[0] == '\0')
              {
              printf("O nome da categoria nao pode estar vazio.\n");
              }
            else
              {
              //verificar a logica disso
              printf("Insira o novo nome da categoria: ");
              scanf("%s", novo_nome);
              printf("\nTem certeza que deseja atualizar a categoria %c?\n['S' para sim ou 'N' para nao] -> ", update_cat);
              scanf(" %c", &confirma);

              if(confirma == 's' || confirma == 'S')
                {
                categorias[i].cod = novo_cod;
                strcpy(categorias[i].nome, novo_nome);
                printf("\nCategoria atualizada com sucesso!\n");
                }
              else
                {
                printf("\nA atualizacao da categoria foi cancelada.\n");
                }
              }
          }
        }
      }
      if(categoria_existe == 0)
        {
        printf("\nCategoria inexistente\n");
        }
      categoria_existe = 0;
      break;
    case 5:
      printf("[Atualizar produto]\n\n");
      printf("Qual produto deseja atualizar?\nInsira o ID do produto: ");
      scanf("%d", &update_prod);
      for(int i = 0; i < MAX_PROD; i++)
        {
        if(produtos[i].id == update_prod)
          {
          produto_existe++;
          printf("\nProduto encontrado: %d - %s\n", produtos[i].id, produtos[i].Nome);
          printf("Insira o novo ID de produto: ");
          scanf("%d", &novo_id);
          if(id_produto_em_uso(produtos, MAX_PROD, novo_id))
            {
            printf("O ID %d ja esta em uso.\n", novo_id);
            }
          else
            {
            // aqui seguimos com as outras validacoes
            if(novo_id <= 0)
              {
              printf("O ID do produto nao pode estar vazio.\n");
              }
            else
              {
              printf("Insira o novo nome de produto: ");
              scanf("%s", novo_nome_prod);

              if(novo_nome_prod == '\0')
                {
                printf("O nome do produto nao pode estar vazio.\n");
                }
              else
                {
                printf("Insira o novo codigo numerico da categoria de produto: ");
                scanf("%d", &novo_cod_cat);

                if(novo_cod_cat <= 0)
                  {
                  printf("O codigo da categoria nao pode estar vazio.\n");
                  }
                else
                  {
                  printf("Insira o novo preco de produto: ");
                  scanf("%f", &novo_preco);
                  if(novo_preco == 0.0)
                    {
                    printf("O preco do produto nao pode estar vazio.\n");
                    }
                  else
                    {
                    //acha o campo disponivel
                    //atribui as novas variavei, salva e atualiza
                    printf("\nTem certeza que deseja atualizar o produto %d?\n['S' para sim ou 'N' para nao] -> ", update_prod);
                    scanf(" %c", &confirma);

                    if(confirma == 's' || confirma == 'S')
                      {
                      produtos[i].id = novo_id;
                      strcpy(produtos[i].Nome, novo_nome_prod);
                      produtos[i].cod_cat = novo_cod_cat;
                      produtos[i].preco = novo_preco;
                      printf("\nProduto atualizado com sucesso!\n");
                      }
                    else
                      {
                      printf("\nA atualizacao do produto foi cancelada.\n");
                      }
                    }
                  }
                }
              }
            }
          }
        }
      if(produto_existe == 0)
        {
        printf("\nProduto inexistente\n");
        }

      strcpy(novo_nome_prod, "");
      produto_existe = 0;
      break;
    case 6:
      printf("\n[Excluir categoria]\n\n");
      printf("Qual categoria deseja excluir?\nInsira o codigo da categoria: ");
      scanf(" %c", &update_cat);
      update_cat = toupper(update_cat);
      for(int i = 0; i < MAX_CAT; i++)
        {
        //verifica se existe codigo de produto
        if(categorias[i].cod == update_cat)
          {
          categoria_existe++;
          //validacao antes se tem algum produto na categoria ainda
          for(int i = 0; i < MAX_PROD; i++)
            {
            if(produtos[i].cod_cat == ((int)update_cat - 64))
              {
              printf("\nCategoria nao pode ser excluida, pois existem produtos!\n");
              var_produto++;
              break;
              }
            }
            if(var_produto == 0)
              {
              printf("Tem certeza que deseja excluir a categoria %c?\n['S' para sim ou 'N' para nao] -> ", categorias[i].cod);
              scanf(" %c", &confirma);
              if(confirma == 's' || confirma == 'S')
                {
                printf("\nCategoria %s ",categorias[i].nome);
                categorias[i].cod = '\0';
                categorias[i].nome[0] = '\0';
                printf("excluida com sucesso!\n");
                }
              else
                {
                printf("\nCancelada exclusao!\n");
                break;
                }
              }
            }
 	  }
      if(categoria_existe == 0)
        {
        printf("\nCategoria inexistente\n");
        }
      categoria_existe = 0;
      var_produto = 0;
      break;
    case 7:
      printf("\n[Excluir produto]\n\n");
      printf("Qual produto deseja excluir?\nInsira o ID do produto: ");
      scanf(" %d", &update_prod);
      for(int i = 0; i < MAX_PROD; i++)
        {
        if(produtos[i].id == update_prod)
          {
          printf("Tem certeza que deseja excluir o produto %d?\n['S' para sim ou 'N' para nao] -> ", produtos[i].id);
          scanf(" %c", &confirma);
          if(confirma == 's' || confirma == 'S')
            {
            printf("\nProduto %s ", produtos[i].Nome);
            produtos[i].id = 0;
            produtos[i].Nome[0] = '\0';
            produtos[i].cod_cat = 0;
            produtos[i].preco = 0.0;
            printf("excluido com sucesso!\n");
            break;
            }
          else
            {
            printf("\nCancelada exclusao!\n");
            break;
            }
          }
        else
          {
          if(produtos[i].id == MAX_PROD)
      	    {
      	    printf("\nProduto inexistente!\n");
      	    }
          }
        }
      break;
    default:
      printf("\nInsira uma opcao valida\n");
    }
  } while(opcao != 0);
  return (0);
  }
