/* Funções e constantes relacionadas à leitura e escrita de arquivos */

#include <stdio.h> /* fopen, fprintf, fclose ... */
#include <linux/limits.h> /* constantes limite */
#include <unistd.h> /* getcwd */
#include "global.h" /* constantes e tipos globais */


/* nomes de arquivos pré-definidos */
#define DEFAULT_FILE_NAME "avl_vs_bst" /* nome padrão do arquivo de saída */
#define HELP_FILE_NAME "help_menu" /* contém o menu de ajuda acionado por -h */


/* copia todos os caracteres de um arquivo para outro, retorna ERROR em caso
 * de falha e ZERO se executado com sucesso */
int copy_file(FILE *to, FILE *from);

/* exibe instruções de uso do programa e informações sobre o funcionamento;
 * retorna ERROR em caso de falha e ZERO se executado com sucesso */
int print_help(char *self_name, char *project_path);

/* recebe o argumento (string) na posição ZERO do programa e retorna o caminho
 * para o diretório onde o projeto se encontra */
char *get_project_path(char *args_zero);


/* copia todos os caracteres de um arquivo para outro, retorna ERROR em caso
 * de falha e ZERO se executado com sucesso */
int copy_file(FILE *to_file, FILE *from_file) {

	/* se algum dos arquivos não existir, retorne ERROR */
	if (to_file == NULL || from_file == NULL)
		return (ERROR);

	/* copiar caracter por caracter do arquivo de origem para o arquivo de
	 * destino, até que EOF seja encontrado */
	char character;
	character = getc(from_file);
	while (character != EOF) {
		fprintf(to_file, "%c", character);
		character = getc(from_file);
	}

	return (ZERO); /* a função foi executada com sucesso */
}


/* exibe instruções de uso do programa e informações sobre o funcionamento;
 * retorna ERROR em caso de falha e ZERO se executado com sucesso */
int print_help(char *self_name, char *project_path) {
	char help_file_path[PATH_MAX];
	sprintf(help_file_path, "%s/%s", project_path,
			HELP_FILE_NAME);
	/* abre o arquivo que tem as informações de ajuda e verifica se é válido
	 * retornará NULL se não for */
	FILE *help_file = fopen(help_file_path, "r");
	if (help_file == NULL) {
		fprintf(stderr, "ERRO ao abrir arquivo com informações de ajuda.\n");
		return (ERROR);
	}
	/* imprime copia o arquivo de ajuda para a saída padrão */
	printf("uso: %s", self_name);
	copy_file(stdout, help_file);
	return (ZERO); /* a função foi executada com sucesso */
}

/* recebe o argumento (string) na posição ZERO do programa e retorna o caminho
 * para o diretório onde o projeto se encontra */
char *get_project_path(char *args_zero) {
	int last_slash_index = ZERO; /* guardará posição da última / */
	int i; /* contador para laço */
	/* procura o índice da última ocorrência de uma / no array */
	for (i = ZERO; args_zero[i] != NULL_CHAR; i++) {
		if (args_zero[i] == '/') {
			last_slash_index = i;
		}
	}

	/* faz uma cópia do array até a última / */
	char *project_path = (char *)malloc(sizeof(char)*(last_slash_index+2));
	for (i = ZERO; i < last_slash_index; i++){
		project_path[i] = args_zero[i];
	}
	project_path[i] = NULL_CHAR;

	return (project_path); /* retorna o array criado */
}