#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "lista.h"

#define N_FILHAS 3
#define MAX_PEDIDOS 5

volatile Lista lista;
volatile short unsigned int interesse[N_FILHAS];
volatile short unsigned int rc;
volatile short unsigned int finish;

void* mae(void *v) {
  int i;
  finish = 0;

	while (1) {
		for (i = 0; i < N_FILHAS; i++) {
			if (interesse[i]) {
				rc = i; /* Passa a vez para a thread */
				while (rc == i);  /* Espera a thread sair da RC */
			}
		}

		i = 0;
		for (Node* node = lista.cabeca; node != NULL; node = node->next)
			i++;

		if (i >= MAX_PEDIDOS) {
			printf("-- Pedidos --\n");
			for (Node* node = lista.cabeca; node != NULL; node = node->next) {
				printf("%s\n", (char*)node->content);
			}
			return NULL;
		}
	}
}

char* get_nome_filha(unsigned short int filha_id) {
	switch (filha_id) {
	case 0: return "Bruna";
	case 1: return "Letícia";
	case 2: return "Natasha";
	}

	return NULL;
}

const char* get_pedido_filha(unsigned short int filha_id, unsigned short int n_pedido) {
	const char* filha_pedido[N_FILHAS][MAX_PEDIDOS] = {
		{ "skate", "violão", "videogame", "curso de computação quântica de verão", "livro genealogia da moral" },
		{ "viagem para o japão", "pular de paraquedas", "conhecer o congresso nacional", "impressora", "quadrinho de calvin e haroldo" },
		{ "chiclete", "sorvete", "chocotone", "miojo", "pão com mortadela" }
	};

	return filha_pedido[filha_id][n_pedido];
}

void* filha_generica(void* v) {
	unsigned short int thr_id = *(unsigned short int*)v;
	char* nome_filha = get_nome_filha(thr_id);
	int j;

	for (unsigned short int i = 0;;i++){
		interesse[thr_id] = 1;
		while (rc != thr_id){
			j = 0;
			for (Node* node = lista.cabeca; node != NULL; node = node->next)
				j++;

			if (j >= MAX_PEDIDOS) {
				return NULL;
			}
			
		} /* Espera ser a vez desta thread */

		if (rand() % 2) {
			const char* pedido = get_pedido_filha(thr_id, i);
			char* pedido_completo = (char*) malloc(sizeof(char)*200);

			strcat(pedido_completo, nome_filha);
			strcat(pedido_completo, ": ");
			strcat(pedido_completo, pedido);
			lista = add_lista(lista, pedido_completo);

			printf("%s pediu %s.\n", nome_filha, pedido);
		}
		interesse[thr_id] = 0;


    rc = -1;
    sleep(1);
  }
}

int main(int argc, char** args){
	lista = nova_lista();
	time_t t;
	srand((unsigned) time(&t));

	pthread_t thr[N_FILHAS], thr_gerente;
	unsigned short int id[N_FILHAS], i;

	pthread_create(&thr_gerente, NULL, mae, NULL);

	for (i = 0; i < N_FILHAS; i++) {
		id[i] = i;
		pthread_create(&thr[i], NULL, filha_generica, &id[i]);
	}

	for (i = 0; i < N_FILHAS; i++){
		pthread_join(thr[i],NULL);
	}
    pthread_join(thr_gerente, NULL);

	free_lista(lista);

	return 0;
}
