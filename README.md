# HUFFMAN
Implementação da codificação de Huffman em C.

Este programa faz parte de um projeto de Estrutura de Dados do período 2015.2 no IC (Instituto de Computação) da UFAL (Universidade Federal de Alagoas), Campus A.C. Simões;

Professor responsável: Márcio Ribeiro [http://ic.ufal.br/marcio]

Membros da equipe:

- Bharbara Correia Costa Coutinho Pereira bharbara.costa@hotmail.com
- Sergio Augusto Teixeira Amorim sata@ic.ufal.br

Trello do projeto: https://trello.com/b/ABXiNDng


Este programa comprime ou extrai arquivos usando a Codificação de Huffman. Na compressão, o arquivo de saída terá nos 3 primeiros bits o número correspondente à quantidade de bits de lixo no final do arquivo. Nos 3 bits seguintes haverá o número correspondente à quantidade de bytes ocupada pela árvore de Huffman. A árvore de Huffman será escrita após os dois primeiros bytes em pré-ordem, em codificação ASCII. Após a árvore de Huffman, haverá os bits com os dados do arquivo comprimido usando a árvore impressa como codificação. Na descompressão, as regras descritas anteriormente devem ter sido usadas para comprimir o arquivo de entrada.



####Instruções de uso:
1. Compilar o arquivo main.c;
2. Rodar com o argumento **_-h_** para obter instruções;
3. Para facilitar a execução dos códigos durante a codificação, o script compile\_and\_run.sh pode ser usado para compilar e rodar o programa; estando no diretório do programa, basta usar `chmod +x compile_and_run.sh` para adicionar permissão de execução para o arquivo e depois executá-lo com `./compile_and_run.sh`; É possível utilizar o script passando argumentos, que serão repassados para o programa na hora de rodar - ex.: `./compile_and_run.sh -c -i input.txt`;
4. Este programa foi projetado para funcionar em sistemas Linux.

#####Argumentos:
**_-h_**: exibe uma mensagem com instruções e finaliza o programa;

**_-c_**: comprimir o arquivo de entrada (não pode ser usado junto com o argumento **_-x_**)

**_-x_**: descomprimir o arquivo de entrada (não pode ser usado junto com o argumento **_-c_**)

**-i**: caminho para o arquivo de entrada

**-o**: caminho para o arquivo de saída (opcional; padrão: nome do arquivo de entrada)

É necessário informar o caminho para o arquivo de entrada e se ele deve ser comprimido ou descomprimido.



####Arquivos:

**adt.h**: Definição dos tipos abstratos de dados Árvore Binária e Fila de Prioridade e funções relacionadas à codificação de Huffman;

**arguments.h**: Funções e constantes relacionadas à manipulação de argumentos;

**compile\_and\_run.sh**: script para agilizar a compilação e executar o programa;

**file.h**: Funções e constantes relacionadas à leitura e escrita de arquivos;

**global.h**: Tipos de dados e constantes que podem ser utilizadas em qualquer parte do projeto;

**help\_menu**: Arquivo com instruções de uso do programa - é usado para imprimir as instruções quando o argumento **_-h_** é setado;

**main.c**: arquivo principal, que deve ser compilado para rodar o projeto;



####Observações:

As recomendações de estilo na escrita do código descritas neste documento foram seguidas a medida que não fugiam do escorpo do projeto: Recommended C Style and Coding Standards (Cannon) [https://www.doc.ic.ac.uk/lab/cplus/cstyle.html]

Testado usando o GCC 5.2.1 GNU/Linux