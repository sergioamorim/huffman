/* Tipos de dados e constantes que podem ser utilizadas em qualquer
 * parte do projeto.
 */


/* Definição do tipo booleano, para facilitar a leitura do código */
typedef int bool;
#define FALSE (0)
#define TRUE (1)

/* Constante ZERO, para facilitar a leitura do código */
#define ZERO (0)

/* Constante de erro padrão */
#define ERROR (-1)

/* Constante de caracter nulo */
#define NULL_CHAR ('\0')

/* definição do número primo maior que o inteiro correspondente ao maior char
 * na tabela ascii; é primo para garantir que não haja colisões na hash table
 */
#define ASCII_MAX_PRIME 257

/* número de elementos na tabela ascii */
#define ASCII_MAX 256

/* tamanho de um byte */
#define BYTE_SIZE 8