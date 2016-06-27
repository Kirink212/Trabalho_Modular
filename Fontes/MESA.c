#include "MESA.h"
#include "BARALHO.h"
#include <stdio.h>
#include <string.h>

MES_tpCondRet MES_ExibirPlacar( int valor1 , int valor2 )
{
	
	printf( "Placar:\nEquipe 1: %d\tEquipe 2: %d\n" , valor1 , valor2 ) ;
	
	return MES_CondRetOK ;
}

MES_tpCondRet MES_ExibirCartas( tppLista cartas )
{
	BAR_tppCarta* carta ;
	LIS_tpCondRet retornoLista ;
	char* valor = ( char* ) malloc( 7 * sizeof( char ) ) ;
	char* naipe = ( char* ) malloc( 8 * sizeof( char ) ) ;
	
	if ( valor == NULL || naipe == NULL )
	{
		return MES_CondRetFaltouMemoria ;
	}
	
	LIS_IrInicioLista( cartas ) ;
	
	carta = (BAR_tppCarta*) LIS_ObterValor( cartas ) ;
	
	if (carta == NULL )
	{
		return MES_CondRetListaVazia ;
	}
	
	BAR_ObterValor( carta , valor ) ;
	BAR_ObterNaipe( carta , naipe ) ;
	printf( "%s de %s\n" , valor , naipe ) ;
	retornoLista = LIS_AvancarElementoCorrente( cartas , 1 ) ;
	
	while ( retornoLista != LIS_CondRetFimLista )
	{
		carta = (BAR_tppCarta*) LIS_ObterValor( cartas ) ;
		BAR_ObterValor( carta , valor ) ;
		BAR_ObterNaipe( carta , naipe ) ;
		printf( "%s de %s\n" , valor , naipe ) ;
		retornoLista = LIS_AvancarElementoCorrente( cartas , 1 ) ;
	}
	
	free( valor ) ;
	free( naipe ) ;
	return MES_CondRetOK ;
}

MES_tpCondRet MES_ExibirValor( int valor )
{
	printf( "%d" , valor ) ;
	
	return MES_CondRetOK ;
}

MES_tpCondRet MES_ExibirMensagem( char* mensagem )
{
	if ( mensagem == NULL )
	{
		return MES_CondRetMensagemVazia ;
	}
	printf( mensagem ) ;
	
	return MES_CondRetOK ;
}

MES_tpCondRet MES_ReceberComando( int* comando )
{	
	scanf( "%d" , comando ) ;
	
	return MES_CondRetOK ;
}