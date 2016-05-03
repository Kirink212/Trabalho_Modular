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
	CINCO,
	SEIS,
	SETE,
	DAMA,
	VALETE,
	REI,
	AS,
	DOIS,
	TRES
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
	ESPADAS,
	COPAS,
	PAUS
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

LIS_tppLista BAR_CriarBaralho()
{
	int i, j;
	Valor val[10] = {QUATRO, CINCO, SEIS, SETE, DAMA, VALETE, REI, AS, DOIS, TRES};
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
}

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
}

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
}

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
}

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
}

int BAR_ObterValor(Carta* card)
{
	return card->valor;
}

int BAR_ObterNaipe(Carta* card)
{
	return card->naipe;
}