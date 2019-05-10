/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int ehPrimo(int numero){
      int flag = 0;

      for(int i = 2; i <= numero/2; ++i){
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
  int vetor[200];
  int i=0, tamanho=0, j=0;

  pid_t filhos[4];

  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  int *NPrimos; /* Numero de elementos que ja foram processados */
  NPrimos = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  if (NPrimos==(int*)-1) printf("Erro de alocacao!\n");
  (*NPrimos) = 0;

  do {
    scanf("%d%c", &vetor[i], &temp);
    i++;
  } while(temp != '\n');
  tamanho =i;

  for (int i = 0; i < tamanho; i++) {
    if (ehPrimo(vetor[i])) {
      printf("%d é primo\n", vetor[i] );
    }
  }
  for (i = 0; i < tamanho; i+=4) {
    /* Create the processes */
    for (j=0; j<4; j++) {
        filhos[j] = fork();
        if (filhos[j] == 0) {
          (*NPrimos) += ehPrimo(vetor[i+j]);
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
