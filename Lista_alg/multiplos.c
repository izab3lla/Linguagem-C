#include <stdio.h>
#define tamanho 8

int main(){

int num[tamanho];
int mult_2 = 0, mult_3 = 0, mult = 0;

for(int i = 0 ; i < 8; i++)
{
   printf ("digite um numero: \n");
   scanf ("%d", &num[i]);

if(num[i] %2 == 0){
mult_2++;
}

if(num[i] %3 == 0){
printf (" %d - multiplo de 3 \n", num[i]);
mult_3++;
}

if(num[i] %2 == 0 && num[i] %3 == 0){
printf (" %d - multiplo de 2 e 3\n", num[i]);
mult++;
}
printf (" %d - multiplo de 2 \n", mult_2[i]);
printf (" %d - multiplo de 3 \n", mult_3[i]);
printf (" %d - multiplo de 2 e 3 \n", mult[i]);
}



return 0;
}
