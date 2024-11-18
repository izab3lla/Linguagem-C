#include <stdio.h>

int main(){

int idade, quant, soma = 0, media = 0;

printf("Digite quantas idades deseja inserir:");
scanf("%d", &quant);

while (quant > 0){
printf("Digite a idade %d:", quant);
scanf ("%d", &idade);

if(idade >= 18){
    soma = soma + idade;
}
if(idade < 18){
    media = media + idade/quant;
}

quant--;
}

printf("A soma das idades maiores de 18 eh: %d \n", soma);
printf("A media da idade de pessoas menores de 18 eh: %d \n", media);

return 0;
}
