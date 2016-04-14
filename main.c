#include <stdio.h> /* funções de entrada e saída */
#include "adt.h" /* tipos abstratos usados no projeto */
#include "global.h" /* constantes e tipos globais */
#include "arguments.h" /* funções de tratamento de argumentos */


int main (int args_count, char *args[]) {

	FILE *input_file;
	FILE *output_file;

	char *input_file_name;
	char *output_file_name;
	char *project_path = get_project_path(args[ZERO]);

	int arg_file_name_position;

	if (args_count <= 1) {
		fprintf(stderr, "ERRO: é preciso informar argumentos.\n");
		print_help(args[ZERO], project_path);
		return (ERROR);
	}

	if (argument_is_set(args_count, args, 'i') == FALSE) {
		fprintf(stderr, "ERRO: é necessário informar o arquivo de entrada.");
		fprintf(stderr, "\n");
		print_help(args[ZERO], project_path);
		return (ERROR);
	}

	if (argument_is_set(args_count, args, 'c') == FALSE
		&& argument_is_set(args_count, args, 'x') == FALSE) {
		fprintf(stderr, "ERRO: é necessário informar se o arquivo de entrad");
		fprintf(stderr, "a deve ser comprimido ou ex-\n\ttraído.\n");
		print_help(args[ZERO], project_path);
		return (ERROR);
	}

	if (argument_is_set(args_count, args, 'c') != FALSE
		&& argument_is_set(args_count, args, 'x') != FALSE) {
		fprintf(stderr, "ERRO: não é possível extrair e comprimir o mesmo a");
		fprintf(stderr, "rquivo.\n");
		print_help(args[ZERO], project_path);
		return (ERROR);
	}

	arg_file_name_position = (argument_is_set(args_count, args, 'i') + 1);
	if (arg_file_name_position == args_count) {
		fprintf(stderr, "ERRO: é necessário informar o caminho para o arqui");
		fprintf(stderr, "vo de entrada.\n");
		print_help(args[ZERO], project_path);
		return (ERROR);
	}

	input_file_name = args[arg_file_name_position];

	if (argument_is_set(args_count, args, 'o') == FALSE
		|| (argument_is_set(args_count, args, 'o') + 1) == args_count) {
		output_file_name = args[arg_file_name_position];
	}
	else {
		output_file_name = (argument_is_set(args_count, args, 'o') + 1);
	}

	input_file = fopen(input_file_name, "r");
	output_file = fopen(output_file_name, "w");

	int ascii[255];

	queue_t *tree;
	node_t *tree_root;
	tree = create_queue();

	int i;
	for (i = ZERO; i < 255; i++) {
		ascii[i] = ZERO;
	}

	char current_char;

	current_char = getc(input_file);
	while (current_char != EOF) {
		ascii[current_char]++;
		current_char = getc(input_file);
	}

	for (i = ZERO; i < 255; i++) {
		if (ascii[i] != ZERO) {
			if (i != '*') {
				tree = enqueue(tree, ascii[i], (char)i);
			}
			else {
				tree = enqueue(tree, ascii[i], (char)'\\');
				tree = enqueue(tree, ascii[i], (char)'*');
			}
		}
	}

	tree_root = huffmanrize_queue(tree);

	if (print_header(output_file, tree_root) == ERROR) {
		fclose(input_file);
		return (ERROR);
	}

	fclose(input_file);
	fclose(output_file);

	return (ZERO);
}