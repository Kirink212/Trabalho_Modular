﻿/***************************************************************************
*  $MCI Módulo de implementação: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabouço para a automação de testes 
*								de programas redigidos em C
*
*  Projeto: INF 1301 - T2 de Programação Modular - Implementação do Truco
*  Autores: Luís Fernando Teixeira Bicalho (lfer),  
*			Leonardo Lages de Alencar(llages) e 
*			Bruno D'Almeida Franco (bfranco)
*
*  $HA Histórico de evolução:
*     Versão	Autor		Data				Observações
*     6         llages  21/jul/2016         alterações nas funções
*                                           obtervalor e obternaipe
*                                           para preencherem uma
*                                           string dada
*     5         llages  08/maio/2016        alteração do nome de
*                                           variáveis para seguir
*                                           os padrões e adição de
*                                           assertivas
*     4			lfer	05/maio/2016		adição e revisão de 
*											comentários no código
*     3			lfer	03/maio/2016		criação das condições 
*											de retorno e adição de 
*                                           funções
*     2			llages	22/abr/2016			revisão de implementação
*     1			lfer e	16/abr/2016			início desenvolvimento
*				bfranco
*
***************************************************************************/

#include "Baralho.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/***********************************************************************
*
*  $TC Tipo de dados: BAR Lista de Valores
*
*  $ED Descrição do tipo
*     Tipos de valores possíveis para um elemento do tipo carta
*
*
***********************************************************************/
typedef enum valor {
	QUATRO,
	/* Menor valor existente no baralho é 4 */
	CINCO,
	/* Valor 5 */
	SEIS,
	/* Valor 6 */
	SETE,
	/* Valor 7 */
	DAMA,
	/* Valor Q ou Dama */
	VALETE,
	/* Valor J ou Valete */
	REI,
	/* Valor K ou Rei */
	AS,
	/* Valor A ou Ás */
	DOIS,
	/* Valor 2 */
	TRES
	/* Maior valor existente no baralho é 3 */
} Valor;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Lista de Naipes
*
*  $ED Descrição do tipo
*     Tipos de naipes possíveis para um elemento do tipo carta
*
*
***********************************************************************/
typedef enum naipe {
	OUROS,
	/* Naipe representado pelo símbolo de Ouros (♦)*/
	ESPADAS,
	/* Naipe representado pelo símbolo de Espadas (♠) */
	COPAS,
	/* Naipe representado pelo símbolo de Espadas (♥) */
	PAUS
	/* Naipe representado pelo símbolo de Espadas (♣) */
} Naipe;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Tipo carta
*
*
***********************************************************************/

typedef struct carta BAR_tpCarta ;
struct carta {
	Valor valor;
	Naipe naipe;
};

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BAR  &Criar baralho
*  ****/
LIS_tppLista BAR_CriarBaralho( )
{
	int i, 
      j ;
	/* Vetores de Valor e de Naipe */
	Valor val[10] = { QUATRO , CINCO , SEIS , SETE , DAMA ,
					  VALETE , REI , AS , DOIS , TRES } ;
	Naipe nap[4] = { OUROS , ESPADAS , COPAS , PAUS } ;

	BAR_tppCarta carta = NULL ;

	// Cria o baralho como uma lista vazia 
	LIS_tppLista baralho = LIS_CriarLista( NULL ) ;

	// Percorre os vetores de Valor e Naipe declarados
	for( i = 0 ; i < 4 ; i++ )
	{
		for( j = 0 ; j < 10 ; j++ )
		{
			//Cada carta sendo alocada dinamicamente à cada iteração
			carta = (BAR_tppCarta) malloc( sizeof( BAR_tpCarta ) ) ; 

			if( carta == NULL )
			{
				return NULL ;
			}/* if */

			// Elemento inicializado e inserido na lista com valor e naipe
			carta->naipe = nap[i] ;
			carta->valor = val[j] ;
			if(LIS_InserirElementoApos( baralho, carta) != LIS_CondRetOK )
			{
				return NULL ;
			}/* if */
		}
	}
	return baralho ;
}/* Fim função: BAR  &Criar baralho */

