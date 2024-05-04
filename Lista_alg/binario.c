#include <stdio.h>

int main(){

int n, bi, div = 1;


printf("Insira o numero que deseja transformar em binario:");
scanf("%d", &n);

while(div <= n /2){
  div *= 2;
}

while(div > 0){
    bi = n/div;
    printf ("%d", bi);
    n %= div;
    div /=2;

}
return 0;
}
