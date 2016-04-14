/* Definição dos tipos abstratos de dados Árvore Binária e Fila de Priorida-
 * de */


#include "global.h" /* constantes globais */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */


/* estrutura de um nó de uma árvore fila binária */
typedef struct node_t__ {
    char character;
    int quantity; /* quantidade de vezes que o character aparece no arquivo */
    struct node_t__ *next_node;
    struct node_t__ *left; /* filho à esquerda do nó */
	struct node_t__ *right; /* filho à esquerda do nó */
} node_t;

/* estrutura de uma fila */
typedef struct queue_t__ {
    node_t *first;
    int size;
} queue_t;


/* cria uma fila de prioridade vazia e a retorna */
queue_t *create_queue();

/* enfileira um caracter e a quantidade de vezes que ele aparece à fila rece-
 * bida e retorna a própia fila */
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

/* imprime a árvore huff no arquivo em pré-ordem */
void print_tree_pre_order(FILE *, node_t *);

/* imprime o cabeçalho do arquivo .huff (tamanho da árvore e árvore), retorna
 * ERROR em caso se falha 
 * @@@##    O TAMANHO DO LIXO É ESCRITO COM OUTRA FUNÇÃO    ##@@@ */
int print_header(FILE *, node_t *);

/* retorna o número de nós da árvore */
int tree_size(node_t *);

/* retorna ZERO se conseguir escrever o tamanho dá árvore no arquivo ou ERROR
 * se ocorrer algum erro */
int print_size_of_tree(FILE *, node_t *);

/* retorna o byte de entrada com o bit na posição fornecida setado */
unsigned int set_bit(unsigned char current_byte, int position);


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
	    node_t *dequeued_node_copy = (node_t *)malloc(sizeof(node_t));
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
	if (!is_empty_queue(queue)) {
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

/* imprime a árvore huff no arquivo em pré-ordem */
void print_tree_pre_order(FILE *output_file, node_t *node_tree) {
	if (node_tree != NULL) {
		fprintf(output_file, "%c", node_tree->character);
		print_tree_pre_order(output_file, node_tree->left);
		print_tree_pre_order(output_file, node_tree->right);
	}
}

/* retorna ZERO se conseguir escrever o tamanho dá árvore no arquivo ou ERROR
 * se ocorrer algum erro */
int print_size_of_tree(FILE *output_file, node_t *tree_root) {
	
	unsigned int size_of_tree;
	size_of_tree = (unsigned int)tree_size(tree_root);

	/* verifica se é possível escrever a árvore em 13 bits */
	if (size_of_tree>8191) {
		fprintf(stderr, "ERRO: o tamanho da árvore não pode ser maior que 8191.\n");
		fclose(output_file);
		return (ERROR);
	}

	/* a primeira parte do número (tamanho da árvore) */
	unsigned int size_of_tree_first = (size_of_tree >> 8);

	unsigned char current_writing_char = (unsigned char)ZERO;
	unsigned int bit;
	int i;

	/* escreve os 5 primeiros bits do tamanho da árvore */
	for (i = 7; i >= ZERO ; i--) {
		bit = (size_of_tree_first >> i);
		if (bit & 1) {
			current_writing_char = set_bit(current_writing_char, i);
		}
	}
	fprintf(output_file, "%c", current_writing_char);
	
	/* escreve os 8 últimos bits do tamanho da árvore */
	current_writing_char = (unsigned char)ZERO;
	for (i = 7; i >= ZERO ; i--) {
		bit = (size_of_tree >> i);
		if (bit & 1) {
			current_writing_char = set_bit(current_writing_char, i);
		}
	}
	fprintf(output_file, "%c", current_writing_char);

	return (ZERO);
}

/* retorna o número de nós da árvore */
int tree_size(node_t *node_tree) {
	if (node_tree != NULL) {
		return ((tree_size(node_tree->left) + tree_size(node_tree->right) + 1));
	}
	return (ZERO);
}

/* imprime o cabeçalho do arquivo .huff (tamanho da árvore e árvore), retorna
 * ERROR em caso se falha 
 * @@@##    O TAMANHO DO LIXO É ESCRITO COM OUTRA FUNÇÃO    ##@@@ */
int print_header(FILE *output_file, node_t *tree_root) {
	/* se a função de imprimir o tamanho da árvore retornar ERROR, retorna
	 * ERROR também */
	if (print_size_of_tree(output_file, tree_root) == ERROR) {
		return (ERROR);
	}
	print_tree_pre_order(output_file, tree_root);
	return (ZERO);
}


/* retorna o byte de entrada com o bit na posição fornecida setado */ 
unsigned int set_bit(unsigned char current_byte, int position) {
	unsigned char mask = (1 << position);
	return (mask | current_byte);
}