/***************************************************************************
*
*  Função: BAR &Liberar Baralho
*  ****/

BAR_tpCondRet BAR_LiberarBaralho( LIS_tppLista baralho )
{
	BAR_tppCarta carta ;
	
	// Assertiva que verifica se baralho está vazio
	#ifdef _DEBUG
		assert( baralho != NULL ) ;
	#endif

	// Obtendo o valor da carta no topo do baralho
	// Movendo o ponteiro para o começo da lista de cartas
	LIS_IrInicioLista( baralho ) ;
	
	carta = (BAR_tppCarta) LIS_ObterValor( baralho ) ;

	// Percorre o baralho enquanto não chega ao seu final
	while( carta != NULL )
	{
		//Verificando se a retirada da carta foi bem sucedida
		if (LIS_ExcluirElemento( baralho ) != LIS_CondRetOK )
		{
			return BAR_CondRetCartaNaoExcluida ;
		}/* if */

		/* Liberando a carta e inicializando a próxima a ser retirada na
		  iteração, respectivamente */
		free( carta ) ;
		carta = (BAR_tppCarta) LIS_ObterValor( baralho ) ;

	}/* while */
	
	LIS_DestruirLista( baralho ) ;

	return BAR_CondRetOK ;
}/* Fim função: BAR  &Liberar baralho */

/***************************************************************************
*
*  Função: BAR &Embaralhar cartas
*  ****/

BAR_tpCondRet BAR_EmbaralharCartas(LIS_tppLista baralho)
{
	int random,
      i ;
	void* carta ;
	
	// Assertiva que verifica se baralho está vazio
	#ifdef _DEBUG
		assert( baralho != NULL ) ;
	#endif
	
	srand( (unsigned int) time( NULL ) ) ;
	for( i = 0 ; i < 50 ; i++ )
	{
		random = rand() % 40 ;
		LIS_IrInicioLista( baralho ) ;

		if ( LIS_AvancarElementoCorrente( baralho, random ) == LIS_CondRetListaVazia )
		{
			return BAR_CondRetErroAndarListaVazia ;
		}/* if */

		carta = LIS_ObterValor( baralho ) ;

		if ( LIS_ExcluirElemento( baralho ) != LIS_CondRetOK )
		{
			return BAR_CondRetCartaNaoExcluida;
		}/* if */

		random = rand() % 40 ;
		LIS_IrInicioLista( baralho ) ;

		if ( LIS_AvancarElementoCorrente( baralho , random ) == LIS_CondRetListaVazia )
		{
			return BAR_CondRetErroAndarListaVazia ;
		}/* if */

		if ( LIS_InserirElementoAntes( baralho , carta ) != LIS_CondRetOK )
		{
			return BAR_CondRetFaltouMemoria ;
		}/* if */

	}/* for */
	return BAR_CondRetOK ;
}/* Fim função: BAR  &Embaralhar cartas*/

/***************************************************************************
*
*  Função: BAR &Distribuir cartas
*  ****/

BAR_tpCondRet BAR_DistribuirCartas(LIS_tppLista baralho, LIS_tppLista jogador)
{
	void* carta ;
	int i ;
	// Assertiva que verifica se baralho e jogador estão vazios
	#ifdef _DEBUG
		assert( baralho != NULL && jogador != NULL) ;
	#endif
	for( i = 0 ; i < 3 ; i++ )
	{
		LIS_IrInicioLista( baralho ) ;
		carta = LIS_ObterValor( baralho ) ;
		if( LIS_ExcluirElemento( baralho ) != LIS_CondRetOK )
		{
			return BAR_CondRetCartaNaoExcluida ;
		}
		LIS_InserirElementoApos( jogador, carta) ;
	}
	return BAR_CondRetOK ;
}/* Fim função: BAR  &Distribuir cartas */

/***************************************************************************
*
*  Função: BAR &Escolher manilha
*  ****/

