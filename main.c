#include <stdio.h>
#include "adt.h"
#include "global.h"

int main () {

	FILE *input_file;
	FILE *output_file;

	input_file = fopen("input.txt", "r");
	output_file = fopen("output.txt", "w");

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