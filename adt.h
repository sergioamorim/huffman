/* Definição dos tipos abstratos de dados Árvore Binária e Fila de Priorida-
 * de */


#include "global.h" /* constantes globais */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */


/* estrutura de um nó de uma árvore fila binária */
typedef struct node_t__ {
    unsigned int character;
    int quantity; /* quantidade de vezes que o character aparece no arquivo */
    struct node_t__ *next_node; /* próximo nó, quando ainda é uma fila */
    struct node_t__ *left; /* filho à esquerda do nó */
	struct node_t__ *right; /* filho à esquerda do nó */
} node_t;

/* estrutura de uma fila de nós de árvore binária */
typedef struct queue_t__ {
    node_t *first; /* primeiro nó da fila */
    int size; /* tamanho da fila */
} queue_t;

/* estrutura de um caracter codificado, com tamanho */
typedef struct bit_char_t__ {
	int size; /* numero de bits do caracter codificado */
	unsigned int b_char; /* caracter codificado */
} bit_char_t;

/* estrutura de um elemento de uma hash table */
typedef struct element_t__ {
	int key; /* caracter sem codificação */
	bit_char_t value; /* caracter codificado e seu tamanho */
	struct element_t__ *next_element;
} element_t;

/* estrutura de uma hash table */
typedef struct hash_table_t__ {
	element_t *table[ASCII_MAX_PRIME];
} hash_table_t;

/* cria uma hash table vazia e a retorna */
hash_table_t *create_hash_table(int);

/* insere um elemento em uma hash table */
void insert_on_hash_table (hash_table_t *, unsigned int, int, unsigned int,
							int);

/* retorna um elemento de uma hash table */
bit_char_t get_of_hash_table (hash_table_t *, int);

/* função para retornar o valor hasheado de uma chave */
int hash_function(int, int);

/* cria uma hash table com os nós de uma huff tree */
hash_table_t *make_huff_table(node_t *, unsigned int *);

/* cria uma fila de prioridade vazia e a retorna */
queue_t *create_queue();

/* enfileira um caracter e a quantidade de vezes que ele aparece à fila rece-
 * bida e retorna a própia fila */
queue_t *enqueue(queue_t *, unsigned int, unsigned int);

/* enfileira um elemento à fila recebida e retorna a própia fila */
queue_t *enqueue_node(queue_t *, node_t *);

/* desenfileira o elemento de maior prioridade de uma fila e o retorna */
node_t *dequeue(queue_t *);

/* retorna TRUE caso a fila recebida esteja vazia e FALSE caso contrário */
bool is_empty_queue(queue_t *);

/* retorna a raíz de uma árvore de huffman gerada a partir da fila recebida */
node_t *huffmanrize_queue(queue_t *);

/* cria um novo elemento em que a quantidade é a soma dos seus dois elementos
 * filhos */
node_t *merge_to_huff(node_t *, node_t *);

/* imprime a árvore huff no arquivo em pré-ordem, caso o caracter de controle
 * * seja encontrado, imprime um contra-barra \ antes, como escape */
void print_tree_pre_order(FILE *, node_t *);

/* imprime o cabeçalho do arquivo .huff (tamanho da árvore e árvore), retorna
 * ERROR em caso se falha 
 * @@@##    O TAMANHO DO LIXO É ESCRITO COM OUTRA FUNÇÃO    ##@@@ */
int print_header(FILE *, node_t *);

/* retorna o número de nós da árvore */
int tree_size(node_t *);

/* retorna ZERO se conseguir escrever o tamanho dá árvore no arquivo ou ERROR
 * se ocorrer algum erro; ao escrever o tamanho, o caracter de escape é levado
 * em consideração */
int print_size_of_tree(FILE *, node_t *, unsigned int);

/* retorna o byte de entrada com o bit na posição fornecida setado */
unsigned int set_bit(unsigned int, int);

/* retorna a quantidade de bits de um caracter codificado */
int bits_quantity(node_t *, unsigned int);

