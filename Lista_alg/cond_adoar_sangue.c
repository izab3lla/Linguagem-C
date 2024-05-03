#include <stdio.h>
#include <stdlib.h>

void main(){

int idade=0;
float peso=0;

printf("Informe sua idade: \n");
scanf("%d", &idade);
printf("Informe seu peso: \n");
scanf(" %f", &peso);

if ((idade >= 18) && (peso >=50)){
    printf("permitido doar! \n");
}
else{
    printf ("Nao eh permitido doar! \n");
}

system ("pause");
return 0;
}
