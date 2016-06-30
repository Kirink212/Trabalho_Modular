/***************************************************************************
*  $MCI Módulo de implementação: MES  Mesa para jogo de truco
*
*  Arquivo gerado:              MESA.c
*  Letras identificadoras:      MES
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 - T4 de Programação Modular - Implementação do Truco
*  Autores: lfer, llages e bfranco
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data       Observações
*     2       llages   27/jun/2016  alterações nas funções ReceberComando
*                                    e ExibirCartas
*     1       llages   11/jun/2016  início desenvolvimento
*
***************************************************************************/

#include "MESA.h"
#include "BARALHO.h"
#include <stdio.h>
#include <string.h>

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MES &Exibir placar
*  ****/

	MES_tpCondRet MES_ExibirPlacar( int valor1 , int valor2 )
	{
		
		printf( "\nEquipe 1: %d\tEquipe 2: %d" , valor1 , valor2 ) ;
		
		return MES_CondRetOK ;
	}

/***************************************************************************
*
*  Função: MES &Exibir cartas
*  ****/

	MES_tpCondRet MES_ExibirCartas( LIS_tppLista pCartas )
	{
		int i = 1 ;
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
		printf( "\n%d - %s de %s" , i , valor , naipe ) ;
		retornoLista = LIS_AvancarElementoCorrente( pCartas , 1 ) ;
		
		while ( retornoLista != LIS_CondRetFimLista )
		{
			i++ ;
			carta = (BAR_tppCarta*) LIS_ObterValor( pCartas ) ;
			BAR_ObterValor( carta , valor ) ;
			BAR_ObterNaipe( carta , naipe ) ;
			printf( "\n%d - %s de %s" , i , valor , naipe ) ;
			retornoLista = LIS_AvancarElementoCorrente( pCartas , 1 ) ;
		}
		
		free( valor ) ;
		free( naipe ) ;
		return MES_CondRetOK ;
	}

/***************************************************************************
*
*  Função: MES &Exibir valor
*  ****/

	MES_tpCondRet MES_ExibirValor( int valor )
	{
		printf( "%d" , valor ) ;
		
		return MES_CondRetOK ;
	}

/***************************************************************************
*
*  Função: MES &Exibir mensagem
*  ****/

	MES_tpCondRet MES_ExibirMensagem( char* mensagem )
	{
		if ( mensagem == NULL )
		{
			return MES_CondRetMensagemVazia ;
		}
		printf( "\n%s" , mensagem ) ;
		
		return MES_CondRetOK ;
	}

/***************************************************************************
*
*  Função: MES &Receber comando
*  ****/

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
	
/********** Fim do módulo de implementação: MES  Mesa para jogo de truco **********/