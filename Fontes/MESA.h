#include "LISTA.h"

typedef enum {
	
	MES_CondRetOK,
	
	MES_CondRetFaltouMemoria,
	
	MES_CondRetListaVazia,
	
	MES_CondRetMensagemVazia,
	
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
* Capta um comando do jogador
*/
MES_tpCondRet MES_ReceberComando( int* comando ) ;