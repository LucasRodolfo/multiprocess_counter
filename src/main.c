/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */
//Lucas Rodolfo de Castro Moura - 156405
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int ehPrimo(long long int numero){            /*Funcao que analisa se um numero eh primo ou nao*/
      int flag = 0;

      for(long long int i = 2; i <= numero/2; ++i){
          if(numero%i == 0){
              flag = 1;
              break;
          }
      }

      if (numero == 1 || numero == 0){
        return 0;
      }
      else{
          if (flag == 0){
            return 1;
          }else{
            return 0;
          }
      }
}

int main() {

  char temp;
  long long int vetor[100];
  int i=0, tamanho=0, j=0, posicao;

  pid_t filhos[4];

  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  int *NPrimos;
  NPrimos = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  if (NPrimos==(int*)-1) printf("Erro de alocacao!\n");
  (*NPrimos) = 0;

  do {                                    /*Esse loop lê string de entrada e armazena em um vetor de inteiros*/
    scanf("%lld%c", &vetor[i], &temp);
    i++;
  } while(temp != '\n');
  tamanho =i;                              /*Guarda o tamanho do vetor de inteiros criado*/

  for (i = 0; i < tamanho; i+=4) {         /*Esse loop passa pelos elementos do vetor de inteiros e cria um proceso filho para analisar cada numero desse vetor*/
    for (j=0; j<4; j++) {
          posicao = i+j;                    /*Posicao do vetor de inteiros que vai ser analisada agora*/
          if (posicao >= tamanho) {         /*Se todos os elementos ja foram analisados, para*/
            break;
          }
          filhos[j] = fork();
          if (filhos[j] == 0) {
              (*NPrimos) += ehPrimo(vetor[posicao]);
              exit(0);
          }
          for (int j=0; j<4; j++) {
            waitpid(filhos[j], NULL, 0);
          }
    }
  }
  printf("%d\n", *NPrimos);

  return 0;
}