/* cria uma hash table vazia com a quantidade de endereços recebida e a retor-
 * na */
hash_table_t* create_hash_table(int);

/* libera a memória ocupada por todos os elementos de uma hash table */
void free_hash_table(hash_table_t *, int);

/* insere um elemento em uma hash table */
void insert_on_hash_table(hash_table_t *hash_table, unsigned int key,
							int size, unsigned int b_char,
							int addresses_quantity);

/* retorna um caracter codificado de acordo com uma huff tree */
unsigned int make_bit_char(node_t *, unsigned int);

/* retorna TRUE se um caracter pertence a uma árvore */
bool is_on_tree(node_t *, unsigned int);

/* escreve no arquivo de saída, usando a codificação pela árvore de huffman,
 * os bytes do arquivo de entrada e retorna o tamanho do lixo */
unsigned int write_compressed(FILE *, FILE *, hash_table_t *);

/* escreve o tamanho do lixo no primeiro byte do arquivo */
void write_trash_size(FILE *, unsigned int);

/* retorna TRUE se o nó recebido for uma folha e FALSE caso contrário */
bool is_leaf(node_t *);

/* retorna a quantidade de bits de lixo que está escrita no primeiro byte do
 * arquivo recebido, nos 3 primeiros bits */
unsigned int get_trash_size(FILE *);

/* retorna o tamanho da árvore que está escrito nos 13 bits seguintes ao ta-
 * manho do lixo */
unsigned int get_tree_size(FILE *);

/* retorna um array com os bytes da árvore escrita no arquivo, após os dois
 * primeiros bytes, de acordo com o tamanho da árvore recebido */
unsigned int *get_tree_array(FILE *, unsigned int);

/* retorna a árvore escrita em pré-ordem nos tree_size bytes após o segundo
 * byte no arquivo recebido */
node_t *get_tree(FILE *, unsigned int);

/* cria uma árvore que é recebida escrita em pré-ordem em um array e a retor-
 * na */
node_t *make_tree(unsigned int **);

/* libera a memória ocupada por todos os nós de uma árvore binária */
void free_binary_tree(node_t *);

/* cria um nó de uma árvore com um caracter e sem filhos */
node_t *create_node(unsigned int, node_t *, node_t *);

/* lê byte a byte do arquivo após a árvore e escreve os caracteres correspon-
 * dentes de acordo com a árvore de huffman recebida */
void decompress(FILE *, unsigned int, int, node_t *, FILE *);

/* retorna TRUE se o bit do byte estiver setado na posição recebida e FALSE
 * caso contrário */
bool is_bit_set(unsigned int, int);

/* verifica se há o caracter de controle * em uma árvore como folha e, se sim,
 * retorna a quantidade de vezes que isso acontece */
unsigned int get_escape_sequences(node_t *);

/* verifica se há o caracter de controle * em uma árvore como folha e, se sim,
 * retorna a quantidade de vezes que isso acontece */
unsigned int get_escape_sequences(node_t *node_tree) {
	unsigned int escapes_sequences = ZERO;
	if (node_tree != NULL) {
		/* se o caracter * for encontrado em um nó e esse nó for uma folha, a
		 * variável de retorno é incrementada */
		if (((node_tree->character == '*') || (node_tree->character == '\\'))
			&& is_leaf(node_tree)){
			escapes_sequences += 1;
		}
		/* verifica à esquerda e à direita do nó e soma o resultado à variável
		 * de retorno */
		escapes_sequences += get_escape_sequences(node_tree->left);
		escapes_sequences += get_escape_sequences(node_tree->right);
	}
	return (escapes_sequences); /* retorna o valor obtido */
}


/* retorna TRUE se o bit do byte estiver setado na posição recebida e FALSE
 * caso contrário */
bool is_bit_set(unsigned int character, int position) {
	unsigned int mask = 1 << position;
	return (mask & character);
}

/* lê byte a byte do arquivo após a árvore e escreve os caracteres correspon-
 * dentes de acordo com a árvore de huffman recebida */
