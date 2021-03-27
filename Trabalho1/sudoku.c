#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THR 10

void* f_thread(void **v) {
    int** id = (int **) v;
    int **matriz = id[1];


    printf("Endereço da matriz depois da chamada : %d\n", id[1]);
    printf("conteúdo da matriz tem que ser igual a banana: %d\n",matriz[2][3]);
    //printf("teste leitura matriz %d", );
    return NULL; 
}


int main(int argc, char const *argv[]){   
    int colunas = 9;
    int linhas = 9;  //dimensionamos a matriz

    int **nums = (int *)malloc((2)*sizeof(int *));//Vetor de Ponteiros

    int **matriz = malloc((linhas*sizeof(int *))); //Allocamos a matriz
    for(int i=0;i<linhas;i++){
        matriz[i] = malloc((colunas*sizeof(int)));
    }
    for(int i=0; i<linhas;i++){//preenchendo ela para testes
        for(int j=0; j<colunas;j++){
            matriz[i][j] = i*colunas+j;
        }
    }    

    printf("banana : %d\n", matriz[2][3]);

    nums[0] = 1; //Identificador da thread
    nums[1] = matriz;
    printf("maca : %d\n", nums[0]);
    printf("endereço de matriz antes de ir pra thread : %d\n", nums[1]);
    

    pthread_t thr;  //chamada da thread
    pthread_create(&thr, NULL, f_thread, (void**) nums);
    pthread_join(thr, NULL); 
    free(matriz);
    free(nums);

    return 0;
}
