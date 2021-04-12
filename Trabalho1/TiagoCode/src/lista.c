#include "lista.h"
#include <stdlib.h>

Lista nova_lista() {
	Lista ret;
	ret.cabeca = NULL;
	return ret;
}

Lista add_lista(Lista lst, void* content) {
	Node* node = (Node*) malloc(sizeof(Node));
	node->content = content;
	node->next = lst.cabeca;
	Lista l;
	l.cabeca = node;
	return l;
}

Lista remove_lista(Lista lst) {
	Node* old = lst.cabeca;

	if (old == NULL)
		return lst;

	lst.cabeca = old->next;
	free(old->content);
	free(old);

	return lst;
}

void free_lista(Lista lst) {
	while (lst.cabeca != NULL) lst = remove_lista(lst);
}


