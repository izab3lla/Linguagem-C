#include <stdio.h>

int main (){

int n, num, soma = 0, cont = 1, i;

printf ("Digite um numero para obter a soma dos primos: \n");
scanf ("%d", &num);

for (i = 2; i <= num; i++ ){
    for(n = 2; n<= i; n++){
      if(i %n == 0){
        cont++;
      }
    }
if(cont == 2){
   soma += i;
}
cont = 1;
}
printf ("A soma dos numeros primos eh: %d \n", soma);


return 0;
}
