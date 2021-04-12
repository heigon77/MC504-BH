#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THR 10
#define N 9
#define UNASSIGNED 0

int idThr = 1; // identifca um número pra thread

int is_exist_row(int **grid[N][N], int row, int num){
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_col(int **grid[N][N], int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_box(int **grid[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			} 
		}
	}
	return 0;
}

int is_safe_num(int **grid[N][N], int row, int col, int num) {
	return !is_exist_row(grid, row, num) 
			&& !is_exist_col(grid, col, num) 
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int **grid[N][N], int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int **grid[N][N],int num) {
	
	int row = 0;
	int col = 0;
	
	if (!find_unassigned(grid, &row, &col)){
		return 1;
	}
	
		
		if (is_safe_num(grid, row, col, num)) {
			grid[row][col] = num;
			
			if (solve(grid,num)) {
				return 1;
			}
			
			grid[row][col] = UNASSIGNED;
	}
	
	return 0;
}

void* f_thread(void **v) {
    int** id = (int **) v;
    int **matriz = id[1];
    //int idT = id[0];
    int idT = idThr++; // não consegui usar id[0]
    

    solve(matriz,idT);
    

    // printf("Essa thread cuida da linha: %d\n", idT);
    // printf("Endereço da matriz depois da chamada : %d\n", id[1]);
    // printf("conteúdo da matriz tem que ser igual a banana: %d\n",matriz[2][3]);
    //printf("teste leitura matriz %d", );
    return NULL; 
}

void imprime( int **mat,int l, int c){  //funcao para printar matriz
    for (int i = 0; i < c; i++){
        for (int j = 0; j < l; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

void leitura( int** mat){
    FILE *fp;
    char c;
    int linha=0;
    int coluna=0;
    if((fp=fopen("sudoku.txt", "r")) == NULL){
        printf("Erro na abertura do Arquivo");
    }else{
        while( (c=fgetc(fp)) !=EOF) {
            if(c=='\n'){
                linha++;
                coluna=0;
            }else{
                if(c!=' '){
                    mat[linha][coluna] = ((int)c - 48);
                    coluna++;
                }
            }
        }
    }
    imprime(mat,9,9);
    fclose(fp);
}

int main(int argc, char const *argv[]){   
    int colunas = 9;
    int linhas = 9;  //dimensionamos a matriz

    int **nums = (int *)malloc((2)*sizeof(int *));//Vetor de Ponteiros
    int **matriz = malloc((linhas*sizeof(int *))); //Allocamos a matriz

    for(int i=0;i<linhas;i++){
        matriz[i] = malloc((colunas*sizeof(int)));
    }

    leitura(matriz);

    
    for(int i=0; i<linhas;i++){//preenchendo ela para testes
        for(int j=0; j<colunas;j++){
            matriz[i][j] = 0;
        }
    }    

    nums[0] = 1; //Identificador da thread; não consegui usar
    nums[1] = matriz;

    

    pthread_t thr[linhas];//chamada das threads

    for (int i = 0; i < linhas; i++){ //cria uma thread pra cada coluna
        nums[0] = i; //deveria iniciar cada thread com um identificado, mas como é um ponteiro, ao atualizar muda a thread ja iniciada, aí tinha várias thread com o mesmo identificador
        pthread_create(&thr[i], NULL, f_thread, (void**) nums);
    }


    for (int i = 0; i < linhas; i++){// une as threads
        pthread_join(thr[i], NULL); 
    }


    imprime(matriz,linhas,colunas);

    return 0;
}
