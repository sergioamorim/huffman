/* Funções e constantes relacionadas à manipulação de argumentos */


#include <stdlib.h> /* atoi */
#include "global.h" /* constantes e funções globais */


/* Constantes relacionadas à manipulação de argumentos */
#define ARG_SYMBOL ('-') /* símbolo que precede argumentos */
#define MAX_VALUE_LENGTH (10) /* comprimento máximo para valor de argumento */


/* Recebe a contagem de argumentos, um array de argumentos e um argumento de-
 * sejado. Caso o argumento desejado estiver contido no array de argumentos,
 * retorna a posição do argumento no array de argumentos; caso contrário, re-
 * torna FALSE */
int argument_is_set(int args_count, char *args[], char arg);


/* Recebe a contagem de argumentos, um array de argumentos e um argumento de-
 * sejado. Caso o argumento desejado estiver contido no array de argumentos,
 * retorna a posição do argumento no array de argumentos; caso contrário, re-
 * torna FALSE */
int argument_is_set(int args_count, char *args[], char arg) {

	int i, j; /* índices dos laços para iterar posições dos argumentos */
	for (i = 1; i < args_count; i++) {
		if (args[i][ZERO] == ARG_SYMBOL){ /* o argumento pode estar a seguir */
			for (j = 1; args[i][j] != NULL_CHAR; j++){
				if (args[i][j] == arg) /* se o argumento for encontrado */
					return i; /* retorna a posição do argumento */
			}
		}
	}

	return FALSE; /* o argumento não foi encontrado */
}