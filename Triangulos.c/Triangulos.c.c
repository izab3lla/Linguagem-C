#include <stdio.h>

int main(){

  int v1, v2, v3;

  printf("Digite o primeiro lado: \n");
  scanf("%d", &v1);
  printf("Digite o segundo lado: \n");
  scanf("%d", &v2);
  printf("Digite o terceiro lado: \n");
  scanf("%d", &v3);

 if(((( v1 > ( v2 - v3)) && (v1 < v2 + v3)) && (( v2 > ( v1 - v3)) && (v2 < v1 + v3))) && ((( v3 >  ( v1 - v2)) && (v2 < v1 + v2))))
   {
   if((v1 == v2) && (v2 == v3))
     {
     printf("eh um triangulo equilatero!");
     }

   if(((((v1 == v2) && (v1 != v3))) || ((v2 == v3) && (v2 != v1))) || ((v1 == v3) && (v2 != v3)))
     {
     printf("eh um triangulo isosceles!");
     }

   if(((v1 != v2) && (v2 != v3)) && ((v1 != v3)))
     {
     printf("eh um triangulo escaleno!");
     }
   }

 else
   {
   printf("tente novamente, nao eh um triangulo! \n");
   }

  return (0);
  }


