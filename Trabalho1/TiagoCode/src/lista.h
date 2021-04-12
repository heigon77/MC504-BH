#ifndef LISTA_H
#define LISTA_H

typedef struct Node {
	void* content;
	struct Node* next;
} Node;

typedef struct Lista {
	Node* cabeca;
} Lista;

Lista nova_lista();
Lista add_lista(Lista lst, void* content);
Lista remove_lista(Lista lst);
void free_lista(Lista lst);

#endif // LISTA_H
