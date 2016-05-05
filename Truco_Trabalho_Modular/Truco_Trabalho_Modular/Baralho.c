/***************************************************************************
*  $MCI Módulo de implementação: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabouço para a automação de testes 
*								de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 - T2 de Programação Modular - Implementação do Truco
*  Autores: Luís Fernando Teixeira Bicalho (lfer),  
*			Leonardo Lages de Alencar(llages) e 
*			Bruno D'Almeida Franco (bfranco)
*
*  $HA Histórico de evolução:
*     Versão	Autor		Data				Observações
*     4			lfer	05/maio/2016		adição e revisão de 
*											comentários no código
*     3			lfer	03/maio/2016		criação das condições 
*											de retorno e adição de 
*                                           funções
*     2			llages	07/jul/2003			unificação de todos os módulos em um só projeto
*     1			lfer	16/abr/2003			início desenvolvimento
*
***************************************************************************/

#include "Baralho.h"
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
struct carta {
	Valor valor;
	Naipe naipe;
};

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BAR  &Criar baralho
*  ****/
LIS_tppLista BAR_CriarBaralho()
{
	int i, j;
	/* Vetores de Valor e de Naipe */
	Valor val[10] = {QUATRO,CINCO,SEIS,SETE,DAMA,VALETE,REI,AS,DOIS,TRES};
	Naipe nap[4] = {OUROS, ESPADAS, COPAS, PAUS};
	Carta* card=NULL;
	LIS_tppLista bar = LIS_CriarLista(NULL);
	for(i=0; i<4; i++)
	{
		for(j=0; j<10 ;j++)
		{
			card = (Carta*) malloc(sizeof(Carta));
			if(card == NULL)
			{
				return NULL;
			}
			card->naipe = nap[i];
			card->valor = val[j];
			if(LIS_InserirElementoApos(bar, card) != LIS_CondRetOK)
			{
				return NULL;
			}
		}
	}
	return bar;
}/* Fim função: BAR  &Criar baralho */

/***************************************************************************
*
*  Função: BAR &Liberar Baralho
*  ****/

BAR_tpCondRet BAR_LiberarBaralho(LIS_tppLista baralho)
{
	Carta* card = (Carta*) LIS_ObterValor(baralho);
	LIS_IrInicioLista(baralho);
	while(card != NULL)
	{
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoExcluida;
		}
		free(card);
		card= (Carta*) LIS_ObterValor(baralho);
	}
	return BAR_CondRetOK;
}/* Fim função: BAR  &Liberar baralho */

/***************************************************************************
*
*  Função: BAR &Embaralhar cartas
*  ****/

BAR_tpCondRet BAR_EmbaralharCartas(LIS_tppLista baralho)
{
	int random, i;
	void* carta;
	srand(time(NULL));
	for(i=0;i<50;i++)
	{
		random = rand()%40;
		LIS_IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) == LIS_CondRetListaVazia)
		{
			return BAR_CondRetErroAndarListaVazia;
		}
		carta=LIS_ObterValor(baralho);
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoExcluida;
		}
		random = rand()%40;
		LIS_IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) == LIS_CondRetListaVazia)
		{
			return BAR_CondRetErroAndarListaVazia;
		}
		if (LIS_InserirElementoAntes(baralho, carta) != LIS_CondRetOK)
		{
			return BAR_CondRetFaltouMemoria;
		}
	}
	return BAR_CondRetOK;
}/* Fim função: BAR  &Criar baralho */

/***************************************************************************
*
*  Função: BAR &Liberar Baralho
*  ****/

BAR_tpCondRet BAR_DistribuirCartas(LIS_tppLista bar, LIS_tppLista jog)
{
	void* card;
	int i;
	for(i=0; i<3; i++)
	{
		LIS_IrInicioLista(bar);
		card = LIS_ObterValor(bar) ;
		if(LIS_ExcluirElemento(bar) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoExcluida;
		}
		LIS_InserirElementoApos(jog, card);
	}
	return BAR_CondRetOK;
}/* Fim função: BAR  &Criar baralho */

/***************************************************************************
*
*  Função: BAR &Liberar Baralho
*  ****/

int BAR_EscolherManilha(LIS_tppLista bar)
{
	int i;
	Carta *vira;
	LIS_IrInicioLista(bar);
	vira = (Carta*)LIS_ObterValor(bar);
	if (vira->valor == TRES)
		return QUATRO;
	else
		return (vira->valor) + 1;
}/* Fim função: BAR  &Criar baralho */

/***************************************************************************
*
*  Função: BAR &Liberar Baralho
*  ****/

int BAR_ObterValor(Carta* card)
{
	return card->valor;
}/* Fim função: BAR  &Criar baralho */

/***************************************************************************
*
*  Função: BAR &Liberar Baralho
*  ****/

int BAR_ObterNaipe(Carta* card)
{
	return card->naipe;
}/* Fim função: BAR  &Criar baralho */

