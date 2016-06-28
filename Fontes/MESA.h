#include "LISTA.h"

typedef enum {
	
	MES_CondRetOK,
	/* Retorno OK, funcionamento correto */
	
	MES_CondRetFaltouMemoria,
	/* Faltou memória em alguma operação */
	
	MES_CondRetListaVazia,
	/* Lista a ser manipulada estava vazia */
	
	MES_CondRetMensagemVazia,
	/* Mensagem a ser escrita estava vazia */
	
	MES_CondRetMinMaiorMax,
	/* Valor minimo passado maior que o valor maximo */
	
} MES_tpCondRet ;

/*
* Recebe dois inteiros e exibe-os como placar, sendo valor1 a pontuação da equipe 1 e valor2 a pontuação da equipe 2
*/
MES_tpCondRet MES_ExibirPlacar( int valor1 , int valor2 ) ;

/*
* Recebe uma lista de cartas e escreve o nome e naipe de todas as cartas
*/
MES_tpCondRet MES_ExibirCartas( tppLista cartas ) ;

/*
* Escreve um inteiro na tela
*/
MES_tpCondRet MES_ExibirValor( int valor ) ;

/*
* Escreve uma string na tela
*/
MES_tpCondRet MES_ExibirMensagem( char* mensagem ) ;

/*
* Capta um comando do jogador.
* Obriga o jogador a digitar um número entre min e max
*/
MES_tpCondRet MES_ReceberComando( int* comando , int min , int max ) ;