int BAR_EscolherManilha(LIS_tppLista baralho , char* manilha )
{
	BAR_tppCarta vira ;
	
	// Assertiva que verifica se baralho está vazio
	#ifdef _DEBUG
		assert( baralho != NULL ) ;
	#endif

	/* Posiciona-se o ponteiro no início da lista de cartas e obtém o valor
	  do primeiro elemento, que na nossa especificação é denominado "vira" */
	LIS_IrInicioLista( baralho ) ;
	vira = (BAR_tppCarta) LIS_ObterValor( baralho ) ;

	/* Como TRES é o valor mais alto do baralho, escolhe o menos valor 
	como manilha */
	if ( vira->valor == TRES )
	{
		if ( manilha != NULL )
		{
			strcpy( manilha , "QUATRO" ) ;
		}
		return QUATRO ;
	}
	// Considerando todos os outros casos, a manilha é o valor logo acima
	else
	{
		if ( manilha != NULL ) 
		{
			if ( vira->valor == QUATRO )
			{
				strcpy( manilha , "CINCO" ) ;
			}
			else if ( vira->valor == CINCO )
			{
				strcpy( manilha , "SEIS" ) ;
			}
			else if ( vira->valor == SEIS )
			{
				strcpy( manilha , "SETE" ) ;
			}
			else if ( vira->valor == SETE )
			{
				strcpy( manilha , "DAMA" ) ;
			}
			else if ( vira->valor == DAMA )
			{
				strcpy( manilha , "VALETE" ) ;
			}
			else if ( vira->valor == VALETE )
			{
				strcpy( manilha , "REI" ) ;
			}
			else if ( vira->valor == REI )
			{
				strcpy( manilha , "AS" ) ;
			}
			else if ( vira->valor == AS )
			{
				strcpy( manilha , "DOIS" ) ;
			}
			else if ( vira->valor == DOIS )
			{
				strcpy( manilha , "TRES" ) ;
			}
		}
		return (vira->valor) + 1 ;
	}/* if */

}/* Fim função: BAR  &Escolher manilha */

/***************************************************************************
*
*  Função: BAR &Obter valor
*  ****/

int BAR_ObterValor( BAR_tppCarta carta , char* valor )
{
	// Assertiva que verifica se carta está vazia
	#ifdef _DEBUG
		assert( carta != NULL ) ;
	#endif
	
	if ( valor != NULL )
	{
		if ( carta->valor == QUATRO )
		{
			strcpy( valor , "QUATRO" ) ;
		}
		else if ( carta->valor == CINCO )
		{
			strcpy( valor , "CINCO" ) ;
		}
		else if ( carta->valor == SEIS )
		{
			strcpy( valor , "SEIS" ) ;
		}
		else if ( carta->valor == SETE )
		{
			strcpy( valor , "SETE" ) ;
		}
		else if ( carta->valor == DAMA )
		{
			strcpy( valor , "DAMA" ) ;
		}
		else if ( carta->valor == VALETE )
		{
			strcpy( valor , "VALETE" ) ;
		}
		else if ( carta->valor == REI )
		{
			strcpy( valor , "REI" ) ;
		}
		else if ( carta->valor == AS )
		{
			strcpy( valor , "AS" ) ;
		}
		else if ( carta->valor == DOIS )
		{
			strcpy( valor , "DOIS" ) ;
		}
		else if ( carta->valor == TRES )
		{
			strcpy( valor , "TRES" ) ;
		}
	}

	return carta->valor ;

}/* Fim função: BAR  &Obter valor*/

/***************************************************************************
*
*  Função: BAR &Obter naipe
*  ****/

int BAR_ObterNaipe( BAR_tppCarta carta , char* naipe )
{
	// Assertiva que verifica se carta está vazia
	#ifdef _DEBUG
		assert( carta != NULL ) ;
	#endif
	
	if ( naipe != NULL )
	{
		if ( carta->naipe == OUROS)
		{
			strcpy( naipe , "OUROS" ) ;
		}
		else if ( carta->naipe == ESPADAS )
		{
			strcpy( naipe , "ESPADAS" ) ;
		}
		else if ( carta->naipe == COPAS )
		{
			strcpy( naipe , "COPAS" ) ;
		}
		else if ( carta->naipe == PAUS )
		{
			strcpy( naipe , "PAUS" ) ;
		}
	}
	
	return carta->naipe ;

}/* Fim função: BAR  &Obter naipe */