void decompress(FILE *input_file, unsigned int trash_size, int tree_size, 
				node_t *huff_tree, FILE *output_file) {
	/* se a árvore é de tamanho ZERO, não há o que ser feito, então a função é
	 * interrompida */
	if (tree_size == ZERO) {
		return;
	}

	node_t *current_node = huff_tree;

	unsigned int current_byte; /* byte corrente no arquivo de entrada */
	unsigned int character; /* character da sequencia de bits encontrada */
	unsigned int last_byte; /* último byte do arquivo, antes de EOF */
	int bytes_total; /* total de bytes no arquivo */
	int bytes; /* índice de bytes do arquivo */
	int i; /* índice para laço */

	/* vai até o fim do arquivo e recebe o penúltimo byte (o último será EOF)
	 * e depois recebe o número do byte atual do arquivo (EOF), que será a
	 * quantidade de bytes total do arquivo */
	fseek(input_file, -1, SEEK_END);
	last_byte = getc(input_file);
	bytes_total = ftell(input_file);

	/* volta para o início do arquivo, logo após a árvore que está escrita */
	fseek(input_file, (2+tree_size), ZERO);

	/* para cada byte lido, verifica bit a bit se está setado e, se estiver
	 * anda uma vez para a direita na árvore de huffman, se não, anda uma vez
	 * para a esquerda na árvore de huffman até que se encontre um nó folha da
	 * árvore. quando um nó folha é encontrado, o caracter do nó é escrito no
	 * arquivo de saída e a leitura do restante do byte é continuada, até que
	 * se chegue ao antepenúltimo byte do arquivo (o penúltimo será escrito
	 * depois, respeitando o tamanho do lixo, e o último é EOF e não deve ser
	 * escrito) */
	current_byte = getc(input_file);
	for (bytes = (2+tree_size); bytes < (bytes_total - 1); bytes++) {
		for (i = (BYTE_SIZE - 1); i >= ZERO; i--) {
			/* se o bit estiver setado, anda para a direita na árvore */
			if (is_bit_set(current_byte, i) != FALSE) {
				if (current_node->right != NULL)
					current_node = current_node->right;
			}
			/* se o bit não estiver setado, anda para a esquerda na árvore */
			else {
				if (current_node->left != NULL)
					current_node = current_node->left;
			}
			/* se uma folha for encontrada na árvore, escreve o caracter dela
			 * no arquivo de saída */
			if (is_leaf(current_node) != FALSE) {
				fprintf(output_file, "%c", current_node->character);
				current_node = huff_tree;
			}
		}
		/* recebe o próximo byte */
		current_byte = getc(input_file);
	}

	/* os últimos bits serão recebitos somente até o tamanho do lixo, no últi-
	 * mo byte do arquivo */
	for (i = (BYTE_SIZE-1); i >= (signed int)trash_size; i--) {
		if (is_bit_set(current_byte, i) != FALSE) {
			if (current_node->right != NULL)
				current_node = current_node->right;
		}
		else {
			if (current_node->left != NULL)
				current_node = current_node->left;
		}
		if (is_leaf(current_node) != FALSE) {
			fprintf(output_file, "%c", current_node->character);
			current_node = huff_tree;
		}
	}
	
}


/* retorna um array com os bytes da árvore escrita no arquivo, após os dois
 * primeiros bytes, de acordo com o tamanho da árvore recebido */
unsigned int *get_tree_array(FILE *input_file, unsigned int tree_size) {
	unsigned int i;

	/* cria um array com o tamanho da árvore recebido */
	int *tree_array;
	tree_array = (unsigned int *)malloc(sizeof(unsigned int)*(tree_size));
	/* vai até o terceito byte do arquivo para receber os caracteres (o ter-
	 * ceiro byte é o primeiro byte da árvore) */
	fseek(input_file, 2, ZERO);

	/* recebe os caracteres em sequencia tree_size vezes */
	for (i = ZERO; i < tree_size; i++) {
		tree_array[i] = getc(input_file);
	}
	return (tree_array); /* retorna o endereço para o array criado */
}

