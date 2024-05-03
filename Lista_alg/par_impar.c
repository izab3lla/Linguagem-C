#include <stdio.h>
#define tamanho 6

int main(){

int num [tamanho];
int pares = 0, impar = 0, num_par = 0, num_impar = 0;

for(int i = 0 ; i < 6; i++)
      {
      printf("Entre com um numero:");
      scanf(" %d", &num[i]);

    if (num[i] %2 == 0){
    printf (" %d - par \n", num[i]);
    pares++;
}
    if (num[i] %2 == 1){
    printf (" %d - impar \n", num[i]);
    impar++;
}
}

printf ("A) Os numeros pares sao: %d \n", pares);
printf ("B) Os numeros impares sao: %d \n", impar);

return 0;
}
