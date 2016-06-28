#include "MESA.h"
#include "BARALHO.h"
#include <stdio.h>
#include <string.h>

MES_tpCondRet MES_ExibirPlacar( int valor1 , int valor2 )
{
	
	printf( "\nPlacar:\nEquipe 1: %d\tEquipe 2: %d" , valor1 , valor2 ) ;
	
	return MES_CondRetOK ;
}

MES_tpCondRet MES_ExibirCartas( LIS_tppLista pCartas )
{
	BAR_tppCarta* carta ;
	LIS_tpCondRet retornoLista ;
	char* valor = ( char* ) malloc( 7 * sizeof( char ) ) ;
	char* naipe = ( char* ) malloc( 8 * sizeof( char ) ) ;
	
	if ( valor == NULL || naipe == NULL )
	{
		return MES_CondRetFaltouMemoria ;
	}
	
	if ( pCartas == NULL )
	{
		return MES_CondRetListaNaoExiste ;
	}
	LIS_IrInicioLista( pCartas ) ;
	
	carta = (BAR_tppCarta*) LIS_ObterValor( pCartas ) ;
	
	if ( carta == NULL )
	{
		return MES_CondRetListaVazia ;
	}
	
	BAR_ObterValor( carta , valor ) ;
	BAR_ObterNaipe( carta , naipe ) ;
	printf( "\n%s de %s" , valor , naipe ) ;
	retornoLista = LIS_AvancarElementoCorrente( pCartas , 1 ) ;
	
	while ( retornoLista != LIS_CondRetFimLista )
	{
		carta = (BAR_tppCarta*) LIS_ObterValor( pCartas ) ;
		BAR_ObterValor( carta , valor ) ;
		BAR_ObterNaipe( carta , naipe ) ;
		printf( "\n%s de %s" , valor , naipe ) ;
		retornoLista = LIS_AvancarElementoCorrente( pCartas , 1 ) ;
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
	printf( "\n%s" , mensagem ) ;
	
	return MES_CondRetOK ;
}

MES_tpCondRet MES_ReceberComando( int* comando , int min , int max )
{	
	if ( min > max )
	{
		return MES_CondRetMinMaiorMax ;
	}
	printf( "\nDigite um comando entre %d e %d:\n" , min , max ) ;
	scanf( "%d" , comando ) ;
	
	while ( *comando < min || *comando > max ) 
	{
		printf( "Comando inválido. Digite um comando entre %d e %d:\n" , min , max ) ;
		scanf( "%d" , comando ) ;
	}
	
	return MES_CondRetOK ;
}