/* cria uma árvore com o caracter e árvores esquerda e direita, respectivamen-
 * te, e retorna o endereço para a árvore criada */
node_t *create_node(unsigned int character, node_t *left, node_t *right) {
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->character = character;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

/* cria uma árvore que é recebida escrita em pré-ordem em um array e a retor-
 * na */
node_t *make_tree(unsigned int **tree_array) {

	/* se o nó for *, faz o nó da esquerda primeiro, depois anda uma posição
	 * no array (após o nó da esquerda) e retorna o nó da direita já incluso
	 * no nó que está sendo criado com o * */
	if (**tree_array == '*') {

		node_t *left;
		*tree_array = (*tree_array + 1); /* anda uma posição no array */
		left = make_tree(tree_array);
		*tree_array = (*tree_array + 1); /* anda uma posição no array */
		return (create_node('*', left, make_tree(tree_array)));

	}
	/* se o nó for \, retorna uma folha com o próximo caracter */
	else if (**tree_array == '\\') {
		*tree_array = (*tree_array + 1); /* anda uma posição no array */
		return (create_node(**tree_array, NULL, NULL));

	}

	/* se o nó não for * nem \, retorna uma folha com o caracter atual */
	return (create_node(**tree_array, NULL, NULL)); 
}

/* retorna a árvore escrita em pré-ordem nos tree_size bytes após o segundo
 * byte no arquivo recebido */
node_t *get_tree(FILE *input_file, unsigned int tree_size) {
	if (tree_size == ZERO) {
		return NULL;
	}

	/* recebe o array com a árvore em pré-ordem */
	unsigned int *tree_array;
	tree_array = get_tree_array(input_file, tree_size);

	/* guarda a primeira posição do array, que será modificado pela função que
	 * cria a árvore, para que a memória alocada para o array possa ser libe-
	 * rada depois */
	unsigned int *tree_array_zero;
	tree_array_zero = tree_array;

	/* recebe a árvore criada a partir do array recebido */
	node_t *tree_root = make_tree(&tree_array);
	
	/* libera a memória alocada para o array */
	free(tree_array_zero);

	return (tree_root);
}

/* libera a memória ocupada por todos os nós de uma árvore binária */
void free_binary_tree(node_t *node) {
	if (node != NULL) {
		free_binary_tree(node->left);
		free_binary_tree(node->right);
		free(node);
	}
}

/* retorna o tamanho da árvore que está escrito nos 13 bits seguintes ao ta-
 * manho do lixo */
unsigned int get_tree_size(FILE *input_file) {
	unsigned int tree_size;
	unsigned char first_byte;
	unsigned int second_byte;

	fseek(input_file, ZERO, SEEK_SET); /* volta ao início do arquivo */

	/* recebe os dois primeiros bytes do arquivo */
	first_byte = getc(input_file); 
	second_byte = getc(input_file);

	/* apaga os três primeiros bits do primeiro byte, pois só interessa os 5
	 * bits restantes */
	first_byte = (first_byte << TRASH_BITS_QUANTITY);
	first_byte = (first_byte >> TRASH_BITS_QUANTITY);

	/* o tamanho da árvore é a união entre os 5 últimos bits do primeiro byte
	 * e o segundo byte */
	tree_size = ((first_byte << BYTE_SIZE) | second_byte);

	return (tree_size); /* retorna o valor que estava escrito */
}

/* retorna a quantidade de bits de lixo que está escrita no primeiro byte do
 * arquivo recebido, nos 3 primeiros bits */
unsigned int get_trash_size(FILE *input_file) {
	unsigned int trash_size = ZERO;
	unsigned int first_byte;
	fseek(input_file, ZERO, SEEK_SET); /* volta ao início do arquivo */
	first_byte = getc(input_file); /* recebe o primeiro byte do arquivo */
	trash_size = (unsigned int)(first_byte 
								>> (BYTE_SIZE - TRASH_BITS_QUANTITY));
	return (trash_size); /* retorna o valor que estava escrito */
}

/* retorna TRUE se o nó recebido for uma folha e FALSE caso contrário */
bool is_leaf(node_t *binary_tree) {
	return ((binary_tree != NULL) && (binary_tree->left == NULL) 
			 && (binary_tree->right == NULL));
}

/* escreve o tamanho do lixo no primeiro byte do arquivo */
void write_trash_size(FILE *output_file, unsigned int trash_size) {
	unsigned int first_byte;
	unsigned int writing_char;
	fseek(output_file, ZERO, SEEK_SET); /* volta ao início do arquivo */
	first_byte = getc(output_file); /* recebe o primeiro byte do arquivo */
	writing_char = ZERO; /* inicializa o byte que será escrito*/
	writing_char = (first_byte | (trash_size << 
					(BYTE_SIZE - TRASH_BITS_QUANTITY)));
	fseek(output_file, ZERO, SEEK_SET); /* volta ao início do arquivo */
	fprintf(output_file, "%c", writing_char); /* escreve o byte */
}

/* escreve no arquivo de saída, usando a codificação pela árvore de huffman,
 * os bytes do arquivo de entrada e retorna o tamanho do lixo */
unsigned int write_compressed(FILE *input_file, FILE *output_file, 
								hash_table_t *chars_table) {

		unsigned int trash_size = ZERO; /* tamanho do lixo, será retornado */
		int writing_index = BYTE_SIZE; 
		unsigned int bits_to_next_char = (unsigned int)ZERO;
		unsigned int writing_char = (unsigned int)ZERO;
		bit_char_t current_bit_char;
		/* volta ao início do arquivo para lê-lo por completo */
		fseek(input_file, ZERO, SEEK_SET);
		unsigned int current_char = (unsigned int)getc(input_file);
		while ((signed int)current_char != EOF) {
			current_bit_char = get_of_hash_table(chars_table, current_char);
			/* se o caracter codificado não couber por completo no byte cor-
			 * rente, escreve até onde der, grava no arquivo, e escreve o que
			 * faltou no próximo byte */
			if ((writing_index - current_bit_char.size) < ZERO) {

				bits_to_next_char = ((writing_index
										- current_bit_char.size) * (-1));
				/* pode acontecer de o código para um byte ser maior do que 
				 * 8 bits, então é necessário tratar os casos onde, mesmo es-
				 * crevendo no próximo byte, não vai ser possível escrevê-lo
				 * por inteiro. caso o restante do código seja menor que um
				 * byte, podemos escrever o restante do código no próximo byte
				 * e atualizar o writing_index, para sinalizar em que parte do
				 * byte estamos */
				if (bits_to_next_char < BYTE_SIZE) {
					writing_char = (writing_char | (current_bit_char.b_char >>
							   bits_to_next_char));
					fprintf(output_file, "%c", writing_char);
					writing_char = (unsigned int)ZERO;
					writing_index = BYTE_SIZE;
					writing_char = (current_bit_char.b_char <<
										(writing_index - bits_to_next_char));
					writing_index -= bits_to_next_char;
				}
				/* caso o restante do código seja exatamente 1 byte, basta
				 * escrevê-lo no arquivo */
				else if (bits_to_next_char == BYTE_SIZE) {
					writing_char = (writing_char | (current_bit_char.b_char >>
							   bits_to_next_char));
					fprintf(output_file, "%c", writing_char);
					writing_char = (unsigned int)ZERO;
					writing_index = BYTE_SIZE;
					writing_char = current_bit_char.b_char;
					writing_index -= bits_to_next_char;
					fprintf(output_file, "%c", writing_char);
					writing_char = (unsigned int)ZERO;
					writing_index = BYTE_SIZE;
				}
				/* caso o restante do código seja maior que um byte, é preciso
				 * escrever as três partes do código individualmente: primeiro
				 * a parte que cabe no byte atual, depois a parte central do
				 * código e, depois, o final deve ser escrito no próximo byte
				 */
				else {
					writing_char = (writing_char | (current_bit_char.b_char >>
							   bits_to_next_char));
					fprintf(output_file, "%c", writing_char);
					writing_char = (unsigned int)ZERO;
					writing_index = BYTE_SIZE;
					writing_char = (current_bit_char.b_char >>
										(bits_to_next_char - BYTE_SIZE));
					fprintf(output_file, "%c", writing_char);
					writing_char = (unsigned int)ZERO;
					writing_index = BYTE_SIZE;
					writing_char = (current_bit_char.b_char <<
										(BYTE_SIZE - 
											(bits_to_next_char - BYTE_SIZE)));
					writing_index -= (bits_to_next_char - BYTE_SIZE);
				}
			}
			/* se o caracter codificado ocupar exatamente o que falta para
			 * completar o byte corrente, escreve-o, grava o byte corrente no
			 * arquivo e renova o byte de escrita */
			else if ((writing_index - current_bit_char.size) == ZERO) {
				writing_char = (unsigned int)(writing_char
												| current_bit_char.b_char);
				fprintf(output_file, "%c", writing_char);
				writing_index = BYTE_SIZE;
				writing_char = (unsigned int)ZERO;
			}
			/* se ainda sobrar espaço no byte corrente depois de escrever o
			 * caracter codificado, apenas faz isso */
			else {
				writing_char = (unsigned int)(writing_char
								| (current_bit_char.b_char
									<< (writing_index
										- current_bit_char.size)));
				writing_index -= current_bit_char.size;
			}
			current_char = (unsigned int)getc(input_file);
		}
		/* verifica se o byte corrente está vazio e, caso não esteja, grava-o
		 * no arquivo e salva o novo tamanho do lixo */
		if (writing_index != BYTE_SIZE){
			fprintf(output_file, "%c", writing_char);
			if (writing_index > ZERO) {
				trash_size = (unsigned int)writing_index;
			}
		}
		return ((unsigned int)trash_size); /* retorna o tamanho do lixo */
}

/* cria uma hash table com os nós de uma huff tree */
hash_table_t *make_huff_table(node_t *huff_tree, unsigned int *ascii) {
	hash_table_t *hash_table = create_hash_table(ASCII_MAX);
	unsigned int i; /* será o índice que representará cada um dos caracteres */
	unsigned int size; /* tamanho do caracter codificado */
	unsigned int b_char; /* caracter codificado */

	/* anda pelo array de quantidades e, para cada caracter que apareceu no
	 * texto, inclui ele na hash table junto com seu correspondente codificado
	 * de acordo com a huff tree recebida */
	for (i = ZERO; i < ASCII_MAX; i++) {
		if (ascii[i] != ZERO) {
			size = bits_quantity(huff_tree, i);
			/* se o tamanho retornado for ZERO, então o caracter está na raíz
			 * da árvore huff, seu tamanho sera 1 bit e seu valor será ZERO,
			 * anyway */
			if (size == ZERO) {
				size = 1;
			}
			b_char = make_bit_char(huff_tree, i);
			insert_on_hash_table(hash_table, i, size, b_char,
								 ASCII_MAX_PRIME);
		}
	}
	return (hash_table); /* retorna a hash table criada */
}

/* retorna a quantidade de bits de um caracter codificado */
int bits_quantity(node_t *binary_tree, unsigned int character) {
	
	if (binary_tree != NULL) {

		/* retorna ZERO se o caracter for o próprio da árvore */
		if (binary_tree->character == character && is_leaf(binary_tree)) {
			return (ZERO);
		}
		if (binary_tree->left != NULL) {

			/* se o lado direito não existe mas o lado esquerdo existe, então
		 	 * retorna recursivamente o lado esquerdo */
			if (binary_tree->right == NULL) {
				return (bits_quantity(binary_tree->left, character) + 1);
			}

			/* se ambos os lados existem, verifica a qual lado o caracter per-
			 * tence e retorna o lado correspondente recursivamente */
			if (is_on_tree(binary_tree->left, character) != FALSE) {
				return(bits_quantity(binary_tree->left, character) + 1);
			}
			return (bits_quantity(binary_tree->right, character) + 1);
		}

		/* se o lado esquerdo não existe mas o lado direito existe, então re-
		 * torna recursivamente o lado direito */
		if (binary_tree->right != NULL) {
			return (bits_quantity(binary_tree->right, character) + 1);
		}
	}
	return (ERROR); /* se a árvore for nula, retorna ERROR */
}

/* retorna TRUE se um caracter pertence a uma árvore */
bool is_on_tree(node_t *binary_tree, unsigned int character) {
	if (binary_tree != NULL) {
		/* se o próprio nó for uma folha e tiver o caracter recebido, retorna
		 * TRUE */
		if (is_leaf(binary_tree) && binary_tree->character == character) {
			return (TRUE);
		}
		/* se o nó não tiver o caracter recebido, retorna recursivamente para
		 * a esquerda e para a direita do nó */
		return (is_on_tree(binary_tree->left, character)
				|| is_on_tree(binary_tree->right, character));
	}
	/* se o nó for NULL, retorna FALSE */
	return (FALSE);
}

/* retorna um caracter codificado de acordo com uma huff tree */
unsigned int make_bit_char(node_t *huff_tree, unsigned int character) {
	unsigned int bit_char = ZERO; /* inicia o bit_char zerado*/
	node_t *current_node = huff_tree;
	
	if (huff_tree != NULL) {

		/* navega pela huff tree em busca do caracter e, a cada nível, seta
		 * ou não o último bit, enquanto arrasta os bits anteriores para a
		 * esquerda */
		while(current_node != NULL
				&& !(is_leaf(current_node) && (current_node->character 
												== character))) {
			/* se o caracter estiver à direita na árvore, seta o último bit e
			 * anda para a direita */
			if (is_on_tree(current_node->right, character)) {
				bit_char = set_bit(bit_char, ZERO);
				current_node = current_node->right;
			}
			/* se não estiver à direita, apenas anda para a esquerda */
			else {
				current_node = current_node->left;
			}
			/* arrasta os bits para a esquerda para setar ou não o próximo */
			bit_char = (bit_char << 1);
		}
		/* retorna os bits uma casa à direita, pois eles foram arrastados à 
		 * esquerda uma vez a mais que o necessário */
		bit_char = (bit_char >> 1);
	}
	return (bit_char); /* retorna o bit_char criado */
}

/* cria uma hash table vazia e a retorna */
hash_table_t* create_hash_table(int addresses_quantity) {
	hash_table_t *hash_table = malloc(sizeof(hash_table_t));
	int i;
	for (i = ZERO; i < addresses_quantity; i++) {
		hash_table->table[i] = NULL;
	}
	return hash_table;
}

/* libera a memória ocupada por todos os elementos de uma hash table */
void free_hash_table(hash_table_t *hash_table, int addresses_quantity) {
	int i;
	for (i = ZERO; i < addresses_quantity; i++) {
		if (hash_table->table[i] != NULL) {
			free(hash_table->table[i]);
		}
	}
}

/* função para retornar o valor hasheado de uma chave */
int hash_function(int key, int addresses_quantity){
	return (key % addresses_quantity);
}

/* insere um elemento em uma hash table */
void insert_on_hash_table(hash_table_t *hash_table, unsigned int key,
							int size, unsigned int b_char,
							int addresses_quantity) {

	element_t *new_element = (element_t *)malloc(sizeof(element_t));;
	int hash = hash_function(key, addresses_quantity);
	new_element->key = key;
	new_element->value.size = size;
	new_element->value.b_char = b_char;
	new_element->next_element = NULL;
	if (hash_table->table[hash] != NULL) {
		element_t *current_element = hash_table->table[hash];
		while (current_element->next_element != NULL) {
			current_element = current_element->next_element;
		}
		current_element->next_element = new_element;
	}
	else {
		hash_table->table[hash] = new_element;
	}
}

/* cria uma fila de prioridade vazia e a retorna */
queue_t *create_queue() {
    queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
    new_queue->first = NULL;
    new_queue->size = ZERO;
    return (new_queue);
}

/* enfileira um caracter à fila recebida e retorna a própia fila */
queue_t *enqueue(queue_t *queue, unsigned int quantity,
					unsigned int character) {
    
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

/* retorna TRUE caso a fila recebida esteja vazia e FALSE caso contrário */
bool is_empty_queue(queue_t *queue) {
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

/* imprime a árvore huff no arquivo em pré-ordem, caso o caracter de controle
 * * seja encontrado, imprime um contra-barra \ antes, como escape */
void print_tree_pre_order(FILE *output_file, node_t *node_tree) {
	if (node_tree != NULL) {
		if (((node_tree->character == '*') || (node_tree->character == '\\'))
			&& is_leaf(node_tree)){
			fprintf(output_file, "%c", '\\');
		}
		fprintf(output_file, "%c", node_tree->character);
		print_tree_pre_order(output_file, node_tree->left);
		print_tree_pre_order(output_file, node_tree->right);
	}
}


/* retorna ZERO se conseguir escrever o tamanho dá árvore no arquivo ou ERROR
 * se ocorrer algum erro; ao escrever o tamanho, o caracter de escape é levado
 * em consideração */
int print_size_of_tree(FILE *output_file, node_t *tree_root,
						unsigned int escapes_sequences) {
	
	unsigned int size_of_tree;
	size_of_tree = (unsigned int)tree_size(tree_root);
	size_of_tree += escapes_sequences;

	/* verifica se é possível escrever a árvore em 13 bits */
	if (size_of_tree>8191) {
		fprintf(stderr, "ERRO: o tamanho da árvore não pode ser maior que");
		fprintf(stderr, " 8191.\n");
		fclose(output_file);
		return (ERROR);
	}

	/* a primeira parte do número (tamanho da árvore) */
	unsigned int size_of_tree_first = (size_of_tree >> 8);

	unsigned int current_writing_char = (unsigned int)ZERO;
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
	current_writing_char = (unsigned int)ZERO;
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
		return (tree_size(node_tree->left) + tree_size(node_tree->right) + 1);
	}
	return (ZERO);
}

/* imprime o cabeçalho do arquivo .huff (tamanho da árvore e árvore), retorna
 * ERROR em caso se falha 
 * @@@##    O TAMANHO DO LIXO É ESCRITO COM OUTRA FUNÇÃO    ##@@@ */
int print_header(FILE *output_file, node_t *tree_root) {
	unsigned int escapes_sequences = ZERO;
	escapes_sequences = get_escape_sequences(tree_root);

	fseek(output_file, ZERO, SEEK_SET);

	/* se a função de imprimir o tamanho da árvore retornar ERROR, retorna
	 * ERROR também */
	if (print_size_of_tree(output_file, tree_root, escapes_sequences)
		== ERROR) {
		return (ERROR);
	}


	print_tree_pre_order(output_file, tree_root);

	return (ZERO);
}


/* retorna o byte de entrada com o bit na posição fornecida setado */ 
unsigned int set_bit(unsigned int current_byte, int position) {
	unsigned int mask = (1 << position);
	return (mask | current_byte);
}

/* retorna um elemento de uma hash table */
bit_char_t get_of_hash_table (hash_table_t *hash_table, int key) {
	int hash = hash_function(key, ASCII_MAX_PRIME);
	bit_char_t bit_char;
	bit_char.size = ZERO;
	bit_char.b_char = (unsigned int)ZERO;
	element_t *current_element = hash_table->table[hash];
	if (current_element != NULL) {
		while (current_element != NULL && current_element->key != key) {
			current_element = current_element->next_element;
		}
		return (current_element->value);
	}
	return (bit_char);
}