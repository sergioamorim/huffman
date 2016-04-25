/* Este programa comprime ou extrai arquivos usando a Codificação de Huffman.
 * Na compressão, o arquivo de saída terá nos 3 primeiros bits o número cor-
 * respondente à quantidade de bits de lixo no final do arquivo. Nos 3 bits
 * seguintes haverá o número correspondente à quantidade de bytes ocupada pe-
 * la árvore de Huffman. A árvore de Huffman será escrita após os dois primei-
 * ros bytes em pré-ordem, em codificação ASCII. Após a árvore de Huffman, ha-
 * verá os bits com os dados do arquivo comprimido usando a árvore impressa
 * como codificação. Na descompressão, as regras descritas anteriormente devem
 * ter sido usadas para comprimir o arquivo de entrada.
 * Este é o arquivo principal do projeto, que deve ser compilado.
 *
 * uso: ./main.out [-h] [-c] [-x] -i INPUT_FILE [-o OUTPUT_FILE]
 *
 * argumentos:
 *
 * -h 		exibe esta mensagem de ajuda e encerra o programa
 * -c 		comprimir o arquivo de entrada
 * -x		descomprimir o arquivo de entrada
 * -i INPUT_FILE
 *		arquivo de entrada do programa
 * -o OUTPUT_FILE
 *		arquivo de saída do programa sem extensão (padrão: nome do arquivo de
 *		entrada) 
 */


#include <stdio.h> /* funções de entrada e saída */
#include <string.h> /* strcat */
#include <linux/limits.h> /* constantes de limites do sistema */
#include "adt.h" /* tipos abstratos usados no projeto */
#include "global.h" /* constantes e tipos globais */
#include "arguments.h" /* funções de tratamento de argumentos */
#include "file.h" /* funções para tratamento de arquivos */


