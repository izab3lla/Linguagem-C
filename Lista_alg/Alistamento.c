#include <stdio.h>
#include <stdlib.h>

void main(){

int idade= 0;
char sexo;

printf("Informe sua idade: \n");
scanf("%d", &idade);
printf("Informe seu sexo (M/F): \n");
scanf(" %c", &sexo);


if((idade>= 18) && (sexo == 'M'))
{
printf("Alistamento autorizado! \n");
}
else{
printf("Alistamento negado! \n");
}

system("pause");
}
