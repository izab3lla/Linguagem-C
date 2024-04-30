#include <stdio.h>
#define TOTAL 6

struct habitante
  {
  char nome[60];
  char sobrenome[60];
  char sexo;
  int salario;
  int dia;
  int mes;
  int ano;
  int filhos;
  };

typedef struct habitante habitante;

int main ()
  {
  int i;
  int media_salarial = 0;
  int media_filhos = 0;
  int quantidd_masc = 0;
  int media_filhos_masc = 0;

  struct habitante habitante[6];

  printf("[Preencha com as pessoas entrevistas]\n\n");

  //Entrada
  for(i = 0; i < TOTAL; i++)
    {
    printf("[Pessoa %d]\n\n", i + 1);
    printf ("Digite o primeiro nome: ");
    scanf ("%s", habitante[i].nome);
    printf ("Digite o sobrenome: ");
    scanf ("%s", habitante[i].sobrenome);
    getchar();
    printf ("Digite o sexo: ");
    scanf (" %c", &habitante[i].sexo);
    printf ("Informe o salario: ");
    scanf ("%d", &habitante[i].salario);
    printf ("Informe o ano de nascimento (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &habitante[i].dia, &habitante[i].mes, &habitante[i].ano);
    printf ("Digite a quantidade de filhos: ");
    scanf("%d", &habitante[i].filhos);
    printf("\n");
    }

  printf ("\n[Lista de dados de todas as pessoas entrevistadas]\n\n");

  for(i = 0; i < TOTAL; i++)
    {
    printf("[Pessoa %d]\n\n", i + 1);
    printf ("Nome: %s \n", habitante[i].nome);
    printf ("Sobrenome: %s \n", habitante[i].sobrenome);
    printf ("Sexo: %c \n", habitante[i].sexo);
    printf ("Salario: %d \n", habitante[i].salario);
    printf ("Data de nascimento: %d/%d/%d\n", habitante[i].dia, habitante[i].mes, habitante[i].ano);
    printf ("Quantidade de filhos: %d \n", habitante[i].filhos);
    printf("\n");
    }

  printf ("[Dados da primeira pessoa]\n\n");
  printf ("Nome completo: %s %s \n", habitante[0].nome, habitante[0].sobrenome);
  printf ("Sexo: %c \n", habitante[0].sexo);
  printf ("Salario: %d \n", habitante[0].salario);
  printf ("Data de nascimento: %d/%d/%d \n",  habitante[0].dia, habitante[0].mes, habitante[0].ano);
  printf ("Quantidade de filhos: %d \n", habitante[0].filhos);


  printf ("[Dados da ultima pessoa]\n\n");
  printf ("Nome completo: %s %s \n", habitante[TOTAL-1].nome, habitante[TOTAL-1].sobrenome);
  printf ("Sexo: %c \n", habitante[TOTAL-1].sexo);
  printf ("Salario: %d \n", habitante[TOTAL-1].salario);
  printf ("Data de nascimento: %d/%d/%d \n",  habitante[TOTAL-1].dia, habitante[TOTAL-1].mes, habitante[TOTAL-1].ano);
  printf ("Quantidade de filhos: %d \n", habitante[TOTAL-1].filhos);

  printf ("\n[Dados da quinta pessoa]\n\n");
  printf("[Pessoa %d]\n\n", i + 1);
  printf ("Sobrenome: %s \n", habitante[4].sobrenome);
  printf ("Ano de nascimento: %d/%d/%d \n",  habitante[4].dia, habitante[4].mes, habitante[4].ano);
  printf("\n");

  printf("\n[Dados das pessoas de sexo feminino]\n\n");


  for(i = 0; i < TOTAL; i++)
    {
    if(habitante[i].sexo == 'f' || habitante[i].sexo == 'F')
      {
      printf("[Pessoa %d]\n\n", i + 1);
      printf ("Nome completo: %s %s \n", habitante[0].nome, habitante[0].sobrenome);
      printf ("sexo: %c \n", habitante[0].sexo);
      printf ("Salario: %d \n", habitante[0].salario);
      printf ("Data de nascimento: %d/%d/%d \n",  habitante[0].dia, habitante[0].mes, habitante[0].ano);
      printf ("quantidade de filhos: %d \n", habitante[0].filhos);
      }
    }

  printf("\n[Dados das pessoas com salario maiores do que 9 mil]\n\n");

  for(i = 0; i < TOTAL; i++)
    {
    if(habitante[i].salario > 9000)
      {
      printf("Nome completo: %s %s \n", habitante[i].nome, habitante[i].sobrenome);
      }
    }

  printf("\n");
  printf("[Media salarial populacional]\n\n");
  for(i = 0; i < TOTAL; i++)
    {
    media_salarial = media_salarial + habitante[i].salario;
    }

  printf("A media salarial eh igual a %d\n\n", media_salarial/TOTAL);

  printf("[Media de numero de filhos]\n\n");
  for(i = 0; i < TOTAL; i++)
    {
    media_filhos = media_filhos + habitante[i].filhos;
    }

  printf("A media de filhos eh igual a %d\n\n", media_filhos/TOTAL);

  printf("[Quantidade de pessoas de sexo masculino]\n\n");

  for(i = 0; i < TOTAL; i++)
    {
    if(habitante[i].sexo == 'M' || habitante[i].sexo == 'm')
      {
      quantidd_masc++;
      }
    }

  printf("Quantidade de pessoas de sexo masculino: %d\n\n", quantidd_masc);


  printf("[Quantidade de filhos de pessoas de sexo masculino]\n\n");

  for(i = 0; i < TOTAL; i++)
    {
    if(habitante[i].sexo == 'M' || habitante[i].sexo == 'm')
      {
      media_filhos_masc = media_filhos_masc + habitante[i].filhos;
      }
    }

  printf("Quantidade media de filhos de pessoas de sexo masculino: %d\n\n", media_filhos_masc/quantidd_masc);

  return(0);
  }