int main (int args_count, char *args[]) {

	FILE *input_file; /* guardará o arquivo de entrada */
	FILE *output_file; /* guardará o arquivo de saída */

	char *input_file_name; /* caminho para o arquivo de entrada */
	char output_file_name[PATH_MAX]; /* caminho para o arquivo de saída */
	
	/* caminho para o diretório do projeto */
	char *project_path = get_project_path(args[ZERO]);

	/* posição do array de argumentos onde o caminho para o arquivo de entra-
	 * da está */
	int arg_file_name_position;

	/* hash table que guardará o binário correspondente a cada caracter do ar-
	 * quivo */
	hash_table_t *chars_table;
	/* guardará o valor de um caracter codificado e o número de bits ocupado
	 * por ele */
	bit_char_t current_bit_char;

	/* caracter que será escrito com os caracteres codificados antes de passar
	 * para o arquivo */
	unsigned int trash_size;

	/* caso nenhum argumento tenha sido informado, não é possível continuar o
	 * programa */
	if (args_count <= 1) {
		fprintf(stderr, "ERRO: é preciso informar argumentos.\n");
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	/* caso as instruções sejam solicitadas, exibe e encerra o programa */
	if (argument_is_set(args_count, args, 'h') != FALSE) {
		
		/* caso não seja possível exibir as instruções, retornará ERROR */
		if (print_help(args[ZERO], project_path) == ERROR) {
			return (ERROR);
		}

		return (ZERO); /* o programa é encerrado sem erros */
	}

	/* caso não haja argumento para informar o arquivo de entrada, o programa
	 * não pode continuar */
	if (argument_is_set(args_count, args, 'i') == FALSE) {
		fprintf(stderr, "ERRO: é necessário informar o arquivo de entrada.");
		fprintf(stderr, "\n");
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	/* caso nenhum argumento para comprimir ou extrair o arquivo seja passado,
	 * não será possível continuar o programa */
	if (argument_is_set(args_count, args, 'c') == FALSE
		&& argument_is_set(args_count, args, 'x') == FALSE) {
		fprintf(stderr, "ERRO: é necessário informar se o arquivo de entrad");
		fprintf(stderr, "a deve ser comprimido ou ex-\n\ttraído.\n");
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	/* se ambos os argumentos (para comprimir e para extrair o arquivo) forem
	 * passados, não será possível continuar o programa */
	if (argument_is_set(args_count, args, 'c') != FALSE
		&& argument_is_set(args_count, args, 'x') != FALSE) {
		fprintf(stderr, "ERRO: não é possível extrair e comprimir o mesmo a");
		fprintf(stderr, "rquivo.\n");
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	arg_file_name_position = (argument_is_set(args_count, args, 'i') + 1);
	
	/* se não existir nenhuma string nos argumentos após o argumento -i, não
	 * é possível saber o nome do arquivo de entrada - o programa não pode
	 * continuar */
	if (arg_file_name_position == args_count) {
		fprintf(stderr, "ERRO: é necessário informar o caminho para o arqui");
		fprintf(stderr, "vo de entrada.\n");
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	/* o string com o caminho para o arquivo de entrada é definida */
	input_file_name = args[arg_file_name_position];

	/* se não houver caminho para o arquivo de saída ou se o argumento -o não
	 * for passado, o nome do arquivo de saída será igual ao nome do arquivo
	 * de entrada acrescentado da extensão .huff */
	if (argument_is_set(args_count, args, 'o') == FALSE
		|| (argument_is_set(args_count, args, 'o') + 1) == args_count) {
		strcpy(output_file_name, args[arg_file_name_position]);
		strcat(output_file_name, ".huff");
	}

	/* caso haja string com o caminho para o arquivo de saída nos argumentos, 
	 * o caminho para o arquivo de saída é definido */
	else {
		arg_file_name_position = (argument_is_set(args_count, args, 'o') + 1);
		strcpy(output_file_name, args[arg_file_name_position]);
	}

	/* abre o arquivo de entrada para leitura */
	input_file = fopen(input_file_name, "rb");

	/* caso não seja possível abrir o arquivo de entrada, uma mensagem de erro
	 * é exibida e o programa é encerrado */
	if (input_file == NULL) {
		fprintf(stderr, "ERRO: não foi possível ler o arquivo ");
		fprintf(stderr, "%s\n", input_file_name);
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	/* abre o arquivo de saída para escrita */
	output_file = fopen(output_file_name, "wb+");

	/* caso não seja possível abrir o arquivo de saída, uma mensagem de erro é
	 * exibida e o programa é encerrado */
	if (output_file == NULL) {
		fprintf(stderr, "ERRO: não foi possível escrever no arquivo ");
		fprintf(stderr, "%s\n", output_file_name);
		print_help(args[ZERO], project_path); /* as instruções são exibidas */
		return (ERROR); /* o programa é encerrado */
	}

	/* caso o argumento para compressão seja passado, o arquivo de entrada
	 * será comprimido num arquivo de saída */
	if (argument_is_set(args_count, args, 'c') != FALSE) {

		/* guardará a quantidade de vezes que cada caracter ascii aparece no
		 * arquivo */
		unsigned int ascii[ASCII_MAX];

		queue_t *tree; /* fila de prioridade que se tornará a árvore de huff*/
		node_t *tree_root; /* guardará o nó raíz da árvore de huffman */
	
		tree = create_queue(); /* inicia a fila, vazia */

		unsigned int i;
		/* inicia todas as posições do array de quantidades com ZERO */
		for (i = ZERO; i < ASCII_MAX; i++) {
			ascii[i] = ZERO;
		}
		
		/* guardará cada caracter obtido temporariamente */
		unsigned int current_char; 

		/* recebe caracter por c aracter do arquivo e incrementa a posição cor-
		 * respondente no array de quantidades */
		current_char = getc(input_file);
		while (current_char != EOF) {
			ascii[current_char]++;
			current_char = getc(input_file);
		}

		/* com o array de quantidades pronto, enfileira todos os caracteres e
		 * suas respectivas quantidades em que aparecem no arquivo na fila de
		 * prioridades que se transformará na árvore de huffman */
		for (i = ZERO; i < ASCII_MAX; i++) {
			if (ascii[i] != ZERO) {
				tree = enqueue(tree, ascii[i], (unsigned int)i);
			}
		}

		/* transforma a fila de prioridade em uma árvore de huffman e guarda
		 * o nó raíz */
		tree_root = huffmanrize_queue(tree);

		/* cria a hash table para a arvore de huffman, com os valores de cada
		 * caracter */
		chars_table = make_huff_table(tree_root, ascii);

		/* imprime o cabeçalho do arquivo HUFFMAN, exceto o tamanho do lixo
		 * que será acrescentado posteriormente - em caso de falha, o programa
		 * é encerrado e o arquivo aberto será fechado (em caso de falha, o
		 * arquivo passado para a função é fechado lá) */
		if (print_header(output_file, tree_root) == ERROR) {
			fclose(input_file);
			return (ERROR);
		}

		/* escrever o arquivo comprimido e recebe o tamanho do lixo */
		trash_size = write_compressed(input_file, output_file, chars_table);

		/* escreve o tamanho do lixo nos 3 primeiros bits do arquivo */
		write_trash_size(output_file, trash_size);

		/* libera a memória alocada para a fila/árvore e para a hash table */
		free(tree);
		free_binary_tree(tree_root);
		free_hash_table(chars_table, ASCII_MAX);
		free(chars_table);
	}
	/* caso o argumento para compressão não seja passado, então o de extração
	 * foi, pois a foi feita a verificação que apenas um dos dois deveria ser 
	 * passado, e um dos dois deveria ser passado obrigatoriamente, então o
	 * arquivo de entrada servirá para ser descomprimido em um arquivo de saí-
	 * da */
	else {
		/* receber o tamanho do lixo escrito nos três primeiros bits */
		trash_size = get_trash_size(input_file);

		/* receber o tamanho da árvore escrito nos 13 bits após o tamanho do
		 * lixo */
		unsigned int tree_size = get_tree_size(input_file);

		/* criar uma árvore de huffman de acordo com a que está escrita no
		 * arquivo */
		node_t *huff_tree = get_tree(input_file, tree_size);

		/* descomprimir o arquivo de entrada de acordo com a árvore criada */
		decompress(input_file, trash_size, tree_size, huff_tree, output_file);

		/* libera a memória alocada para a árvore */
		free_binary_tree(huff_tree);

	}

	/* fecha os arquivos abertos */
	fclose(input_file);
	fclose(output_file);

	/* libera a memória alocada para a string com o nome o caminho para o di-
	 * retório do projeto */
	free(project_path);

	return (ZERO); /* o programa foi executado com sucesso */
}