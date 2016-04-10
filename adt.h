/* Definição dos tipos abstratos de dados Árvore Binária e Fila de Priorida-
 * de */


#include "global.h" /* constantes globais */
#include <stdlib.h> /* malloc, memcpy */


/* estrutura de uma fila */
typedef struct queue_t__ {
    node_t *first;
    int size;
} queue_t;

/* estrutura de um nó de uma árvore fila binária */
typedef struct node_t__ {
    char character;
    int quantity; /* quantidade de vezes que o character aparece no arquivo */
    struct node_t__ *next_node;
    struct binary_tree_t__ *left; /* filho à esquerda do nó */
	struct binary_tree_t__ *right; /* filho à esquerda do nó */
} node_t;


/* cria uma fila de prioridade vazia e a retorna */
queue_t *create_queue();

/* enfileira um caracter à fila recebida e retorna a própia fila */
queue_t *enqueue(queue_t *, int, char);

/* desenfileira o elemento de maior prioridade de uma fila e o retorna */
node_t *dequeue(queue_t *);

/* retorna TRUE caso a fila recebida esteja vazia e FALSE caso contrário */
bool is_empty_queue(queue_t *);

/* retorna a raíz de uma árvore de huffman gerada a partir da fila recebida */
node_t *huffmanrize_queue(queue_t *);

/* cria um novo elemento em que a quantidade é a soma dos seus dois elementos
 * filhos */
node_t *merge_to_huff(node_t *, node_t *);

/* cria uma fila de prioridade vazia e a retorna */
queue_t *create_queue() {
    queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
    new_queue->first = NULL;
    new_queue->size = ZERO;
    return (new_queue);
}

/* enfileira um caracter à fila recebida e retorna a própia fila */
queue_t *enqueue(queue_t *queue, int quantity, char character) {
    
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    node_t *current_node = queue->first;
    
    new_node->character = character;
	new_node->quantity = quantity;
	new_node->left = NULL;
	new_node->right = NULL;
    
    /* se a fila está vazia ou a quantidade é maior que a primeira posição */
    if (is_empty_queue(queue) || quantity < queue->first->quantity) {
    	new_node->next_node = queue->first;
        queue->first = new_node;
    }
    else {
        /* encontrar o lugar certo para encaixar o elemento */
        while ((current_node->next_node != NULL)
        		&& (current_node->quantity < quantity)){
            
            current_node = current_node->next_node;
        }
        /* encaixar o elemento no meio da fila (ou inserir no final) */
        new_node->next_node = current_node->next_node;
        current_node->next_node = new_node;
    }

    queue->size++;

    return (queue);
}


/* enfileira um elemento à fila recebida e retorna a própia fila */
queue_t *enqueue_node(queue_t *queue, node_t *node) {
	node_t *current_node = queue->first;

	/* se a fila está vazia ou a quantidade é maior que a primeira posição */
	if (is_empty_queue(queue) || node->quantity < queue->first->quantity) {
		node->next_node = queue->first;
		queue->first = node;
	}
	else {
		/* encontrar o lugar certo para encaixar o elemento */
        while ((current_node->next_node != NULL)
        		&& (current_node->quantity < node->quantity)) {
            
            current_node = current_node->next_node;
        }
        /* encaixar o elemento no meio da fila (ou inserir no final) */
        node->next_node = current_node->next_node;
        current_node->next_node = node;
	}

	queue->size++;

	return (queue); 
}

/* desenfileira o elemento de maior prioridade de uma fila e o retorna;
 * retornará NULL caso a fila esteja vazia */
node_t *dequeue(queue_t *queue) {
    if (!is_empty_queue(queue)) {
	    node_t *dequeued_node;
	    node_t *dequeued_node_copy;
	    dequeued_node = queue->first;

	    /* faz uma cópia do elemento desenfileirado para retorná-lo e anda com
	     * a fila */
	    memcpy(dequeued_node_copy, dequeued_node, sizeof(node_t));
        queue->first = queue->first->next_node;
        free(dequeued_node);

        queue->size--;

        /* retorna a cópia do elemento desenfileirado */
        return (dequeued_node_copy); 
    }
    return (NULL); /* a fila está vazia */
}

/* retorna 1 caso a fila recebida esteja vazia e ZERO caso contrário */
int is_empty_queue(queue_t *queue) {
    return (queue->first == NULL);
}

/* cria um novo elemento em que a quantidade é a soma dos seus dois elementos
 * filhos */
node_t *merge_to_huff(node_t *node_a, node_t *node_b) {
	
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	
	/* totem * designado para ser pai de elementos */
	new_node->character = '*';
	
	/* não haverá mais função de fila */
	new_node->next_node = NULL;
	
	/* a quantidade é a soma das quantidades dos filhos */
	new_node->quantity = (node_a->quantity + node_b->quantity);

	new_node->left = node_a;
	new_node->right = node_b;
	
	return (new_node); /* retorna o novo elemento pai */
}

/* retorna a raíz de uma árvore de huffman gerada a partir da fila recebida */
node_t *huffmanrize_queue(queue_t *queue){
	node_t *node;
	node_t *current_node_a, *current_node_b;

	if (is_empty_queue(queue)) {
		/* enquanto existir mais de um elemento na fila, pega os elementos
		 * nas duas primeiras posições, soma a quantidade dos dois e cria um
		 * novo elemento * que tem os dois elementos como filhos, e esse novo
		 * elemento voltará para a fila */
		while (queue->size > 1) {
			current_node_a = dequeue(queue);
			current_node_b = dequeue(queue);
			node = merge_to_huff(current_node_a, current_node_b);
			queue = enqueue_node(queue, node);
		}
		/* retorna o primeiro elemento na fila (e único), que será a raíz da 
		 * nova árvore Huffman */
		return (queue->first);
	}

	return (NULL);
}