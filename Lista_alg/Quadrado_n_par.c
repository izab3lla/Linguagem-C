#include <stdio.h>

int main (){

int num, quad=0;

printf ("Digite um numero: \n");
scanf ("%d", &num);

if(num %2 == 0){
    quad = num * num;
    printf ("O quadrado desse numero eh %d", quad);
}
else{
    printf ("Nao eh um numero par");
}

return 0;
}
